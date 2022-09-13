/**********************
* Title : Worksheet 
* Author: Ilia Rudnik
* Reviewer: 
* Date : 06/09/2022
* Status : approved
***********************/

struct cbuff{
	
	size_t capacity;
	size_t read;
	size_t write;
	
	char flex[1];

};
cbuff_t *CBuffCreate(size_t capacity)
{
	cbuff_t * new_cbuff = malloc(sizeof(cbuff) + capacity);
	if(NULL == new_cbuff)
	{
		return 0;
	}
	return new_buff;
  	
return 
}





