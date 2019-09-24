// This template is included to help get you started. I've written some trie
// printing functions for you, which are included below. Please be sure to delete
// this comment and add your name to this source file.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TriePrediction.h"


// Helper function called by printTrie(). (Credit: Dr. S.)
void printTrieHelper(TrieNode *root, char *buffer, int k)
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

		printTrieHelper(root->children[i], buffer, k + 1);
	}

	buffer[k] = '\0';
}

// If printing a subtrie, the second parameter should be 1; otherwise, if
// printing the main trie, the second parameter should be 0. (Credit: Dr. S.)
void printTrie(TrieNode *root, int useSubtrieFormatting)
{
	char buffer[1026];

	if (useSubtrieFormatting)
	{
		strcpy(buffer, "- ");
		printTrieHelper(root, buffer, 2);
	}
	else
	{
		strcpy(buffer, "");
		printTrieHelper(root, buffer, 0);
	}
}

TrieNode *buildTrie(char *filename)
{
	return NULL;
}

int processInputFile(TrieNode *root, char *filename)
{
	return 0;
}

TrieNode *destroyTrie(TrieNode *root)
{
	return NULL;
}

TrieNode *getNode(TrieNode *root, char *str)
{
	return NULL;
}

void getMostFrequentWord(TrieNode *root, char *str)
{
}

int containsWord(TrieNode *root, char *str)
{
	return 0;
}

int prefixCount(TrieNode *root, char *str)
{
	return 0;
}

double difficultyRating(void)
{
	return -1.0;
}

double hoursSpent(void)
{
	return -1.0;
}

int main(int argc, char **argv)
{
	return 0;
}
