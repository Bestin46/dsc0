#include <stdio.h>

#define MAX 100

int heap[MAX];
int size = 0;
int isMinHeap;

/* Compare two elements based on heap type */
int compare(int a, int b) {
    if (isMinHeap)
        return a < b;
    else
        return a > b;
}

/* Heapify upwards */
void heapifyUp(int i) {
    int parent, temp;

    while (i > 0) {
        parent = (i - 1) / 2;

        if (compare(heap[i], heap[parent])) {
            temp = heap[i];
            heap[i] = heap[parent];
            heap[parent] = temp;
            i = parent;
        } else {
            break;
        }
    }
}

/* Heapify downwards */
void heapifyDown(int i) {
    int left, right, best, temp;

    while (1) {
        left = 2 * i + 1;
        right = 2 * i + 2;
        best = i;

        if (left < size &&
            compare(heap[left], heap[best]))
            best = left;

        if (right < size &&
            compare(heap[right], heap[best]))
            best = right;

        if (best == i)
            break;

        temp = heap[i];
        heap[i] = heap[best];
        heap[best] = temp;

        i = best;
    }
}

/* Insert an element */
void insert(int value) {
    if (size == MAX) {
        printf("Heap is full!\n");
        return;
    }

    heap[size] = value;
    heapifyUp(size);
    size++;

    printf("Element inserted successfully.\n");
}

/* Delete the root element */
void deleteRoot() {
    int deleted;

    if (size == 0) {
        printf("Heap is empty!\n");
        return;
    }

    deleted = heap[0];
    heap[0] = heap[size - 1];
    size--;

    if (size > 0)
        heapifyDown(0);

    printf("Deleted element: %d\n", deleted);
}

/* Build heap from existing elements */
void buildHeap() {
    int n, i;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    if (n < 0 || n > MAX) {
        printf("Invalid number of elements!\n");
        return;
    }

    printf("Enter elements:\n");

    for (i = 0; i < n; i++)
        scanf("%d", &heap[i]);

    size = n;

    /* Bottom-up heapify */
    for (i = size / 2 - 1; i >= 0; i--)
        heapifyDown(i);

    printf("Heap created successfully.\n");
}

/* Display heap */
void display() {
    int i;

    if (size == 0) {
        printf("Heap is empty!\n");
        return;
    }

    printf("Heap elements: ");

    for (i = 0; i < size; i++)
        printf("%d ", heap[i]);

    printf("\n");
}

int main() {
    int choice, type, value;

    printf("1. Min-Heap\n");
    printf("2. Max-Heap\n");
    printf("Choose heap type: ");
    scanf("%d", &type);

    if (type != 1 && type != 2) {
        printf("Invalid heap type!\n");
        return 1;
    }

    isMinHeap = (type == 1);

    do {
        printf("\n--- Binary Heap Menu ---\n");
        printf("1. Insert\n");
        printf("2. Delete root\n");
        printf("3. Heapify / Build heap\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                insert(value);
                break;

            case 2:
                deleteRoot();
                break;

            case 3:
                buildHeap();
                break;

            case 4:
                display();
                break;

            case 5:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 5);

    return 0;
}