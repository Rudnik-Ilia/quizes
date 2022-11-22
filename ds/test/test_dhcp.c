#include <stdio.h>
#include <string.h> /* memcpy */
#include "dhcp.h"
#include "test.h"


void PrintAddr(ip_t addr)
{	
	size_t i = 0; 
	for(i = 0; i < 4; ++i)
	{
		printf("%d. ", addr[i]); 
	}
	printf("\n"); 
}

int TheSame(ip_t addr1, ip_t addr2)
{	
	size_t i = 0;
	int count = 0;
	for(i = 0; i < 4; ++i)
	{
		count += (addr1[i] - addr2[i]);
	};
	return count;
	

}
void test_status();
void General();
void Delete();

int main()
{	
	test_status();
	General();
	Delete();
/*
*/
PASS;
return 0;
}

void General()
{
	ip_t submask = {198, 162, 1 , 0}; /*24*/
	
	ip_t add0 = {0, 0, 0, 0};
	ip_t add1 = {198, 162, 1, 1};
	ip_t add2 = {198, 162, 1, 25};
	ip_t add3 = {198, 162, 1, 240};
	ip_t add4 = {198, 162, 1, 248};
	
	ip_t add5 = {198, 162, 1, 1};
	ip_t add6 = {198, 162, 1, 2};
	ip_t add7 = {198, 162, 1, 3};
	
	ip_t add_broadcast = {198, 162, 0, 255};
	
	ip_t lev = {88, 45, 222, 77};
	
	ip_t tmp = {0, 0, 0, 0};
		
	dhcp_t *dhcp = CreateDHCP(submask, 5);
	TEST("SIZE", CountFree(dhcp), 29);
	
	AllocateIP(dhcp, add1, tmp);
	TEST("SIZE", CountFree(dhcp), 28);
	TEST("The same", TheSame(add1, tmp), 0);
		
	
	AllocateIP(dhcp, add2, tmp);
	TEST("SIZE", CountFree(dhcp), 27);
	TEST("The same", TheSame(add2, tmp), 0);
	
	AllocateIP(dhcp, add3, tmp);
	TEST("SIZE", CountFree(dhcp), 26);
	TEST("The same", TheSame(add3, tmp), 0);
	
	AllocateIP(dhcp, add4, tmp);
	TEST("SIZE", CountFree(dhcp), 25);
	TEST("The same", TheSame(add4, tmp), 0);
	
	AllocateIP(dhcp, add0, tmp);
	TEST("SIZE", CountFree(dhcp), 24);
	PrintAddr(tmp);
	
	AllocateIP(dhcp, add6, tmp);
	TEST("SIZE", CountFree(dhcp), 23);
	PrintAddr(add6);
	PrintAddr(tmp);
	
	AllocateIP(dhcp, add0, tmp);
	TEST("SIZE", CountFree(dhcp), 22);
	PrintAddr(add0);
	PrintAddr(tmp);
	
	AllocateIP(dhcp, add_broadcast, tmp);
	TEST("SIZE", CountFree(dhcp), 21);
	PrintAddr(add_broadcast);
	PrintAddr(tmp);
	
	/*undefined behavior.....should be*/
	AllocateIP(dhcp, lev, tmp);
	TEST("SIZE", CountFree(dhcp), 20);
	PrintAddr(tmp);
	
	AllocateIP(dhcp, add5, tmp);
	TEST("SIZE", CountFree(dhcp), 19);
	PrintAddr(tmp);
	
	AllocateIP(dhcp, add6, tmp);
	TEST("SIZE", CountFree(dhcp), 18);
	PrintAddr(tmp);
	
	AllocateIP(dhcp, add7, tmp);
	TEST("SIZE", CountFree(dhcp), 17);

	DestroyDHCP(dhcp);
}

void Delete()
{
	ip_t submask = {198, 162, 1 , 0}; /*24*/
	
	ip_t add1 = {198, 162, 1, 1};
	ip_t add2 = {198, 162, 1, 25};
	ip_t add3 = {198, 162, 1, 240};
	ip_t add4 = {198, 162, 1, 248};
	ip_t add5 = {198, 162, 1, 4};
	ip_t add6 = {198, 162, 1, 2};
	ip_t add7 = {198, 162, 1, 3};
	
	ip_t tmp = {0, 0, 0, 0};
	
	ip_t unreal1 = {130, 200, 20, 1};
	ip_t unreal2 = {0, 0, 0, 0};
	
	dhcp_t *dhcp = CreateDHCP(submask, 4);
	TEST("SIZE", CountFree(dhcp), 13);
	
	AllocateIP(dhcp, add1, tmp);
	AllocateIP(dhcp, add2, tmp);
	AllocateIP(dhcp, add3, tmp);
	AllocateIP(dhcp, add4, tmp);
	AllocateIP(dhcp, add5, tmp);
	AllocateIP(dhcp, add6, tmp);
	AllocateIP(dhcp, add7, tmp);
	
	TEST("SIZE", CountFree(dhcp), 6);
	
	FreeIp(dhcp,  add1);
	TEST("SIZE", CountFree(dhcp), 7);
	
	FreeIp(dhcp,  add2);
	TEST("SIZE", CountFree(dhcp), 8);
	
	FreeIp(dhcp,  add3);
	TEST("SIZE", CountFree(dhcp), 9);
	
	FreeIp(dhcp,  add4);
	TEST("SIZE", CountFree(dhcp), 10);
	
	FreeIp(dhcp,  unreal1);
	TEST("SIZE", CountFree(dhcp), 10);
	
	FreeIp(dhcp,  unreal2);
	TEST("SIZE", CountFree(dhcp), 10);

	DestroyDHCP(dhcp);
}

void test_status()
{
	ip_t submask = {198, 162, 1 , 0}; /*24*/
	ip_t add2 = {198, 162, 1, 25};
	ip_t add0 = {0, 0, 0, 0};
	ip_t tmp = {0, 0, 0, 0};
	
	status_t status = 0;
	
	dhcp_t *dhcp = CreateDHCP(submask, 5);
	TEST("SIZE", CountFree(dhcp), 29);
	
	
	status = AllocateIP(dhcp, add0, tmp);
	TEST("Status", status, 1);
	
	status = AllocateIP(dhcp, add2, tmp);
	TEST("Status", status, 0);
	
	status = AllocateIP(dhcp, add2, tmp);
	TEST("Status", status, 1);
	DestroyDHCP(dhcp);
}

















