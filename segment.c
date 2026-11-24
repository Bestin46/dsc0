#include <stdio.h>

#define MAX 100

int arr[MAX], sumTree[4 * MAX], minTree[4 * MAX];
int n;

/* Build segment tree */
void build(int node, int start, int end) {
    if (start == end) {
        sumTree[node] = minTree[node] = arr[start];
        return;
    }

    int mid = (start + end) / 2;

    build(2 * node, start, mid);
    build(2 * node + 1, mid + 1, end);

    sumTree[node] = sumTree[2 * node] + sumTree[2 * node + 1];

    minTree[node] = (minTree[2 * node] < minTree[2 * node + 1])
                    ? minTree[2 * node] : minTree[2 * node + 1];
}

/* Range sum query */
int rangeSum(int node, int start, int end, int l, int r) {
    if (r < start || end < l)
        return 0;

    if (l <= start && end <= r)
        return sumTree[node];

    int mid = (start + end) / 2;

    return rangeSum(2 * node, start, mid, l, r)
         + rangeSum(2 * node + 1, mid + 1, end, l, r);
}

/* Range minimum query */
int rangeMin(int node, int start, int end, int l, int r) {
    if (r < start || end < l)
        return 2147483647;

    if (l <= start && end <= r)
        return minTree[node];

    int mid = (start + end) / 2;

    int a = rangeMin(2 * node, start, mid, l, r);
    int b = rangeMin(2 * node + 1, mid + 1, end, l, r);

    return (a < b) ? a : b;
}

int main() {
    int i, l, r, choice;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    if (n < 1 || n > MAX) {
        printf("Invalid size!\n");
        return 1;
    }

    printf("Enter array elements:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    build(1, 0, n - 1);

    do {
        printf("\n1. Range Sum\n2. Range Minimum\n3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1 || choice == 2) {
            printf("Enter range (l r): ");
            scanf("%d %d", &l, &r);

            if (l < 0 || r >= n || l > r) {
                printf("Invalid range!\n");
            } else if (choice == 1) {
                printf("Range Sum = %d\n",
                       rangeSum(1, 0, n - 1, l, r));
            } else {
                printf("Range Minimum = %d\n",
                       rangeMin(1, 0, n - 1, l, r));
            }
        } else if (choice != 3) {
            printf("Invalid choice!\n");
        }

    } while (choice != 3);

    return 0;
}