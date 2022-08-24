#ifndef __WS8_H__
#define __WS8_H__

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

#endif
