#include <stdio.h>

struct Edge {
    int u, v, w;
};

int parent[20];

int find(int x) {
    if (parent[x] == x)
        return x;
    return find(parent[x]);
}

void unionSet(int u, int v) {
    parent[u] = v;
}

int main() {
    struct Edge e[50], temp;
    int n, m, i, j, u, v;
    int count = 0, cost = 0;

    printf("Enter number of vertices (max 20): ");
    scanf("%d", &n);

    if (n < 1 || n > 20) {
        printf("Invalid number of vertices!\n");
        return 0;
    }

    printf("Enter number of edges (max 50): ");
    scanf("%d", &m);

    if (m < 0 || m > 50) {
        printf("Invalid number of edges!\n");
        return 0;
    }

    printf("Enter edges (u v weight):\n");

    for (i = 0; i < m; i++) {
        scanf("%d %d %d", &e[i].u, &e[i].v, &e[i].w);

        if (e[i].u < 0 || e[i].u >= n ||
            e[i].v < 0 || e[i].v >= n ||
            e[i].u == e[i].v) {
            printf("Warning: Invalid edge!\n");
            return 0;
        }
    }

    /* Sort edges by weight */
    for (i = 0; i < m - 1; i++) {
        for (j = i + 1; j < m; j++) {
            if (e[i].w > e[j].w) {
                temp = e[i];
                e[i] = e[j];
                e[j] = temp;
            }
        }
    }

    /* Initialize Disjoint Set */
    for (i = 0; i < n; i++)
        parent[i] = i;

    printf("Edges in Minimum Spanning Tree:\n");

    for (i = 0; i < m && count < n - 1; i++) {
        u = find(e[i].u);
        v = find(e[i].v);

        if (u != v) {
            printf("%d - %d : %d\n",
                   e[i].u, e[i].v, e[i].w);

            unionSet(u, v);
            cost += e[i].w;
            count++;
        }
    }

    if (count == n - 1)
        printf("Total MST weight = %d\n", cost);
    else
        printf("MST not possible. Graph is disconnected.\n");

    return 0;
}