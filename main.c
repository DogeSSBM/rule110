#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "GetInt.h"

typedef unsigned int uint;

uint loops = 60;
uint len = 30;
char* cells = NULL;
char* next = NULL;

void randomize(void)
{
	for(uint i = 0; i < len; i++){
		next[i] = '_';
		cells[i] = rand() & 0b1 ? '#' : '_';
	}
}

void print(void)
{
	for(uint i = 0; i < len; i++){
		printf("%c", cells[i]);
	}
	printf("\n");
}

uint wrap(int i)
{
	if(i < 0)
		return len+i;
	if(i >= len)
		return i-len;
	return i;
}

char eval(char *group)
{
	static const char liveSet[5][4] = {"110","101","011","010","001"};
	for(uint i = 0; i < 5; i++){
		if(strcmp(group, liveSet[i]) == 0)
			return '#';
	}
	return '_';
}

void evolve(void)
{
	for(uint i = 0; i < len; i++){
		char group[4];
		group[0]=cells[wrap(i-1)];
		group[1]=cells[i];
		group[2]=cells[wrap(i+1)];
		group[3]='\0';
		next[i] = eval(group);
	}
	memcpy(cells, next, sizeof(char)*len);
}

int main(int argc, char const *argv[])
{
	srand(time(NULL));
	if(argc == 3){
		len = strToInt(argv[1]);
		loops = strToInt(argv[2]);
	}
	cells = malloc(sizeof(char) * len);
	next = malloc(sizeof(char) * len);
	randomize();
	for(uint i = 0; i < loops; i++){
		print();
		evolve();
	}
	free(cells);
	free(next);
	return 0;
}
