// Sean Szumlanski
// COP 3502, Fall 2017

// =============================
// TriePrediction: unit_test03.c
// =============================
// Calls my own (unmodified) version of printTrie(), which helps ensure that the
// structure of your trie is as expected.


#include <stdio.h>
#include <string.h>
#include "TriePrediction.h"

// Helper function called by printTrie()
void localPrintTrieHelper(TrieNode *root, char *buffer, int k)
{
	int i;

	if (root == NULL)
		return;

	if (root->count > 0)
		printf("%s (%d)\n", buffer, root->count);

	buffer[k + 1] = '\0';

	for (i = 0; i < 26; i++)
	{
		buffer[k] = 'a' + i;

		localPrintTrieHelper(root->children[i], buffer, k + 1);
	}

	buffer[k] = '\0';
}

// If printing a subtrie, the second parameter should be 1; otherwise, if
// printing the main trie, the second parameter should be 0.
void localPrintTrie(TrieNode *root, int useSubtrieFormatting)
{
	char buffer[1026];

	if (useSubtrieFormatting)
	{
		strcpy(buffer, "- ");
		localPrintTrieHelper(root, buffer, 2);
	}
	else
	{
		strcpy(buffer, "");
		localPrintTrieHelper(root, buffer, 0);
	}
}

// This acts as the main() function for this test case.
int unit_test(int argc, char **argv)
{
	TrieNode *root = buildTrie("corpus01.txt");
	localPrintTrie(root, 0);

	root = destroyTrie(root);

	return 0;
}
