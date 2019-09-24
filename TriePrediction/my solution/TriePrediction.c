// Jose Nunez
// NID: jo695150

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "TriePrediction.h"

TrieNode *createTriNode(void);
TrieNode *insertString(TrieNode *root, char *str);
int prefixCountHelper(TrieNode *root, int numberOfStrings);
int getMostFrequentWordHelper(TrieNode *root, char *tempstr, char *str, int count, int index);
void stripPunctuators(char *str);

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

// allocates memory for a new node and set everything to NULL
TrieNode *createTriNode(void)
{
	return calloc(1, sizeof(TrieNode));
}

// Insert a string into a trie. This function returns the last node of the string inserted.
TrieNode *insertString(TrieNode *root, char *str)
{
	int i, index, len = strlen(str);
	TrieNode *wizard;

	if (root == NULL)
		root = createTriNode();

	wizard = root;

	for (i = 0; i < len; i++)
	{
		index = tolower(str[i]) - 'a';

		// Before the wizard can move forward to the next node
		// make sure that node actually exists. If not, create it!
		if (wizard->children[index] == NULL)
			wizard->children[index] = createTriNode();

		// Now the wizard is able to jump forward.
		wizard = wizard->children[index];
	}

	// wizard should be at the terminal node that represents the string we're
	// trying to insert. increase its count, and return the terminal node.
	wizard->count++;
	return wizard;
}

// remove any non-alphabetic character from the string passed in.
void stripPunctuators(char *str)
{
	int i, j = 0;
	int len = strlen(str);
	char *nonPunctionStr = calloc(len + 1 , sizeof(char));

	// checks every spot in the inserted string, and only copy alphabetic characters
	// into the nonPunction string.
	for(i = 0; i < len; i++)
	{
		if (isalpha(str[i]))
		{
			nonPunctionStr[j] = str[i];
			j++;
		}
	}

	// copy the new string into the original, and free any allocated memory.
	strcpy(str, nonPunctionStr);
	free(nonPunctionStr);
}

// opens and reads filename, and create create a trie
// including all its appropriate subtries
TrieNode *buildTrie(char *filename)
{
	// creates the main root of the trie being created.
	TrieNode *root = createTriNode();
  TrieNode *previousRoot = NULL;
	TrieNode *currentRoot = NULL;
	char buffer[MAX_CHARACTERS_PER_WORD + 1];
	int length = 0, endOfSentence = 0;
	FILE *ifp;

	// checks to see if the file exits, and if not just return NULL
	if ((ifp = fopen(filename, "r")) == NULL)
	{
		fprintf(stderr, "Failed to open \"%s\" in buildTrie().\n", filename);
		return NULL;
	}

	// while loop that keeps reading till the end of the file
	while (fscanf(ifp, "%s", buffer) != EOF)
	{
		length = strlen(buffer);

		// checks to see if the last character in the string is a '!', '.', or '?' since those
		// mark the end of a sentence, so set endOfSentence to 1.
		if(buffer[length - 1] == '.' || buffer[length - 1] == '!' || buffer[length - 1] == '?')
			endOfSentence = 1;

		// remove any puntuations that the string might have, and insert it into the
		// trie. after inserting currentRoot recieves the terminal node of the string
		stripPunctuators(buffer);
		currentRoot = insertString(root, buffer);

		// checks to see if there was a previous word read in
		if(previousRoot != NULL)
		{
			// create a subtrie for the previous word if it doesnt exit
			if(previousRoot->subtrie == NULL)
				previousRoot->subtrie = createTriNode();
			// insert the current word into the subtrie of the previous
			insertString(previousRoot->subtrie, buffer);
		}

		// if endOfSentence is 1, we reset the previousRoot to NULL and endOfSentence
		// back to 0. Else previousRoot become the currentRoot
		if(endOfSentence == 1)
		{
			previousRoot = NULL;
			endOfSentence = 0;
		}
		else
			previousRoot = currentRoot;

	}

	fclose(ifp);
	return root;
}

// This function takes in the root of a trie and the name of an input file, and
// processes that file according to the description in the pdf. returns 1 if
// file doesnt exists, 0 otherwise.
int processInputFile(TrieNode *root, char *filename)
{
	int i, j;
	TrieNode *wizard = root;
	char buffer[MAX_CHARACTERS_PER_WORD + 1];
	char buffer2[MAX_CHARACTERS_PER_WORD + 1];
	FILE *ifp;

	// if file does not exits return 1
	if ((ifp = fopen(filename, "r")) == NULL)
	{
		return 1;
	}

	// while loop that reads till end of file
	while (fscanf(ifp, "%s", buffer) != EOF)
	{
		if(buffer[0] == '@')
		{
			// reads the next two strings, and converts the second one into an int
			// so we now the number of iterations to take in our for loop
			fscanf(ifp, "%s", buffer);
			fscanf(ifp, "%s", buffer2);
			j = atoi(buffer2);

			// if the word read is not in the trie, then just print it and return 0
			if(!containsWord(root, buffer))
			{
				printf("%s\n",buffer);
				fclose(ifp);
				return 0;
			}

			printf("%s", buffer);
			// run till the specified number of iterations that was read in
			for(i = 0; i < j; i++ )
			{
				// get the terminal node of the string
				wizard = getNode(root,buffer);

				// if the string has a subtrie, get the most frequent string in it, and
				// update buffer into the most frequent string
				if(wizard->subtrie != NULL)
				{
					getMostFrequentWord(wizard->subtrie, buffer);
					printf(" %s", buffer);
					printf("%s", i == (j - 1) ? "\n" : "" );
				}
				// if the string has no subtrie, then return 0 and terminate early
				else
				{
					printf("\n");
					fclose(ifp);
					return 0;
				}

			}
		}
		else if(buffer[0] == '!')
		{
			printTrie(root,0);
		}
		else
		{
			// checks to see if the string is in the trie, and if so get its terminal node
			if(containsWord(root, buffer))
			{
				wizard = getNode(root, buffer);
				// if the string has no subtries just print the string and "(EMPTY)"
				if(wizard->subtrie == NULL)
				{
					printf("%s\n",buffer);
					printf("(EMPTY)\n");
				}
				// else if it does, print the string and its subtries
				else
				{
					printf("%s\n",buffer);
					printTrie(wizard->subtrie, 1);
				}
			}
			// if the string is not in the trie, just print the string and "(INVALID STRING)"
			else
			{
				printf("%s\n",buffer);
				printf("(INVALID STRING)\n");
			}

		}
	}

	fclose(ifp);
	return 0;
}

// Frees all dynamically allocated memory associated with this trie.
TrieNode *destroyTrie(TrieNode *root)
{
	int i;

	if(root == NULL)
		return NULL;

	// recursively goes to the end of each string inserted in the trie
	for(i = 0; i < 26; i++)
	{
		if(root->children[i] != NULL)
			destroyTrie(root->children[i]);
	}

	// once it gets to the end of a string, checks to see if it has a subtrie
	// and if so recursively goes to the end of each string in the subtrie
	if(root->subtrie != NULL)
		destroyTrie(root->subtrie);

	// frees any memory once we see there's no more children or subtries
	free(root);
	return root = NULL;
}

// recieves a root and string, and Searches the trie for the specified string
// if string is in the trie, return it terminal node.
TrieNode *getNode(TrieNode *root, char *str)
{
	int i, index, len;
	TrieNode *wizard;

	if (root == NULL || str == NULL)
		return NULL;

	len = strlen(str);
	wizard = root;

	// checks to see if the string is represented in the trie, if it see it's not
	// just return NULL
	for (i = 0; i < len; i++)
	{
		index = tolower(str[i]) - 'a';

		if (wizard->children[index] != NULL)
			wizard = wizard->children[index];
		else
			return NULL;
	}

	if(wizard->count >= 1)
		return	wizard;
	else
		return NULL;
}

// searches trie for most frequently occurring word and copies it into the string
void getMostFrequentWord(TrieNode *root, char *str)
{
	int count = 0, index = 0;
	char *tempStr = malloc(MAX_CHARACTERS_PER_WORD *sizeof(char) + 1);;

	// if trie is empty, copy in the empty string, else calls Helper function,
	if(root == NULL)
		strcpy(str,"");
	else
		getMostFrequentWordHelper(root, tempStr, str, count, index);

  free(tempStr);
}

// use to help getMostFrequentWord, by recursively going through the trie
// returns the count of the most frequent Word
int getMostFrequentWordHelper(TrieNode *root, char *tempstr, char *str, int count, int index)
{
	int i;

	if(root == NULL)
		return 0;

	// if root->count is higher than our count tracker, make that string our current
	// most frequent, and update the count tracker.
	if(root->count > count)
	{
		count = root->count;
		strcpy(str, tempstr);
	}

	for(i = 0; i < 26; i++)
	{
		// recursively goes through each string in the trie and updates the count when
		// it returns
		if(root->children[i] != NULL)
		{
			tempstr[index] = i + 'a';
			count = getMostFrequentWordHelper(root->children[i], tempstr, str, count, index + 1);
		}
		// adds terminator character to the end our tempStr
		tempstr[index] = '\0';
	}

	return count;
}

// Searches the trie for the specified string, returns 1 if the string is
// is represented in the trie, return 0
int containsWord(TrieNode *root, char *str)
{
	int i, index, len = strlen(str);
	TrieNode *wizard;

	if (root == NULL || str == NULL)
		return 0;

	wizard = root;

	// checks to see if the string is represented in the trie, if it see it's not
	// just return 0
	for (i = 0; i < len; i++)
	{
		index = tolower(str[i]) - 'a';

		if (wizard->children[index] != NULL)
			wizard = wizard->children[index];
		else
			return 0;
	}

	// checks to see if str is a word represented in the trie
	if(wizard->count >= 1)
		return	1;
	else
		return 0;
}

// returnsThe number of strings in the trie that begin with the specified string
int prefixCount(TrieNode *root, char *str)
{

	int i, index = 0, count = 0, numberOfStrings = 0, len = strlen(str);
	TrieNode *wizard;

	if (root == NULL || str == NULL)
		return 0;

	wizard = root;

	// checks to see if the string is represented in the trie, if it see it's not
	// just return 0
	for (i = 0; i < len; i++)
	{
		index = tolower(str[i]) - 'a';

		if (wizard->children[index] != NULL)
			wizard = wizard->children[index];
		else
			return 0;
	}

	// once the terminal node of the string is found, call helper function and
	// pass in terminal node as the root, and numberOfStrings
	numberOfStrings = prefixCountHelper(wizard, numberOfStrings);
	return numberOfStrings;
}

// recursively goes through the trie starting at the node being passed in as the
// root and count the number of string found and returns it
int prefixCountHelper(TrieNode *root, int numberOfStrings)
{
	int i;

	if(root == NULL)
		return 0;

	// incriment numberOfStrings by the root->count
	numberOfStrings += root->count;

	// recursively goes through each string in the trie and updates the count when
	// it returns
	for(i = 0; i < 26; i++)
	{
		if(root->children[i] != NULL)
			numberOfStrings = prefixCountHelper(root->children[i], numberOfStrings);
	}

	return numberOfStrings;
}

double difficultyRating(void)
{
	return 4.5;
}

double hoursSpent(void)
{
	return 30.0;
}

int main(int argc, char **argv)
{
	char *corpusFile = argv[1];
	char *inputFile = argv[2];

	TrieNode *root = buildTrie(corpusFile);
	processInputFile(root, inputFile);
	root = destroyTrie(root);

	return 0;
}
