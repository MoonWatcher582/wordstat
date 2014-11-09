#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "wordstat.h"

struct hash* masterhash;

int main(int argc, char **argv){
	char c;										/*next character*/
	char *str;									/*the developing word*/
	char *temp;									/*temp ptr for resizing*/
	int count = 0;								/*size of string*/
	int bufferSize = 128;						/*variable determining size of char array*/
	FILE *fp;									/*pointer to file to read-in*/	
	masterhash = calloc(sizeof(struct hash),1);	/*initialize the hash's mem*/	
	
	if(argv[1] == NULL){
		printf("Invalid number of arguments\n");
		return -1;
	}
	if(strcmp(argv[1], "-h") == 0){			/*check for "help" arg*/
		printf("Enter the name of a file to see how often a word is used, and how many variations it has.\n");
		return 0;
	}
	fp = fopen(argv[1], "r");				/*open the file*/
	if(fp == NULL){							/*Error if there is no file*/
		printf("Error Opening File\n");
		return -1;
	}
	c = fgetc(fp);							/*read in the first character*/
	str = malloc(bufferSize);				/*create char array*/

	while(c != EOF){						/*do while c is not at the end*/
		if(count == bufferSize){			/*if we've passed the size of the string*/
			temp = malloc(bufferSize);		/*allocate space for a temp storage*/
			strcpy(temp,str);				/*copy the string into the temp*/
			bufferSize *= 2;				/*increase buffersize*/
			str = realloc(str, bufferSize);	/*reallocate space for the larger char array*/
			strcpy(str, temp);				/*copy the string back from temp storage*/
			free(temp);						/*free temp mem*/
		}		
		if(isalpha(c)){						/*if you find the first character of a word*/
			while((isalnum(c)) && c != EOF){
				str[count] = c;				/*add it to the str of whatever size*/
				count++;					/*keep track of size/place in string*/
				c = fgetc(fp);				/*get next char*/
			}
			count++;						/*add an extra space for null byte*//* THIS MIGHT BE DONE ALREADY*/
			str[count] = '\0';				/*add null byte. string is now complete. whoo.*/
			/*printf("%s\n", str);*/
			processStr(str);				/*add the string to the data structure*/
			count = 0;						/*reset count so you can move through the str array again*/
			memset(&str[0], 0, sizeof(str));/*wipe string*/
		}else{
			c = fgetc(fp);					/*if you do not find a letter/digit, keep going*/
		}
	}
	free(str);
	fclose(fp);
	printResult();							/*print the stats*/
	/*free everything, prev, next*/
	return 0;								/*return successfully*/
}

/*
 *	This function will take the word and store
 *	it in proper data structures
 */
void processStr(char* str){
	insert(str);
	/*
	 *	Check to see if the word is already in the heap
	 *	if yes, incrememnt numOccur
	 *		check to see if that capitalization is in the array
	 *		if it is, break
	 *		if not, add to array, increment counter
	 *	if not, add to heap, initialize counters to 1
	 */
}

/*
 *	This function will produce the output of the program
 */
void printResult(){
	/*
	 *	Print out each node of the heap, Name, Count and ArrSize
	 */
	int i;
	struct stat* ptr;
	freeTable(1);
	printf("WORD\t\tTOTAL OCCURRENCES\tCASE SENSITIVE VERSIONS\n");
	for(i = 0; i < 26; i++){
		ptr = &(masterhash->table[i]);
		if(ptr == NULL || ptr->word == NULL){
			continue;
		}
		while(ptr != NULL){
			printf("%s\t\t%d\t\t\t%d\n", ptr->word,ptr->numOccur, ptr->varSize);
			ptr = ptr->next;
		}
	}	
	freeTable(0);
}

/*
 *	free the nodes
 */
void freeTable(int p){
	int i;
	struct stat* ptr;
	struct stat* prev;
	struct LLVarNode* curr;
	struct LLVarNode* pre; 
	if(p == 0){	
		for(i = 0; i < 26; i++){
			ptr = &(masterhash->table[i]);
			while(ptr != NULL){
				prev = ptr;
				ptr = ptr->next;
				free(prev->word);
			}
		}
	}else if(p == 1){
		for(i = 0; i < 26; i++){
			ptr = &(masterhash->table[i]);
			while(ptr != NULL){
				curr = ptr->head;
				while(curr != NULL){
					pre = curr;
					curr = curr->next;
					free(pre->wordVar);
					free(pre);
				}
				ptr = ptr->next;
			}
		}	
	}
}

/*
 *	creates a new stat node
 */
struct stat* newStat(char* str){
	struct stat* ws = malloc(sizeof(struct stat));
	ws->word = malloc(sizeof(str));
	strcpy(ws->word, str);
	lowerCase(ws->word);
	ws->numOccur = 1;
	ws->varSize = 1;
	ws->head = malloc(sizeof(struct LLVarNode));
	ws->head->wordVar = malloc(sizeof(str));
	strcpy(ws->head->wordVar, str);
	return ws;
}

int hashFunc(char* str){
	char c = str[0];
	if(c == 'a' || c == 'A'){
		return 0;
	}else if(c == 'b' || c == 'B'){
        return 1;
    }else if(c == 'c' || c == 'C'){
        return 2;
    }else if(c == 'd' || c == 'D'){
        return 3;
    }else if(c == 'e' || c == 'E'){
		return 4;
	}else if(c == 'f' || c == 'F'){
		return 5;
	}else if(c == 'g' || c == 'G'){
		return 6;
	}else if(c == 'h' || c == 'H'){
		return 7;
	}else if(c == 'i' || c == 'I'){
		return 8;
	}else if(c == 'j' || c == 'J'){
		return 9;
	}else if(c == 'k' || c == 'K'){
		return 10;
	}else if(c == 'l' || c == 'L'){
		return 11;
	}else if(c == 'm' || c == 'M'){
		return 12;
	}else if(c == 'n' || c == 'N'){
		return 13;
	}else if(c == 'o' || c == 'O'){
		return 14;
	}else if(c == 'p' || c == 'P'){
		return 15;
	}else if(c == 'q' || c == 'Q'){
		return 16;
	}else if(c == 'r' || c == 'R'){
		return 17;
	}else if(c == 's' || c == 'S'){
		return 18;
	}else if(c == 't' || c == 'T'){
		return 19;
	}else if(c == 'u' || c == 'U'){
		return 20;
	}else if(c == 'v' || c == 'V'){
		return 21;
	}else if(c == 'w' || c == 'W'){
		return 22;
	}else if(c == 'x' || c == 'X'){
		return 23;
	}else if(c == 'y' || c == 'Y'){
		return 24;
	}else if(c == 'z' || c == 'Z'){
		return 25;
	}else{
		return -1;
	}
}

void insert(char* str){
	int hf = hashFunc(str);							/*get the hash value for the string*/
	struct stat* currstr;
	struct stat* ptr;	
	struct stat* prev = NULL;								/*pointer to prev node*/
	struct LLVarNode* llptr;						/*pointer to the head of the variation ll*/
	struct stat temp;
	struct stat* temptr;
	/*printf("%d\n", hf);*/
	if(hf == -1){
		return;
	}
	currstr = search(str,hf);						/*find the stat for the current word*/
	ptr = &(masterhash->table[hf]);					/*pointer to the front of the LL at the correct hash slot*/
	if(currstr == NULL){							/*if the word is not in the hash table*/
		currstr = newStat(str);						/*create a new stat node*/
		while(ptr->word != NULL){					/*move through LL*/
			int cmp = strcasecmp(str, ptr->word);
			if(cmp > 0){							/*if str is lexigraphically LARGER than the current word*/
				prev = ptr;							/*set prev to ptr*/
				ptr = ptr->next;					/*advance ptr*/
				if(ptr == NULL){
					prev->next = currstr;
					break;
				}
			}else if(cmp < 0){						/*if str is smaller than current word*/
				currstr->next = ptr;				/*add currstr into list*/
				if(prev != NULL){
					prev->next = currstr;
				}
				if(prev == NULL){					/*if curr is the first word in the list*/
					temptr = newStat(ptr->word);
					temp = *temptr;
					temptr->numOccur = ptr->numOccur;	/*these values reset to the new head for temptr*/
					temptr->varSize = ptr->varSize;
					temptr->head = ptr->head;
					temptr->next = ptr->next;
					currstr->next = temptr;
					masterhash->table[hf] = *currstr;
				}
			
				break;								/*end loop*/
			}else{
				break;
			}
		}
		if(ptr != NULL){
			if(ptr->word == NULL){
				masterhash->table[hf] = *currstr;
			}  
		}
	}else{											/*if the word is in the table*/
		currstr->numOccur++;						/*increment the number of times it appears*/
		llptr = currstr->head;
		while(llptr != NULL){						/*move through variation LL*/
			/*printf("%s%s\n", str, llptr->wordVar);*/
			if(strcmp(str,llptr->wordVar) == 0){	/*if this variation already appeared, end the loop*/
				break;
			}
			llptr = llptr->next;
		}
		if(llptr == NULL){							/*if the ptr is null, meaning no equivalent was detected*/
			struct LLVarNode* newHead = malloc(sizeof(struct LLVarNode));
			newHead->wordVar = malloc(sizeof(str));
			strcpy(newHead->wordVar, str);			/*create a new node, copy the string into the node*/ 
			newHead->next = currstr->head;
			currstr->head = newHead;				/*set newHead as the head of the LL*/
			currstr->varSize++;						/*increment the number of variations*/
		}
	}
}

struct stat* search(char* str, int hf){
	struct stat* ptr = &(masterhash->table[hf]);	/*go to the start of the list at that hash function*/
	while(ptr->word != NULL){						/*loop through list*/	
		int cmp = strcasecmp(str,ptr->word);		/*compare the strings*/
		if(cmp == 0){								/*if a match is found*/
			return ptr;								/*return it*/
		}
		ptr = ptr->next;							/*increment ptr*/
		if(ptr == NULL){
			break;
		}
	}	
	return NULL;									/*return null if no match is found*/
}

char* lowerCase(char* str){
	int i;
	for(i = 0; i < strlen(str); i++){
		str[i] = tolower(str[i]);
	}
	return str;
}
