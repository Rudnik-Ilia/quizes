/**********************
* Title : Worksheet DLL
* Author: Ilia Rudnik
* Reviewer: 
* Date : 06/09/2022
* Status : approved
***********************/

struct dll_node{

	void * data;
  	dllist_iter_t *previous;
  	dllist_iter_t *next;
  	
};
 
 
struct dllist{

	dllist_iter_t *head;
	dllist_iter_t *tail;
	
};


