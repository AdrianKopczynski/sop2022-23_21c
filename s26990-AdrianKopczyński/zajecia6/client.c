#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Client: Error - no arguments\n");
        printf("Client: [server IP], [server Port]\n");
        return 1;
    }

    int server_port;
    int socket_n;
    struct sockaddr_in serv_addr;
    int connect_n;
    char *fileName;
    int fileLen;
    int write_n;
    int fileSize;
    int read_n;
    char *buffer;
    FILE *file;
    char *server;

    server = argv[1];
    server_port = atoi(argv[2]);
    socket_n = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_n < 0) {
        printf("Client: Error while creating socket\n");
        return 1;
    }

    memset((char *)&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(server_port);
    connect_n = connect(socket_n, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    if (connect_n < 0) {
        printf("Client: Error while attempting to connect\n");
        return 1;
    }

    printf("Client: Connected\n");
    printf("Client: Enter file name length\n");
    scanf("%d", &fileLen);
    fileName = malloc((fileLen + 1) * sizeof(char));
    printf("Client: Enter file name\n");
    scanf("%s", fileName);
    fileName[strcspn(fileName, "\n")] = '\0';
    write_n = write(socket_n, &fileLen, sizeof(int));
    if (write_n < 0) {
        printf("Client: Can't send file length\n");
        return 1;
    }
    printf("Client: File name length sent\n");
    write_n = write(socket_n, fileName, fileLen);
    if (write_n < 0) {
        printf("Client: Can't send file name\n");
        return 1;
    }
    printf("Client: File name sent\n");

    read_n = read(socket_n, &fileSize, sizeof(int));
    if (read_n < 0) {
        printf("Client: Error while getting file size from server\n");
        return 1;
    }
    if (fileSize < 0) {
        printf("Client: Error with file, maybe it doesn't exist\n");
        return 1;
    }
    file = fopen(fileName, "w");
    if (!file) {
        printf("Client: Error opening file\n");
        return 1;
    }
    int number_bytes = 0;
    buffer = malloc(fileSize * sizeof(char));
    while (number_bytes < fileSize) {
        read_n = read(socket_n, buffer, fileSize - number_bytes);
        if (read_n <= 0)
            break;

        write_n = fwrite(buffer, sizeof(char), read_n, file);
        if (write_n != read_n) {
            printf("Client: Error saving file\n");
            fclose(file);
            free(buffer);
            free(fileName);
            close(socket_n);
            return 1;
        }

        number_bytes += read_n;
    }

    fclose(file);
    free(fileName);
    free(buffer);
    close(socket_n);
    printf("Client: File downloaded successfully\n");
    return 0;
}

