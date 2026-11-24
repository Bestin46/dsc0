#include <stdio.h>

#define MAX 20
#define HEAP_CAPACITY 500
#define INF 999999

struct Item {
    int distance;
    int vertex;
};

struct Item heap[HEAP_CAPACITY];
int size = 0;

/* Insert into min-heap */
void insert(struct Item item) {
    int i;

    if (size >= HEAP_CAPACITY - 1)
        return;

    i = ++size;

    while (i > 1 &&
           item.distance < heap[i / 2].distance) {
        heap[i] = heap[i / 2];
        i = i / 2;
    }

    heap[i] = item;
}

/* Remove minimum-distance item */
struct Item deleteMin() {
    struct Item minItem = heap[1];
    struct Item last = heap[size--];
    int i = 1, child;

    while (2 * i <= size) {
        child = 2 * i;

        if (child < size &&
            heap[child + 1].distance < heap[child].distance)
            child++;

        if (last.distance <= heap[child].distance)
            break;

        heap[i] = heap[child];
        i = child;
    }

    if (size > 0)
        heap[i] = last;

    return minItem;
}

/* Print shortest path */
void printPath(int parent[], int vertex) {
    if (vertex == -1)
        return;

    printPath(parent, parent[vertex]);
    printf("%d ", vertex);
}

int main() {
    int graph[MAX][MAX];
    int dist[MAX], parent[MAX];
    int n, e, source, u, v, w, i, j;
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

    /* Initialize adjacency matrix */
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++)
            graph[i][j] = INF;
    }

    printf("Enter edges (source destination weight):\n");

    for (i = 0; i < e; i++) {
        scanf("%d %d %d", &u, &v, &w);

        if (u < 0 || u >= n || v < 0 || v >= n ||
            u == v || w < 0 || w >= INF ||
            graph[u][v] != INF) {
            printf("Invalid edge!\n");
            return 1;
        }

        graph[u][v] = w;
        graph[v][u] = w;
    }

    printf("Enter source vertex: ");
    scanf("%d", &source);

    if (source < 0 || source >= n) {
        printf("Invalid source vertex!\n");
        return 1;
    }

    /* Initialize distances and parents */
    for (i = 0; i < n; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }

    dist[source] = 0;

    item.distance = 0;
    item.vertex = source;
    insert(item);

    /* Dijkstra's algorithm */
    while (size > 0) {
        item = deleteMin();
        u = item.vertex;

        /* Ignore outdated heap entries */
        if (item.distance != dist[u])
            continue;

        for (v = 0; v < n; v++) {
            if (graph[u][v] != INF &&
                dist[u] + graph[u][v] < dist[v]) {

                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;

                item.distance = dist[v];
                item.vertex = v;
                insert(item);
            }
        }
    }

    printf("\nVertex\tDistance\tShortest Path\n");

    for (i = 0; i < n; i++) {
        if (dist[i] == INF) {
            printf("%d\tUnreachable\tNo path\n", i);
        } else {
            printf("%d\t%d\t\t", i, dist[i]);
            printPath(parent, i);
            printf("\n");
        }
    }

    return 0;
}