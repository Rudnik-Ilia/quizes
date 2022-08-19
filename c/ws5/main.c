/**********************
* Title : Worksheet 5 
* Author: Ilia Rudnik
* Reviewer: mariia
* Date : 20/08/2022
***********************/

#include"ws5.h"
#define UNUSED(x) (void)x

int main(int argc, char *argv[], char *env[])
{	
	
	/*
		Run the program: ./a.out [name.txt],
		
		command for program:
							-remove  -removing [name.txt] if exists.
							-count   -counting lines in [name.txt] .
							<[text]  -adding text after '<' to beginig of file.
							-exit    -exit from program.
							
							typing text without command is adding text to end of file.
	*/
	
	
	logger(argv);

UNUSED(argc);
UNUSED(env);
return 0;
}

