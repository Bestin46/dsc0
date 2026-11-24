#include <stdio.h>
#include <stdlib.h>
#define MAX 20
struct Node {
    int vertex;
    struct Node *next;
};
struct Node *adjList[MAX];
int adjMatrix[MAX][MAX];
int n;
/* Add edge to adjacency list */
void addListEdge(int u, int v) {
    struct Node *newNode = malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->vertex = v;
    newNode->next = adjList[u];
    adjList[u] = newNode;
}
/* Add edge to both representations */
void addEdge(int u, int v) {
    adjMatrix[u][v] = 1;
    adjMatrix[v][u] = 1;
    addListEdge(u, v);
    addListEdge(v, u);
}
/* Display adjacency matrix */
void displayMatrix() {
    int i, j;
    printf("\nAdjacency Matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++)
            printf("%d ", adjMatrix[i][j]);
        printf("\n");
    }
}
/* Display adjacency list */
void displayList() {
    int i;
    struct Node *temp;
    printf("\nAdjacency List:\n");
    for (i = 0; i < n; i++) {
        printf("%d: ", i);
        temp = adjList[i];
        while (temp != NULL) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}
int main() {
    int e, u, v, i, choice;
    printf("Enter number of vertices (1-%d): ", MAX);
    scanf("%d", &n);
    if (n < 1 || n > MAX) {
        printf("Invalid number of vertices!\n");
        return 1;
    }
    for (i = 0; i < n; i++)
        adjList[i] = NULL;
    printf("Enter number of edges: ");
    scanf("%d", &e);
    if (e < 0 || e > n * (n - 1) / 2) {
        printf("Invalid number of edges!\n");
        return 1;
    }
    printf("Enter edges (u v), vertices numbered 0 to %d:\n", n - 1);
    for (i = 0; i < e; i++) {
        scanf("%d %d", &u, &v);
        if (u < 0 || u >= n || v < 0 || v >= n ||
            u == v || adjMatrix[u][v]) {
            printf("Invalid or duplicate edge!\n");
            return 1;
        }
        addEdge(u, v);
    }
    do {
        printf("\n--- Graph Representation ---\n");
        printf("1. Display Adjacency Matrix\n");
        printf("2. Display Adjacency List\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                displayMatrix();
                break;
            case 2:
                displayList();
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 3);
    /* Free allocated memory */
    for (i = 0; i < n; i++) {
        struct Node *temp = adjList[i];
        while (temp != NULL) {
            struct Node *next = temp->next;
            free(temp);
            temp = next;
        }
    }
    return 0;
}