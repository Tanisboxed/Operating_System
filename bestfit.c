#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Node {
    int size;
    int isAllocated;
    struct Node* next;
} Node;

Node* createNode(int size) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->size = size;
    newNode->isAllocated = 0;
    newNode->next = NULL;
    return newNode;
}

void allocateMemory(Node* head, int size) {
    Node* current = head;
    Node* bestFit = NULL;
    int minSizeDiff = INT_MAX;

    while (current != NULL) {
        if (current->isAllocated == 0 && current->size >= size) {
            int sizeDiff = current->size - size;
            if (sizeDiff < minSizeDiff) {
                bestFit = current;
                minSizeDiff = sizeDiff;
            }
        }
        current = current->next;
    }

    if (bestFit != NULL) {
        bestFit->isAllocated = 1;
        printf("Memory allocated successfully!\n");
    } else {
        printf("Insufficient memory available for allocation.\n");
    }
}

void deallocateMemory(Node* head) {
    Node* current = head;
    while (current != NULL) {
        current->isAllocated = 0;
        current = current->next;
    }
    printf("Memory deallocated successfully!\n");
}

void displayMemoryStatus(Node* head) {
    Node* current = head;
    printf("Memory Status:\n");
    while (current != NULL) {
        printf("Size: %d\tAllocated: %s\n", current->size, current->isAllocated ? "Yes" : "No");
        current = current->next;
    }
}

int main() {
    Node* head = createNode(100);
    head->next = createNode(50);
    head->next->next = createNode(200);
    head->next->next->next = createNode(75);

    int choice, size;

    do {
        printf("\n---- Best Fit Memory Allocation Menu ----\n");
        printf("1. Allocate Memory\n");
        printf("2. Deallocate Memory\n");
        printf("3. Display Memory Status\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the size to allocate: ");
                scanf("%d", &size);
                allocateMemory(head, size);
                break;
            case 2:
                deallocateMemory(head);
                break;
            case 3:
                displayMemoryStatus(head);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}
