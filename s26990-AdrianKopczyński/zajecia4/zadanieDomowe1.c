#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Blad alokacji pamieci.\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

void insertAtBeginning(struct Node** head, int value) {
    struct Node* newNode = createNode(value);
    newNode->next = *head;
    *head = newNode;
    printf("Wstawiono element %d na poczatek listy.\n", value);
}

void insertAtEnd(struct Node** head, int value) {
    struct Node* newNode = createNode(value);
    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    printf("Wstawiono element %d na koniec listy.\n", value);
}

void displayList(struct Node* head) {
    if (head == NULL) {
        printf("Lista jest pusta.\n");
    } else {
        printf("Zawartosc listy: ");
        struct Node* current = head;
        while (current != NULL) {
            printf("%d ", current->data);
            current = current->next;
        }
        printf("\n");
    }
}

void deleteElement(struct Node** head, int value) {
    if (*head == NULL) {
        printf("Lista jest pusta.\n");
        return;
    }

    struct Node* current = *head;
    struct Node* previous = NULL;

    while (current != NULL && current->data != value) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Element %d nie wystepuje w liscie.\n", value);
        return;
    }

    // Usuwanie elementu
    if (previous == NULL) {
        *head = current->next;
    } else {
        previous->next = current->next;
    }

    printf("Usunieto element %d z listy.\n", value);
    free(current);
}

void freeList(struct Node* head) {
    struct Node* current = head;
    struct Node* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

int main() {
    struct Node* head = NULL;
    insertAtEnd(&head, 5);
    insertAtBeginning(&head, 3);
    insertAtEnd(&head, 7);
    insertAtBeginning(&head, 1);
    displayList(head);
    deleteElement(&head, 5);
    deleteElement(&head, 10);
    displayList(head);
    freeList(head);
    return 0;
}

