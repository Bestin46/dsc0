#include <stdio.h>
int main() {
    int graph[20][20] = {0};
    int visited[20] = {0};
    int parent[20];
    int queue[20];
    int n, e, u, v, start, goal;
    int front = 0, rear = 0;
    int i, node, path[20], len = 0;
    printf("Enter number of vertices (max 20): ");
    scanf("%d", &n);
    if (n < 1 || n > 20) {
        printf("Invalid number of vertices!\n");
        return 0;
    }
    printf("Enter number of edges: ");
    scanf("%d", &e);
    if (e < 0 || e > n * (n - 1) / 2) {
        printf("Invalid number of edges!\n");
        return 0;
    }
    printf("Enter edges (u v), vertices from 0 to %d:\n", n - 1);
    for (i = 0; i < e; ) {
        scanf("%d %d", &u, &v);
        if (u < 0 || u >= n || v < 0 || v >= n) {
            printf("Warning: Invalid vertex! Enter vertices from 0 to %d.\n", n - 1);
            continue;
        }
        graph[u][v] = 1;
        graph[v][u] = 1;
        i++;
    }
    printf("Enter start vertex: ");
    scanf("%d", &start);
    printf("Enter destination vertex: ");
    scanf("%d", &goal);
    if (start < 0 || start >= n || goal < 0 || goal >= n) {
        printf("Warning: Invalid start or destination vertex!\n");
        return 0;
    }
    for (i = 0; i < n; i++)
        parent[i] = -1;
    queue[rear++] = start;
    visited[start] = 1;
    printf("BFS Traversal: ");
    while (front < rear) {
        node = queue[front++];
        printf("%d ", node);
        for (i = 0; i < n; i++) {
            if (graph[node][i] == 1 && !visited[i]) {
                visited[i] = 1;
                parent[i] = node;
                queue[rear++] = i;
            }
        }
    }
    if (!visited[goal]) {
        printf("\nNo path exists\n");
    } else {
        node = goal;
        while (node != -1) {
            path[len++] = node;
            node = parent[node];
        }
        printf("\nShortest Path: ");
        for (i = len - 1; i >= 0; i--)
            printf("%d ", path[i]);
        printf("\nDistance: %d\n", len - 1);
    }
    return 0;
}