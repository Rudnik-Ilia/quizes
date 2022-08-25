#ifndef __WS8_5_H__
#define __WS8_5_H__

#define SIZE_NAME 20
#define SIZE_SONAME 20

typedef struct
{
	char name[SIZE_NAME];
	char soname[SIZE_SONAME];
	struct
	{
		struct {
		
			float a;
			
		} human;
		struct {
		
			float b; 
		} real; 
		
		float sport;
	}grades;
	
}student;





int Reader(student * st);
int Writer(student * st);

#endif

