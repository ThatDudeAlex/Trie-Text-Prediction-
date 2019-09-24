// Sean Szumlanski
// COP 3502, Fall 2017

// =============================
// TriePrediction: unit_test07.c
// =============================
// Tests the functionality of prefixCount().


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
	root = buildTrie("corpus01.txt");

	if (prefixCount(root, "") != 10)
		failwhale("fails with empty string as prefix");

	if (prefixCount(root, "ch") != 2)
		failwhale("fails with \"ch\" as prefix");

	if (prefixCount(root, "really") != 1)
		failwhale("fails with \"really\" as prefix");

	if (prefixCount(root, "realism") != 0)
		failwhale("fails with \"realism\" as prefix");

	root = destroyTrie(root);

	printf("Success!\n");

	return 0;
}
