// Code framework comes form cardtest4.c and playdom.c in order to set the game up as both 
// a basic initialized game, and a game which has had several turns. 
// Purpose: This tests the getCostTest() function
// Name: Bridget McGinn
// CS362

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>


int main() {

	printf("----------------- Testing Function getCost() --------------- \n");
	printf("\nCheck cards 0-26\n");

	if (getCost(0)== 0)
	{
		printf("0. TEST PASSED\n");
	}
	else
	{
		printf("0.TEST FAILED\n");
	}
	if (getCost(1)== 2)
	{
		printf("1.TEST PASSED\n");
	}
	else
	{
		printf("1.TEST FAILED\n");
	}
	if (getCost(2)== 5)
	{
		printf("2.TEST PASSED\n");
	}
	else
	{
		printf("2.TEST FAILED\n");
	}
	if (getCost(3)== 8)
	{
		printf("3.TEST PASSED\n");
	}
	else
	{
		printf("3.TEST FAILED\n");
	}
	if (getCost(4)== 0)
	{
		printf("4.TEST PASSED\n");
	}
	else
	{
		printf("4.TEST FAILED\n");
	}
	if (getCost(5)== 3)
	{
		printf("5.TEST PASSED\n");
	}
	else
	{
		printf("5.TEST FAILED\n");
	}
	if (getCost(6)== 6)
	{
		printf("6.TEST PASSED\n");
	}
	else
	{
		printf("6.TEST FAILED\n");
	}
	if (getCost(7)== 6)
	{
		printf("7.TEST PASSED\n");
	}
	else
	{
		printf("7.TEST FAILED\n");
	}
	if (getCost(8)== 5)
	{
		printf("8.TEST PASSED\n");
	}
	else
	{
		printf("8.TEST FAILED\n");
	}
	if (getCost(9)== 4)
	{
		printf("9.TEST PASSED\n");
	}
	else
	{
		printf("9.TEST FAILED\n");
	}
	if (getCost(10)== 4)
	{
		printf("10.TEST PASSED\n");
	}
	else
	{
		printf("10.TEST FAILED\n");
	}
	if (getCost(11)== 5)
	{
		printf("11.TEST PASSED\n");
	}
	else
	{
		printf("11.TEST FAILED\n");
	}
	if (getCost(12)== 4)
	{
		printf("12.TEST PASSED\n");
	}
	else
	{
		printf("12.TEST FAILED\n");
	}
	if (getCost(13)== 4)
	{
		printf("13.TEST PASSED\n");
	}
	else
	{
		printf("13.TEST FAILED\n");
	}
	if (getCost(14)== 3)
	{
		printf("14.TEST PASSED\n");
	}
	else
	{
		printf("14.TEST FAILED\n");
	}
	if (getCost(15)== 4)
	{
		printf("15.TEST PASSED\n");
	}
	else
	{
		printf("15.TEST FAILED\n");
	}
	if (getCost(16)== 3)
	{
		printf("16.TEST PASSED\n");
	}
	else
	{
		printf("16.TEST FAILED\n");
	}
	if (getCost(17)== 5)
	{
		printf("17.TEST PASSED\n");
	}
	else
	{
		printf("17.TEST FAILED\n");
	}
	if (getCost(18)== 3)
	{
		printf("18.TEST PASSED\n");
	}
	else
	{
		printf("18.TEST FAILED\n");
	}
	if (getCost(19)== 5)
	{
		printf("19.TEST PASSED\n");
	}
	else
	{
		printf("19.TEST FAILED\n");
	}
	if (getCost(20)== 3)
	{
		printf("20.TEST PASSED\n");
	}
	else
	{
		printf("20.TEST FAILED\n");
	}
	if (getCost(21)== 4)
	{
		printf("21.TEST PASSED\n");
	}
	else
	{
		printf("21.TEST FAILED\n");
	}
	if (getCost(22)== 2)
	{
		printf("22.TEST PASSED\n");
	}
	else
	{
		printf("22.TEST FAILED\n");
	}
	if (getCost(23)== 5)
	{
		printf("23.TEST PASSED\n");
	}
	else
	{
		printf("23.TEST FAILED\n");
	}
	if (getCost(24)== 4)
	{
		printf("24.TEST PASSED\n");
	}
	else
	{
		printf("24.TEST FAILED\n");
	}
	if (getCost(25)== 4)
	{
		printf("25.TEST PASSED\n");
	}
	else
	{
		printf("25.TEST FAILED\n");
	}
	if (getCost(26)== 4)
	{
		printf("26.TEST PASSED\n");
	}
	else
	{
		printf("26.TEST FAILED\n");
	}
	

	printf("\nCheck out of bounds cards\n");
	
	if(getCost(27)== -1)
	{
		printf("TEST PASSED\n\n");
	}
	else
	{
		printf("TEST FAILED\n\n");
	}
}


