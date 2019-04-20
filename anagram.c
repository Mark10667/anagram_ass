#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

int compare(const void*a, const void*b){
	return *(char*)a-*(char*)b;
}

void print_value(VNode** head){
	VNode* current = *head;
	VNode* tem = current;
	while(tem!=NULL){
		current = current->next;
		printf("%s ", tem->value);
		tem = current;
	}
}

int main (int argc, char ** argv) {
	static DNode* dictionary [DEFAULT_HASH_SIZE];

	FILE* f = fopen("words.txt", "r");
	if(f == NULL){
		printf("Error opening file. \n");
		return 1;
	}
	char s[100];
	while(fscanf(f, "%s", s)!=EOF){
		char a[100];
		strcpy(a, s);
		qsort(s, strlen(s), sizeof(char), compare);
		set(dictionary, DEFAULT_HASH_SIZE, s, a);
	}
	fclose(f);

	// print process
	int count = 0;
	for(int i=0; i<DEFAULT_HASH_SIZE; i++){
		if(dictionary[i]!=NULL){
			//puts("\nNext Hash position:");
			DNode* head = dictionary[i];
			DNode* current = NULL;
			current = head;
			while(current != NULL){
				DNode* tem = current;
				current = current->next;
					if(tem->key != NULL){
						if(((tem->values)->next) != NULL){
							//printf("Key is %s:\n", tem->key);
							count++;
							print_value(&(tem->values));
							puts("\n");
						}
					}
			}
		}
	}

	printf("The total number of anagram is %d\n", count);
	free_dictionary(dictionary, DEFAULT_HASH_SIZE);


	return 0;
}
