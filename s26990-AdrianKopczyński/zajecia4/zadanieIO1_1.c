#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char filename[100];
    int numElements;
    
    printf("Podaj nazwê pliku: ");
    scanf("%s", filename);

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Nie mo¿na otworzyæ pliku.\n");
        return 1;
    }

    fscanf(file, "%d", &numElements);

    int *numbers = (int*) malloc(numElements * sizeof(int));
    for (int i = 0; i < numElements; i++) {
        fscanf(file, "%d", &numbers[i]);
    }

    printf("Wczytane liczby:\n");
    for (int i = 0; i < numElements; i++) {
        printf("%d\n", numbers[i]);
    }

    free(numbers);

    fclose(file);

    return 0;
}
