#include <stdio.h>
#include <string.h> /* memcpy */
#include "dhcp.h"


void PrintAddr(ip_t addr)
{	
	size_t i = 0; 
	for(i = 0; i < 4; ++i)
	{
		printf("%d. ", addr[i]); 
	}
	printf("\n"); 
}



int main()
{
	ip_t submask = {255, 255, 255, 0}; /*24*/
	
	ip_t add = {198, 162, 1, 252};
	ip_t add1 = {198, 162, 1, 251};
	ip_t add2 = {198, 162, 1, 250};
	ip_t add3 = {198, 162, 1, 249};
	ip_t add4 = {198, 162, 1, 248};
	
	ip_t add5 = {198, 162, 1, 1};
	ip_t add6 = {198, 162, 1, 2};
	ip_t add7 = {198, 162, 1, 3};
	
	ip_t add8 = {150, 200, 1, 3};
	
	
	ip_t tmp = {0, 0, 0, 0};
	
	ip_t zero = {0, 0, 0, 0};
	size_t bits = 6;	

	dhcp_t *dhcp = CreateDHCP(submask, bits);
	
	

	AllocateIP(dhcp, add1, tmp);
	AllocateIP(dhcp, add, tmp);
	PrintAddr(tmp);
	AllocateIP(dhcp, add, tmp);
	PrintAddr(tmp);
	AllocateIP(dhcp, add, tmp);
	AllocateIP(dhcp, add4, tmp);
	
	
	AllocateIP(dhcp, add4, tmp);
	AllocateIP(dhcp, add, tmp);
	AllocateIP(dhcp, add1, tmp);
	AllocateIP(dhcp, add2, tmp);
	AllocateIP(dhcp, add3, tmp);
	AllocateIP(dhcp, add4, tmp);
	AllocateIP(dhcp, add5, tmp);
	AllocateIP(dhcp, add6, tmp);
	AllocateIP(dhcp, add7, tmp);
	
	AllocateIP(dhcp, add8, tmp);
	AllocateIP(dhcp, zero, tmp);
	/*
*/
	
	
	PrintAddr(tmp);
	
	printf("%ld\n",CountFree(dhcp));
	

	 DestroyDHCP(dhcp);
return 0;
}
