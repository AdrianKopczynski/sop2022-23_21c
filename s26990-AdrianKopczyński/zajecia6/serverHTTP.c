#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <time.h>
#include <arpa/inet.h>

typedef struct {
    char* hostname;
    char* files;
} VirtualHost;

void handleClient(int clientSocket, VirtualHost* virtualHosts, int numHosts, FILE* logs) {
    char client_ip[INET_ADDRSTRLEN];
    char time_to_str[20];
    struct tm* time_n;
    time_t current_time;

    time(&current_time);
    time_n = localtime(&current_time);
    strftime(time_to_str, sizeof(time_to_str), "%Y-%m-%d %H:%M:%S", time_n);

    struct sockaddr_in client_addr;
    socklen_t client_address = sizeof(client_addr);
    getpeername(clientSocket, (struct sockaddr*)&client_addr, &client_address);
    inet_ntop(AF_INET, &(client_addr.sin_addr), client_ip, INET_ADDRSTRLEN);
    fprintf(logs, "[%s] Received connection from %s\n", time_to_str, client_ip);

    char client_choose[20];
    char response[255];

    int read_n = read(clientSocket, client_choose, sizeof(client_choose));
    if (read_n < 0) {
        printf("Server: Can't get hostname from client\n");
        fprintf(logs, "[%s] Can't get hostname from client %s, connection terminated\n", time_to_str, client_choose);
        fclose(logs);
        close(clientSocket);
        return;
    }

    bool foundHost = false;
    for (int i = 0; i < numHosts; i++) {
        if (strcmp(client_choose, virtualHosts[i].hostname) == 0) {
            strcpy(response, virtualHosts[i].files);
            foundHost = true;
            break;
        }
    }

    if (!foundHost) {
        printf("Server: Couldn't find this host\n");
        strcpy(response, "404 not found\n");
        send(clientSocket, response, strlen(response) + 1, 0);
        fprintf(logs, "[%s] Can't open %s host, connection terminated\n", time_to_str, client_choose);
        fclose(logs);
        close(clientSocket);
        return;
    }

    int send_n = send(clientSocket, response, strlen(response) + 1, 0);
    if (send_n < 0) {
        printf("Server: Error while sending files\n");
        fprintf(logs, "[%s] Can't send files to client %s\n", time_to_str, client_ip);
        fclose(logs);
        close(clientSocket);
        return;
    }

    fprintf(logs, "[%s] Client successfully received data\n", time_to_str);
    fclose(logs);
    close(clientSocket);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("No port given\n");
        return 1;
    }

    VirtualHost virtualHosts[2];
    virtualHosts[0].hostname = "test.com";
    virtualHosts[0].files = "/home/adrian/http/kraje.txt";
    virtualHosts[1].hostname = "test2.com";
    virtualHosts[1].files = "/home/adrian/http/kraje.txt";
    int numHosts = 2;

    struct sockaddr_in serv_addr;
    int port;
    int socket_n;
    int bind_n;
    FILE* logs;

    time_t current_time;
    time(&current_time);
    struct tm* time_n = localtime(&current_time);
    char time_to_str[20];
    strftime(time_to_str, sizeof(time_to_str), "%Y-%m-%d %H:%M:%S", time_n);

    logs = fopen("logs.txt", "w+");
    if (logs == NULL) {
        printf("Cannot open logs\n");
        return 1;
    }

    port = atoi(argv[1]);
    socket_n = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_n < 0) {
        printf("Server: Failed to create socket\n");
        fclose(logs);
        return 1;
    }
    fprintf(logs, "[%s] Created socket\n", time_to_str);

    memset((char*)&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    bind_n = bind(socket_n, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if (bind_n < 0) {
        printf("Server: Failed to bind\n");
        fclose(logs);
        return 1;
    }
    fprintf(logs, "[%s] Socket binded\n", time_to_str);
    listen(socket_n, 5);
    fprintf(logs, "[%s] Listening for connections\n", time_to_str);
    printf("Server: Waiting for connection\n");

    while (true) {
        struct sockaddr_in client_addr;
        socklen_t client_address = sizeof(client_addr);
        int clientSocket = accept(socket_n, (struct sockaddr*)&client_addr, &client_address);
        if (clientSocket < 0) {
            perror("Server: Failed to accept connection\n");
            fprintf(logs, "[%s] Connection failed\n", time_to_str);
            fclose(logs);
            return 1;
        }

        pid_t fork_n = fork();
        if (fork_n == 0) {
            close(socket_n);
            handleClient(clientSocket, virtualHosts, numHosts, logs);
            return 0;
        } else if (fork_n < 0) {
            printf("Server: Cannot create client process\n");
            fprintf(logs, "[%s] Failed at creating client process\n", time_to_str);
            fclose(logs);
            close(socket_n);
            return 1;
        } else {
            close(clientSocket);
        }
    }

    fclose(logs);
    return 0;
}

