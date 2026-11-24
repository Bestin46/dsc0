#include <stdio.h>
int graph[20][20], visited[20];
int n;
void dfs(int v) {
    int i;
    visited[v] = 1;
    printf("%d ", v);
    for (i = 0; i < n; i++) {
        if (graph[v][i] && !visited[i])
            dfs(i);
    }
}
int checkCycle(int v, int parent) {
    int i;
    visited[v] = 1;
    for (i = 0; i < n; i++) {
        if (graph[v][i]) {
            if (!visited[i]) {
                if (checkCycle(i, v))
                    return 1;
            } else if (i != parent) {
                return 1;
            }
        }
    }
    return 0;
}
int main() {
    int e, u, v, i, connected = 1, cycle;
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
        if (u == v || graph[u][v]) {
            printf("Warning: Self-loops and duplicate edges are not allowed. Try again.\n");
            continue;
        }
        graph[u][v] = 1;
        graph[v][u] = 1;
        i++;
    }
    printf("DFS Traversal: ");
    dfs(0);
    for (i = 0; i < n; i++) {
        if (!visited[i])
            connected = 0;
    }
    printf("\n");
    for (i = 0; i < n; i++)
        visited[i] = 0;
    cycle = checkCycle(0, -1);
    if (cycle)
        printf("Cycle detected\n");
    else
        printf("No cycle detected\n");

    if (connected)
        printf("Graph is connected\n");
    else
        printf("Graph is not connected\n");
    return 0;
}