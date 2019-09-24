// Sean Szumlanski
// COP 3502, Fall 2017

// =============================
// TriePrediction: unit_test05.c
// =============================
// Tests the functionality of mostFrequentWord().


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TriePrediction.h"


void failwhale(char *err_msg)
{
	printf("fail whale :( --- %s\n", err_msg);
	exit(0);
}

// This acts as the main() function for this test case.
int unit_test(int argc, char **argv)
{
	TrieNode *root, *result, *solution;
	char str[MAX_CHARACTERS_PER_WORD + 1];

	// Ensure str is not initialized to the empty string, to test that
	// mostFrequentWord() works with strings that contain garbage data.
	str[0] = 'x';

	// Load a trie in which there is only one string with the most frequent
	// count ("pie").
	root = buildTrie("corpus03.txt");
	getMostFrequentWord(root, str);
	if (strcmp(str, "pie") != 0)
		failwhale("fails on corpus03.txt; should have found \"pie\"");
	root = destroyTrie(root);

	// Load a trie in which there are multiple strings with the most frequent
	// count ("i", "like", and "pie").
	root = buildTrie("corpus01.txt");
	getMostFrequentWord(root, str);
	if (strcmp(str, "i") != 0)
		failwhale("fails on corpus01.txt; should have found \"i\"");
	root = destroyTrie(root);

	// Test mostFrequentWord on an empty tree.
	root = NULL;
	getMostFrequentWord(root, str);
	if (strcmp(str, "") != 0)
		failwhale("fails on empty tree; should have returned NULL");

	printf("Success!\n");

	return 0;
}
