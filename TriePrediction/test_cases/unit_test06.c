// Sean Szumlanski
// COP 3502, Fall 2017

// =============================
// TriePrediction: unit_test06.c
// =============================
// Tests the functionality of containsWord().


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
	root = buildTrie("corpus05.txt");

	// This should succeed; "robot" should be in the trie.
	if (!containsWord(root, "robot"))
		failwhale("fails when searching for 'robot'");

	// This should return NULL; "power" is the prefix of a word in the trie,
	// but it is not a string that is actually represented in the trie.
	if (containsWord(root, "power"))
		failwhale("fails when searching for 'power'");

	// This should return NULL; "gold" is nowhere in the trie.
	if (containsWord(root, "gold"))
		failwhale("fails when searching for 'gold'");

	root = destroyTrie(root);

	printf("Success!\n");

	return 0;
}
