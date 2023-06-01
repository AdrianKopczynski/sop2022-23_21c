#include <stdio.h>
#include <stdlib.h>

#define MAX_FILENAME_LENGTH 100

void printNumbersInReverseOrder(int *numbers, int numElements) {
    for (int i = numElements - 1; i >= 0; i--) {
        printf("%d\n", numbers[i]);
    }
}

int main(int argc, char *argv[]) {
    FILE *file;
    int numElements;
    int *numbers;
    
    if (argc == 1) {
        printf("Podaj liczbe elementow ciagu: ");
        scanf("%d", &numElements);
        
        numbers = (int*) malloc(numElements * sizeof(int));
        
        printf("Podaj liczby:\n");
        for (int i = 0; i < numElements; i++) {
            scanf("%d", &numbers[i]);
        }
        printf("\nLiczby w odwrotnej kolejnosci: \n");
        printNumbersInReverseOrder(numbers, numElements);
        
        free(numbers);
    } else if (argc == 2) {
        char filename[MAX_FILENAME_LENGTH];
        strcpy(filename, argv[1]);
        
        file = fopen(filename, "r");
        if (file == NULL) {
            printf("Nie mozna otworzyc pliku.\n");
            return 1;
        }
        
        fscanf(file, "%d", &numElements);
        
        numbers = (int*) malloc(numElements * sizeof(int));
        
        for (int i = 0; i < numElements; i++) {
            fscanf(file, "%d", &numbers[i]);
        }
        printf("\n\n Liczby w odwrotnej kolejnosci: \n");
        printNumbersInReverseOrder(numbers, numElements);
        
        free(numbers);
        
        fclose(file);
    } else {
        printf("Nieprawidlowa liczba argumentow.\n");
        return 1;
    }
    
    return 0;
}
