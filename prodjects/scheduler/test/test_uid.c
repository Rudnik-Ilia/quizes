

#include <unistd.h>
#include <stdio.h>
#include "ilrd_uid.h"



int main()
{
	ilrd_uid_t id = {0,0,0};
	ilrd_uid_t id2 = {0,0,0};
	ilrd_uid_t id3 = {0,0,0};
	
	
	id = UIDCreate();
	/*
	sleep(3);
	*/
	id2 = UIDCreate();
	id3 = UIDCreate();
	
	printf("%d\n", UIDIsSame(id,id2));
	printf("%d\n", UIDIsSame(id,id3));
	printf("%d\n", UIDIsSame(id2,id3));
	
	printf("%d\n", id2.created_time);
	printf("%d\n", id.created_time);


return 0;
}
