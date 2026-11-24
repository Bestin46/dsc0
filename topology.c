#include <stdio.h>

#define MAX 20

int graph[MAX][MAX];
int n;

/* DFS helper function */
int dfs(int v, int state[], int stack[], int *top)
{
    int i;

    state[v] = 1;

    for(i = 0; i < n; i++)
    {
        if(graph[v][i])
        {
            if(state[i] == 1)
                return 0;

            if(state[i] == 0)
            {
                if(!dfs(i, state, stack, top))
                    return 0;
            }
        }
    }

    state[v] = 2;
    stack[++(*top)] = v;

    return 1;
}

/* Topological sort using DFS */
void topologicalDFS()
{
    int state[MAX] = {0};
    int stack[MAX], top = -1;
    int i;

    for(i = 0; i < n; i++)
    {
        if(state[i] == 0)
        {
            if(!dfs(i, state, stack, &top))
            {
                printf("Cycle detected. Topological sorting is not possible.\n");
                return;
            }
        }
    }

    printf("Topological order using DFS: ");

    while(top >= 0)
        printf("%d ", stack[top--]);

    printf("\n");
}

/* Topological sort using BFS */
void topologicalBFS()
{
    int indegree[MAX] = {0};
    int queue[MAX], front = 0, rear = 0;
    int count = 0, i, j, v;

    /* Calculate indegree */
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            if(graph[i][j])
                indegree[j]++;
        }
    }

    /* Insert zero-indegree vertices */
    for(i = 0; i < n; i++)
    {
        if(indegree[i] == 0)
            queue[rear++] = i;
    }

    printf("Topological order using BFS: ");

    while(front < rear)
    {
        v = queue[front++];
        printf("%d ", v);
        count++;

        for(j = 0; j < n; j++)
        {
            if(graph[v][j])
            {
                indegree[j]--;

                if(indegree[j] == 0)
                    queue[rear++] = j;
            }
        }
    }

    if(count != n)
        printf("\nCycle detected. Topological sorting is not possible.");

    printf("\n");
}

/* Main function */
int main()
{
    int e, u, v, i;

    printf("Enter number of vertices (1-%d): ", MAX);
    scanf("%d", &n);

    if(n < 1 || n > MAX)
    {
        printf("Invalid number of vertices!\n");
        return 1;
    }

    printf("Enter number of directed edges: ");
    scanf("%d", &e);

    if(e < 0 || e > n * (n - 1))
    {
        printf("Invalid number of edges!\n");
        return 1;
    }

    printf("Enter edges (u v), representing u -> v:\n");

    for(i = 0; i < e; i++)
    {
        if(scanf("%d %d", &u, &v) != 2)
        {
            printf("Invalid input!\n");
            return 1;
        }

        if(u < 0 || u >= n || v < 0 || v >= n ||
           u == v || graph[u][v])
        {
            printf("Invalid or duplicate edge!\n");
            return 1;
        }

        graph[u][v] = 1;
    }

    topologicalDFS();
    topologicalBFS();

    return 0;
}