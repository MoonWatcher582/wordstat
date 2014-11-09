#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
 
/*
 *  linked list struct used to hold word variations
 */
struct LLVarNode{
	char* wordVar;              /*node holds variation of a word*/
	struct LLVarNode* next;     /*ptr to next node*/
};

/*
 *  struct used to hold information about each word
 */
struct stat{
	int varSize;                /*the number of different variations of the word*/
	int numOccur;               /*the total number of occurrences of the word*/
	char *word;                 /*the word itself*/
	struct LLVarNode* head;     /*LLNode containing the different variations of the word, make this a linked list*/
	struct stat* next;          /*ptr to next node for hash collisions*/
};

/*simple hash table*/
struct hash{
	struct stat table[26];
};

/*
 *  hash table functions
 */
int hashFunc(char*);            /*the hash function*/
void insert(char*);             /*insert an element into the table*/
struct stat* search(char*, int);/*find and return a stat*/
 
/*
 *  main's functions
 */
void processStr(char*);         /*put the string in the data structure*/
void printResult(void);         /*print all the words and counters*/
char* lowerCase(char*);         /*set a word to lower case*/
void freeTable(int);

