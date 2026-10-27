#include <stdio.h>
#define MAX 20

int parent[MAX];
int rank[MAX];

void makeSet(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void unionSet(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);

    if (rootX == rootY) {
        printf("%d and %d are already in the same set.\n", x, y);
        return;
    }

    if (rank[rootX] < rank[rootY]) {
        parent[rootX] = rootY;
    } else if (rank[rootX] > rank[rootY]) {
        parent[rootY] = rootX;
    } else {
        parent[rootY] = rootX;
        rank[rootX]++;
    }
}

void display(int n) {
    printf("\nElement\tParent\tRank\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\n", i, parent[i], rank[i]);
    }
}

int main() {
    int n, choice, x, y;

    printf("Enter number of elements: ");
    scanf("%d", &n);
    makeSet(n);

    while (1) {
        printf("\n--- DISJOINT SET ---\n");
        printf("1. FIND\n");
        printf("2. UNION\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter element: ");
                scanf("%d", &x);
                printf("Representative of %d = %d\n", x, find(x));
                break;

            case 2:
                printf("Enter two elements: ");
                scanf("%d %d", &x, &y);
                unionSet(x, y);
                break;

            case 3:
                display(n);
                break;

            case 4:
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}