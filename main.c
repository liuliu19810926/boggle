/*
 ============================================================================
 Name        : main.c
 Author      : liuliu
 Version     :
 Copyright   : 
 Description : boggle in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define ROW	4
#define COL	4

typedef struct
{
	char array[(ROW * COL + 1)];	// 1 more element for string terminator
	int pos;
} string;

// Function prototypes
bool isWord(char *array, char *word);
void findWordsUtil(char boggle[ROW][COL], bool visited[ROW][COL], int i,
                   int j, string *str, char *word);
void findWords(char boggle[ROW][COL], char *word);
void clearVisited(int row, int col, bool vist[ROW][COL]);
void initString(string *str);
bool appendStringChar(string *str, char ch);
bool deleteStringChar(string *str);

// This Boggle algorithm is based on the C++ code from following website:
// http://www.geeksforgeeks.org/boggle-find-possible-words-board-characters/

// A given function to check if a word is present
bool isWord(char* array, char *word)
{
	if(!strcmp(array, word))
	{
		return true;
	}
	return false;
}

// A recursive function to print all words present on boggle
void findWordsUtil(char boggle[ROW][COL], bool visited[ROW][COL], int i,
                   int j, string *str, char *word)
{
	int row, col;
	char ch;

    // Mark current cell as visited and append current character
    // to str
	visited[i][j] = true;
	ch = boggle[i][j];
	appendStringChar(str, ch);

    // If str is present in dictionary, then print it
	if(isWord(str->array, word))
	{
		printf("%s\n", str->array);
	}

    // Traverse 8 adjacent cells of boggle[i][j]
    for (row = i - 1; row <= i + 1 && row < ROW; row++)
    {
    	for (col = j - 1; col <= j + 1 && col < COL; col++)
    	{
    		if (row >= 0 && col >= 0 && !visited[row][col])
    		{
    			findWordsUtil(boggle, visited, row, col, str, word);
    		}
    	}
    }

    // Erase current character from string and mark visited
    // of current cell as false
    deleteStringChar(str);
    visited[i][j] = false;
}

// Prints all words present in dictionary.
void findWords(char boggle[ROW][COL], char *word)
{
	int i, j;
    bool visited[ROW][COL];
    string str;

    // Mark all characters as not visited
    clearVisited(ROW, COL, visited);

    // Initialize current string
    initString(&str);

    // Consider every character and look for all words
    // starting with this character
    for (i = 0; i < ROW; i++)
    {
    	for (j = 0; j < COL; j++)
    	{
    		findWordsUtil(boggle, visited, i, j, &str, word);
    	}
    }
}

// Clear visited flags
void clearVisited(int row, int col, bool vist[ROW][COL])
{
	int i, j;

	for(i = 0; i < ROW; i++)
	{
		for(j = 0; j < COL; j++)
		{
			vist[i][j] = false;
		}
	}
}

// Initialize string
void initString(string *str)
{
	memset((str->array), '\0', sizeof(str->array));
	str->pos = 0;
}

// Append a char to string
bool appendStringChar(string *str, char ch)
{
	if(str->pos < sizeof(str->array))
	{
		*(str->array + str->pos) = ch;
		(str->pos)++;
		return true;
	}
	return false;
}

// Delete last char from string
bool deleteStringChar(string *str)
{
	int temp;

	temp = str->pos;
	if(--temp >= 0)
	{
		*(str->array + temp) = '\0';
		str->pos = temp;
		return true;
	}
	return false;
}

// Driver program to test above function
int main()
{
	FILE *f;
	int length;
	char word[ROW * COL + 1];

//    char boggle[ROW][COL] = {{'G','I','Z'},
//                         	 {'U','E','K'},
//                         	 {'Q','S','E'}};

	char boggle[ROW][COL] = {{'a', 'b', 'a', 'n'},
							 {'z', 'q', 'z', 'd'},
							 {'r', 'r', 'o', 'r'},
							 {'r', 'n', 'r', 'r'}};

//	char boggle[ROW][COL] = {{'z', 'z', 'z', 'z'},
//							 {'z', 'z', 'b', 'z'},
//							 {'h', 'z', 'e', 'z'},
//							 {'a', 'z', 'z', 'z'}};


    memset(word, '\0', sizeof(word));
//    strcpy(word, "abandon");
//    findWords(boggle, word);

    // Please note that it could take a very long time to search through the "word.list" file
    f = fopen("word.list", "r+");
    if(f != NULL)
    {
    	printf("Start to search \"word.list\"...\n");
		while(fgets(word, sizeof(word), f))
		{
			// Replace line-feed with string terminator
			length = strlen(word);
			if(*(word + length - 1) == '\n')
				*(word + length - 1) = '\0';

			// Find word
			findWords(boggle, word);
		}
		fclose(f);
		printf("Search finished\n");
    }
    else
    {
    	printf("Failed to open \"word.list\"\n");
    }

    return 0;
}
