#include <stdio.h>
#include <stdlib.h>
#define M 4 /* order of the B-Tree */
typedef struct BTreeNode
{
int keys[M - 1];
struct BTreeNode *child[M];
int n; /* number of keys */
int leaf; /* 1 if leaf */
} BTreeNode;
BTreeNode *root = NULL;
BTreeNode *createNode(int leaf)
{
BTreeNode *t = (BTreeNode *)calloc(1, sizeof(BTreeNode));
t->leaf = leaf;
return t;
}
/* split the full child parent->child[i] */
void splitChild(BTreeNode *parent, int i)
{
BTreeNode *y = parent->child[i];
BTreeNode *z = createNode(y->leaf);
int mid = (M - 1) / 2, j;
z->n = M - 2 - mid;
for (j = 0; j < z->n; j++)
z->keys[j] = y->keys[mid + 1 + j];
if (!y->leaf)
for (j = 0; j <= z->n; j++)
z->child[j] = y->child[mid + 1 + j];
y->n = mid;

for (j = parent->n; j > i; j--)
{
parent->child[j + 1] = parent->child[j];
parent->keys[j] = parent->keys[j - 1];
}
parent->child[i + 1] = z;
parent->keys[i] = y->keys[mid];
parent->n++;
}
void insertNonFull(BTreeNode *x, int key)
{
int i = x->n - 1;
if (x->leaf)
{
while (i >= 0 && key < x->keys[i])
{
x->keys[i + 1] = x->keys[i];
i--;
}
x->keys[i + 1] = key;
x->n++;
}
else
{
while (i >= 0 && key < x->keys[i])
i--;
i++;
if (x->child[i]->n == M - 1)
{
splitChild(x, i);
if (key > x->keys[i])
i++;
}
insertNonFull(x->child[i], key);
}

}
void insert(int key)
{
if (root == NULL)
{
root = createNode(1);
root->keys[0] = key;
root->n = 1;
return;
}
if (root->n == M - 1)
{
BTreeNode *s = createNode(0);
s->child[0] = root;
root = s;
splitChild(s, 0);
}
insertNonFull(root, key);
}
void traverse(BTreeNode *x)
{
int i;
if (x == NULL)
return;
for (i = 0; i < x->n; i++)
{
if (!x->leaf)
traverse(x->child[i]);
printf("%d ", x->keys[i]);
}
if (!x->leaf)
traverse(x->child[i]);
}
int main()
{

int choice, key;
while (1)
{
printf("\n1. Insert\n2. Traversal\n3. Exit\n");
printf("Enter your choice: ");
scanf("%d", &choice);
switch (choice)
{
case 1:
printf("Enter key: ");
scanf("%d", &key);
insert(key);
break;
case 2:
printf("B-Tree traversal: ");
traverse(root);
printf("\n");
break;
case 3:
return 0;
default:
printf("Invalid choice.\n");
}
}
}
