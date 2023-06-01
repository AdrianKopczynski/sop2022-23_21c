#include <stdio.h>

void printSpaces(int n) {
    for (int i = 0; i < n; i++) {
        printf(" ");
    }
}

void printStars(int n) {
    for (int i = 0; i < n; i++) {
        printf("*");
    }
}

void printTree(int height) {
    int spaces = height - 1;
    int stars = 1;

    for (int i = 0; i < height; i++) {
        printSpaces(spaces);
        printStars(stars);
        printf("\n");
        spaces--;
        stars += 2;
    }
    
    printSpaces(height - 1);
    printf("| |\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Podaj wysokosc choinki jako parametr wywolania programu.\n");
        return 1;
    }

    int height = atoi(argv[1]);
    if (height <= 0) {
        printf("Wysokosc musi byc liczba dodatnia.\n");
        return 1;
    }

    printTree(height);

    return 0;
}
