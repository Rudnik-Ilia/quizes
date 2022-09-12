#ifndef __WS8_H__
#define __WS8_H__


#define LEN_OF_ARR 3
#define MAX2(a,b) ((a > b) ? a : b) 
#define MAX3(a,b,c) MAX2(MAX2(a, b), c)   
#define SIZE_OF_VAR(x) (size_t)(&x + 1) - (size_t)(&x)
#define SIZE_OF_TYPE(x) (char*)((x*)0 + 1) - (char*)(x*)0 


typedef enum {
	INT = 1,
	FLOAT = 2,
	STR = 3
} type;


typedef struct
{
	type name;
    void* data;
    
} SuperStruct;


SuperStruct* CreaterStruct(type nameOf ,void *value);
void AddEveryThing(int num, SuperStruct* p_struc);
void PrintEverything(SuperStruct* p_struc);
void Cleaner(SuperStruct* arr[], int lenArr);


#endif
