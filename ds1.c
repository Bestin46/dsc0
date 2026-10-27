#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

typedef struct Node {
    int key;
    int value;
    struct Node *next;
} Node;

Node *chainTable[SIZE] = {NULL};

typedef struct {
    int key;
    int value;
    int status;
} Entry;

Entry openTable[SIZE];

int hashFunction(int key) {
    return key % SIZE;
}

void initializeOpenTable() {
    int i;
    for (i = 0; i < SIZE; i++)
        openTable[i].status = 0;
}

void insertChaining(int key, int value) {
    int index = hashFunction(key);
    Node *newNode = (Node *)malloc(sizeof(Node));

    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    newNode->key = key;
    newNode->value = value;
    newNode->next = chainTable[index];
    chainTable[index] = newNode;

    printf("Key inserted using Separate Chaining at index %d.\n", index);
}

int searchChaining(int key) {
    int index = hashFunction(key);
    Node *temp = chainTable[index];

    while (temp != NULL) {
        if (temp->key == key) {
            printf("Key found!\n");
            printf("Key : %d\n", temp->key);
            printf("Value : %d\n", temp->value);
            return 1;
        }
        temp = temp->next;
    }

    return 0;
}

int deleteChaining(int key) {
    int index = hashFunction(key);
    Node *temp = chainTable[index];
    Node *prev = NULL;

    while (temp != NULL) {
        if (temp->key == key) {
            if (prev == NULL)
                chainTable[index] = temp->next;
            else
                prev->next = temp->next;

            free(temp);
            printf("Key deleted successfully.\n");
            return 1;
        }

        prev = temp;
        temp = temp->next;
    }

    return 0;
}

int insertOpenAddressing(int key, int value, int startIndex) {
    int index, i;

    for (i = 0; i < SIZE; i++) {
        index = (startIndex + i) % SIZE;

        if (openTable[index].status != 1) {
            openTable[index].key = key;
            openTable[index].value = value;
            openTable[index].status = 1;

            printf("Key inserted using Open Addressing at index %d.\n", index);
            return 1;
        }
    }

    printf("Hash table is full!\n");
    return 0;
}

int searchOpenAddressing(int key) {
    int startIndex = hashFunction(key);
    int index, i;

    for (i = 0; i < SIZE; i++) {
        index = (startIndex + i) % SIZE;

        if (openTable[index].status == 0)
            return 0;

        if (openTable[index].status == 1 && openTable[index].key == key) {
            printf("Key found!\n");
            printf("Key : %d\n", openTable[index].key);
            printf("Value : %d\n", openTable[index].value);
            return 1;
        }
    }

    return 0;
}

int deleteOpenAddressing(int key) {
    int startIndex = hashFunction(key);
    int index, i;

    for (i = 0; i < SIZE; i++) {
        index = (startIndex + i) % SIZE;

        if (openTable[index].status == 0)
            return 0;

        if (openTable[index].status == 1 && openTable[index].key == key) {
            openTable[index].status = 2;
            printf("Key deleted successfully.\n");
            return 1;
        }
    }

    return 0;
}

void displayHashTable() {
    int i;
    Node *temp;

    printf("\n========== HASH TABLE ==========\n");

    printf("\n--- Separate Chaining ---\n");

    for (i = 0; i < SIZE; i++) {
        printf("Index %d: ", i);

        temp = chainTable[i];

        if (temp == NULL) {
            printf("Empty");
        } else {
            while (temp != NULL) {
                printf("[%d : %d]", temp->key, temp->value);

                if (temp->next != NULL)
                    printf(" -> ");

                temp = temp->next;
            }
        }

        printf("\n");
    }

    printf("\n--- Open Addressing ---\n");

    for (i = 0; i < SIZE; i++) {
        printf("Index %d: ", i);

        if (openTable[i].status == 0) {
            printf("Empty");
        } else if (openTable[i].status == 1) {
            printf("Key = %d, Value = %d",
                   openTable[i].key, openTable[i].value);
        } else {
            printf("Deleted");
        }

        printf("\n");
    }

    printf("================================\n");
}

void insert() {
    int key, value, index, choice;

    printf("\nEnter key: ");
    scanf("%d", &key);

    printf("Enter value: ");
    scanf("%d", &value);

    index = hashFunction(key);
    printf("Hash index = %d\n", index);

    if (openTable[index].status == 0 && chainTable[index] == NULL) {
        openTable[index].key = key;
        openTable[index].value = value;
        openTable[index].status = 1;

        printf("Key inserted at index %d.\n", index);
        return;
    }

    printf("\nCollision occurred at index %d!\n", index);
    printf("\nChoose collision resolution technique:\n");
    printf("1. Separate Chaining\n");
    printf("2. Open Addressing\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        insertChaining(key, value);
    } else if (choice == 2) {
        insertOpenAddressing(key, value, index);
    } else {
        printf("Invalid choice!\n");
    }
}

void search() {
    int key;

    printf("\nEnter key to search: ");
    scanf("%d", &key);

    if (searchOpenAddressing(key))
        return;

    if (searchChaining(key))
        return;

    printf("Key not found.\n");
}

void deleteKey() {
    int key;

    printf("\nEnter key to delete: ");
    scanf("%d", &key);

    if (deleteOpenAddressing(key))
        return;

    if (deleteChaining(key))
        return;

    printf("Key not found.\n");
}

int main() {
    int choice;

    initializeOpenTable();

    while (1) {
        printf("\n=========================\n");
        printf("       HASH TABLE\n");
        printf("=========================\n");
        printf("1. Insert\n");
        printf("2. Search\n");
        printf("3. Delete\n");
        printf("4. Display Hash Table\n");
        printf("5. Exit\n");
        printf("=========================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                insert();
                break;

            case 2:
                search();
                break;

            case 3:
                deleteKey();
                break;

            case 4:
                displayHashTable();
                break;

            case 5:
                printf("Program terminated.\n");
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}