#include <stdio.h>

#define MAX 20
#define MAXHEAP 500
#define INF 999999

struct Item {
    int weight;
    int vertex;
    int parent;
};

struct Item heap[MAXHEAP];
int size = 0;

/* Insert an item into the min-heap */
void insert(struct Item item) {
    int i;

    if (size >= MAXHEAP - 1) {
        printf("Heap is full!\n");
        return;
    }

    i = ++size;

    while (i > 1 && item.weight < heap[i / 2].weight) {
        heap[i] = heap[i / 2];
        i = i / 2;
    }

    heap[i] = item;
}

/* Remove the minimum-weight item */
struct Item deleteMin() {
    struct Item minItem = heap[1];
    struct Item last = heap[size--];
    int i = 1, child;

    while (2 * i <= size) {
        child = 2 * i;

        if (child < size &&
            heap[child + 1].weight < heap[child].weight)
            child++;

        if (last.weight <= heap[child].weight)
            break;

        heap[i] = heap[child];
        i = child;
    }

    if (size > 0)
        heap[i] = last;

    return minItem;
}

int main() {
    int graph[MAX][MAX];
    int visited[MAX] = {0};
    int n, e, u, v, w, i;
    int selected = 0, totalCost = 0;
    struct Item item;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    if (n < 1 || n > MAX) {
        printf("Invalid number of vertices!\n");
        return 1;
    }

    printf("Enter number of edges: ");
    scanf("%d", &e);

    if (e < 0 || e > n * (n - 1) / 2) {
        printf("Invalid number of edges!\n");
        return 1;
    }

    /* Initialize graph */
    for (i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            graph[i][j] = INF;
    }

    printf("Enter edges (source destination weight):\n");

    for (i = 0; i < e; i++) {
        scanf("%d %d %d", &u, &v, &w);

        if (u < 0 || u >= n || v < 0 || v >= n ||
            u == v || w <= 0 || w >= INF ||
            graph[u][v] != INF) {
            printf("Invalid edge! Enter valid, unique edges.\n");
            return 1;
        }

        graph[u][v] = w;
        graph[v][u] = w;
    }

    /* Start from vertex 0 */
    visited[0] = 1;

    for (i = 0; i < n; i++) {
        if (graph[0][i] != INF) {
            item.weight = graph[0][i];
            item.vertex = i;
            item.parent = 0;
            insert(item);
        }
    }

    printf("\nEdges in the Minimum Spanning Tree:\n");

    while (size > 0 && selected < n - 1) {
        item = deleteMin();

        if (visited[item.vertex])
            continue;

        visited[item.vertex] = 1;

        printf("%d - %d : %d\n",
               item.parent, item.vertex, item.weight);

        totalCost += item.weight;
        selected++;

        /* Insert edges from the newly visited vertex */
        for (i = 0; i < n; i++) {
            if (!visited[i] && graph[item.vertex][i] != INF) {
                struct Item next;

                next.weight = graph[item.vertex][i];
                next.vertex = i;
                next.parent = item.vertex;

                insert(next);
            }
        }
    }

    if (selected != n - 1) {
        printf("Minimum Spanning Tree does not exist.\n");
    } else {
        printf("Total cost of MST = %d\n", totalCost);
    }

    return 0;
}