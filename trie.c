#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

/* Trie Node */
typedef struct TrieNode
{
struct TrieNode *children[ALPHABET_SIZE];
int isEndOfWord;
} TrieNode;

/* Create a new Trie node */
TrieNode *createNode()
{
TrieNode *newNode = (TrieNode *)malloc(sizeof(TrieNode));

newNode->isEndOfWord = 0;

for (int i = 0; i < ALPHABET_SIZE; i++)
newNode->children[i] = NULL;

return newNode;
}

/* Insert a word into Trie */
void insert(TrieNode *root, char word[])
{
TrieNode *current = root;

for (int i = 0; word[i] != '\0'; i++)
{
int index = word[i] - 'a';

if (current->children[index] == NULL)
current->children[index] = createNode();

current = current->children[index];
}

current->isEndOfWord = 1;

printf("Word inserted successfully.\n");
}

/* Search for a complete word */
int search(TrieNode *root, char word[])
{
TrieNode *current = root;

for (int i = 0; word[i] != '\0'; i++)
{
int index = word[i] - 'a';

if (current->children[index] == NULL)
return 0;

current = current->children[index];
}

return current->isEndOfWord;
}

/* Display words recursively */
void displayWords(TrieNode *root, char word[], int depth)
{
if (root->isEndOfWord)
{
word[depth] = '\0';
printf("%s\n", word);
}

for (int i = 0; i < ALPHABET_SIZE; i++)
{
if (root->children[i] != NULL)
{
word[depth] = 'a' + i;
displayWords(root->children[i], word, depth + 1);
}
}
}

/* Autocomplete */
void autocomplete(TrieNode *root, char prefix[])
{
TrieNode *current = root;

/* Move through the Trie according to prefix */
for (int i = 0; prefix[i] != '\0'; i++)
{
int index = prefix[i] - 'a';

if (current->children[index] == NULL)
{
printf("No words found with prefix \"%s\".\n", prefix);
return;
}

current = current->children[index];
}

char word[100];

strcpy(word, prefix);

printf("Words starting with \"%s\":\n", prefix);

displayWords(current, word, strlen(prefix));
}

/* Main function */
int main()
{
TrieNode *root = createNode();

int choice;
char word[100];

while (1)
{
printf("\n\n==============================\n");
printf(" TRIE\n");

printf("==============================\n");
printf("1. Insert Word\n");
printf("2. Search Word\n");
printf("3. Autocomplete\n");
printf("4. Display All Words\n");
printf("5. Exit\n");
printf("==============================\n");

printf("Enter your choice: ");
scanf("%d", &choice);

switch (choice)
{
case 1:

printf("Enter word: ");
scanf("%s", word);

for (int i = 0; word[i] != '\0'; i++)
word[i] = tolower(word[i]);

insert(root, word);
break;

case 2:

printf("Enter word to search: ");
scanf("%s", word);

for (int i = 0; word[i] != '\0'; i++)
word[i] = tolower(word[i]);

if (search(root, word))
printf("Word found.\n");
else
printf("Word not found.\n");

break;

case 3:

printf("Enter prefix: ");
scanf("%s", word);

for (int i = 0; word[i] != '\0'; i++)
word[i] = tolower(word[i]);

autocomplete(root, word);
break;

case 4:
{
char result[100];

printf("\nAll words in Trie:\n");
displayWords(root, result, 0);

break;
}

case 5:

printf("Program terminated.\n");
return 0;

default:

printf("Invalid choice.\n");
}
}

return 0;
}