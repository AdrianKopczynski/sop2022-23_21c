#include <stdio.h>

int maximum(int a, int b) {
    return (a > b) ? a : b;
}

int minimum(int a, int b) {
    return (a < b) ? a : b;
}

int sum(int a, int b) {
    return a + b;
}

int main() {
    int (*functions[3])(int, int) = {maximum, minimum, sum};
    int functionId, elementCount;

    printf("Wybierz funkcje:\n");
    printf("0 - Maksimum\n");
    printf("1 - Minimum\n");
    printf("2 - Suma\n");
    scanf("%d", &functionId);

    if (functionId < 0 || functionId > 2) {
        printf("Nieprawidlowy numer funkcji.\n");
        return 1;
    }

    printf("Podaj liczbe elementow ciagu: ");
    scanf("%d", &elementCount);

    int v;
    printf("Podaj kolejno liczby:\n");
    scanf("%d", &v);

    for (int i = 1; i < elementCount; i++) {
        int element;
        scanf("%d", &element);

        v = functions[functionId](v, element);
    }

    printf("Wynik: %d\n", v);

    return 0;
}
