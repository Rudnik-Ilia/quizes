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

void Test_Jo();

int main()
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
	ip_t add_server = {198, 162, 0, 254};
	ip_t add_subnet = {198, 162, 0, 0};
	
	ip_t lev = {88, 45, 222, 77};
	
	ip_t tmp = {0, 0, 0, 0};
		
	dhcp_t *dhcp = CreateDHCP(submask, 5);
	TEST("SIZE", CountFree(dhcp), 29);
	
	AllocateIP(dhcp, add1, tmp);
	TEST("SIZE", CountFree(dhcp), 28);
	PrintAddr(tmp);
	
	AllocateIP(dhcp, add2, tmp);
	TEST("SIZE", CountFree(dhcp), 27);
	PrintAddr(tmp);
	
	AllocateIP(dhcp, add3, tmp);
	TEST("SIZE", CountFree(dhcp), 26);
	PrintAddr(tmp);
	
	AllocateIP(dhcp, add4, tmp);
	TEST("SIZE", CountFree(dhcp), 25);
	PrintAddr(tmp);
	
	AllocateIP(dhcp, add0, tmp);
	TEST("SIZE", CountFree(dhcp), 24);
	PrintAddr(tmp);
	
	AllocateIP(dhcp, add6, tmp);
	TEST("SIZE", CountFree(dhcp), 23);
	PrintAddr(tmp);
	
	AllocateIP(dhcp, add0, tmp);
	TEST("SIZE", CountFree(dhcp), 22);
	PrintAddr(tmp);
	
	AllocateIP(dhcp, add_broadcast, tmp);
	TEST("SIZE", CountFree(dhcp), 21);
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
	PrintAddr(tmp);
	

/*	
	PrintTrie(dhcp);
*/	
	DestroyDHCP(dhcp);
return 0;
}

void Test_Jo()
{
    dhcp_t *dhcp = NULL;
    ip_t alloc_ip;
    ip_t ip = {192,168,2,48};
    ip_t ip_1 = {192,168,2,49};
    ip_t ip_2 = {192,168,2,50};
    ip_t ip_3 = {192,168,2,51};
    ip_t ip_4 = {192,168,2,52};

    dhcp = CreateDHCP(ip, 4);
    
    printf("Free: %lu\n",CountFree(dhcp));

    AllocateIP(dhcp, ip_1, alloc_ip);
    printf("Free: %lu\n",CountFree(dhcp));
    printf("Suggested Ip: ");
    PrintAddr(ip_1);
    printf("Allocated Ip: ");
    PrintAddr(alloc_ip);

    AllocateIP(dhcp, ip_2, alloc_ip);
    printf("Free: %lu\n",CountFree(dhcp));
    printf("Suggested Ip: ");
    PrintAddr(ip_2);
    printf("Allocated Ip: ");
    PrintAddr(alloc_ip);

    AllocateIP(dhcp, ip_3, alloc_ip);
    printf("Free: %lu\n",CountFree(dhcp));
    printf("Suggested Ip: ");
    PrintAddr(ip_3);
    printf("Allocated Ip: ");
    PrintAddr(alloc_ip);

    AllocateIP(dhcp, ip_3, alloc_ip);
    printf("Free: %lu\n",CountFree(dhcp));
    printf("Suggested Ip: ");
    PrintAddr(ip_3);
    printf("Allocated Ip: ");
    PrintAddr(alloc_ip);


    DestroyDHCP(dhcp);
    
}





















