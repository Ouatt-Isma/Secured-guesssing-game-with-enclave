#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "guessing_game_t.h"


// Global variables

int NUMBER_TO_GUESS=-1;
int maxnum = -1; 
int cpt = 0; 

//Function to generate the seedd
int generate_seed(){
	return 11*time(NULL)+7; 
}

//Function to generate an integer
int generate_integer(){
	srand(generate_seed()); 
	return rand()%256; 
	//return 2; 
}

//Function to get the max value of tentative from the host
void enc_get_maxnum(int res){
	 maxnum = res; 
	 return; 

}

//Function to compare the entered value and the generated random value
void enc_compare(int a, int* res){
	cpt++; 
	if (NUMBER_TO_GUESS==-1){
		NUMBER_TO_GUESS=generate_integer();

	}
	if (maxnum<cpt){
		 fprintf(stderr, "Enclave autolock because %d(max value)<%d(number of tentative)\n", maxnum, cpt);
		//exit(1);
		oe_abort(); 
	}
	*res = a==NUMBER_TO_GUESS;
	return; 

}


