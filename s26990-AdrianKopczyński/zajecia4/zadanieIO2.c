#include <stdio.h>

void printHexDump(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Nie mozna otworzyc pliku.\n");
        return;
    }

    unsigned char buffer[16];
    size_t bytesRead;

    int offset = 0;
    while ((bytesRead = fread(buffer, sizeof(unsigned char), 16, file)) > 0) {
        printf("%08X  ", offset);

        for (size_t i = 0; i < bytesRead; i++) {
            printf("%02X ", buffer[i]);
            if ((i + 1) % 4 == 0) {
                printf(" ");  
            }
        }

        if (bytesRead < 16) {
            for (size_t i = bytesRead; i < 16; i++) {
                printf("   ");
                if ((i + 1) % 4 == 0) {
                    printf(" ");
                }
            }
        }

        printf(" ");
		/*ASCI*/
        for (size_t i = 0; i < bytesRead; i++) {
            if (buffer[i] >= 32 && buffer[i] <= 126) {
                printf("%c", buffer[i]);
            } else {
                printf(".");
            }
        }

        printf("\n");

        offset += bytesRead;
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Podaj nazwe pliku jako argument.\n");
        return 1;
    }

    char *filename = argv[1];
    printHexDump(filename);

    return 0;
}
