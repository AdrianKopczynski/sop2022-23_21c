#include <stdio.h>

int fibonacciRecursive(int n) {
    if (n <= 1)
        return n;
    else
        return fibonacciRecursive(n - 1) + fibonacciRecursive(n - 2);
}

void fibonacciIterative(int n) {
    int a = 0, b = 1, tmp;

    printf("Iteracyjnie: ");

    if (n >= 1)
        printf("%d ", a);
    if (n >= 2)
        printf("%d ", b);

    for (int i = 3; i <= n; i++) {
        tmp = a + b;
        printf("%d ", tmp);
        a = b;
        b = tmp;
    }

    printf("\n");
}

int main() {
    int n;

    printf("Podaj ilosc kolejnych liczb ciagu Fibonacciego do wygenerowania: ");
    scanf("%d", &n);

    printf("Rekurencyjnie: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", fibonacciRecursive(i));
    }
    printf("\n");

    fibonacciIterative(n);

    return 0;
}
