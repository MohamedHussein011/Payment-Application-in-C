/*
 * Name: Mohamed Hussein Mohamed Salem
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>

#include "../STD_TYPE.h"
#include "../Card/card.h"
#include "terminal.h"

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{
	uint32_t day,month,year;
	uint8_t tempYear[4], tempMonth[2], tempDay[2];
	uint32_t temp;
	time_t t;
	time(&t);
	struct tm *local =  localtime(&t);

	/*parameters to display cuurent date DD/MM/YYYY*/
	day = local -> tm_mday;
	month = local -> tm_mon + 1;
	year = local -> tm_year + 1900;
	
	printf("Please, enter the transaction date.\n");
	printf("Note: the date must be entered as DD/MM/YYYY\n"); 
	printf("Current date is: %02d/%02d/%02d\n",day,month,year);
	printf("Date: "); fflush(stdout);
	scanf("%s",&termData -> transactionDate);
	
	/*check if transaction date is valid or not*/
	if ((strlen(termData->transactionDate) < 10) || (strlen(termData->transactionDate) > 10) || (termData -> transactionDate == NULL))
		return WRONG_DATE;
	
	/*check if transaction date contains nothing than numbers & / */
	for (uint8_t i = 0; i<strlen(termData -> transactionDate); i++)
	{
		if(i == 2 || i == 5)
		{
			if(termData -> transactionDate[i] != '/')
				return WRONG_DATE;
			else
				continue;
		}
		

		if(isdigit(termData -> transactionDate[i] - '0') != 0)
			return WRONG_DATE;
		
	}
	
	/*check if transaction date's day is not bigger than 31 & month not bigger than 12 
	  & year not smaller than 2022*/
	if((termData -> transactionDate[0] - '0' > 3) || (termData -> transactionDate[3] - '0' > 1))
		return WRONG_DATE;
	
	if((termData -> transactionDate[0] - '0' == 3) && (termData -> transactionDate[1] - '0' > 1))
		return WRONG_DATE;
	
	if((termData -> transactionDate[3] - '0' == 1) && (termData -> transactionDate[4] - '0' > 2))
		return WRONG_DATE;
	
	/*check if transaction date precedes the current year or not */
	tempYear[0] = termData -> transactionDate[6];
	tempYear[1] = termData -> transactionDate[7];
	tempYear[2] = termData -> transactionDate[8];
	tempYear[3] = termData -> transactionDate[9];
	
	temp = atoi(tempYear);
	if(temp < year)
		return WRONG_DATE;
	else if(temp == year)
	{
		tempMonth[0] = termData -> transactionDate[3];
		tempMonth[1] = termData -> transactionDate[4];
		
		temp = atoi(tempMonth);
		if(temp < month)
			return WRONG_DATE;
		else if(temp == month)
		{
			tempDay[0] = termData -> transactionDate[0];
			tempDay[1] = termData -> transactionDate[1];
			
			temp = atoi(tempDay);
			if(temp < day)
				return WRONG_DATE;
		}
	}
	
	return OK;
}

EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{	
	uint8_t tempTerminalYear[2], tempTerminalMonth[2];
	uint8_t tempCardYear[2], tempCardMonth[2];
	
	/*check if card is expired or not by comparing the month & year between the card expiration 
	date & transaction Date*/
	tempTerminalYear[0] = termData.transactionDate[8];
	tempTerminalYear[1] = termData.transactionDate[9];
	tempCardYear[0] = cardData.cardExpirationDate[3];
	tempCardYear[1] = cardData.cardExpirationDate[4];
	
	if(atoi(tempTerminalYear) > atoi(tempCardYear))
		return EXPIRED_CARD;
	else if(atoi(tempTerminalYear) == atoi(tempCardYear))
	{
		tempTerminalMonth[0] = termData.transactionDate[3];
		tempTerminalMonth[1] = termData.transactionDate[4];
		tempCardMonth[0] = cardData.cardExpirationDate[0];
		tempCardMonth[1] = cardData.cardExpirationDate[1];
		
		if(atoi(tempTerminalMonth) > atoi(tempCardMonth))
			return EXPIRED_CARD;
		
	}
	
	return OK;
}

EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData)
{
	uint8_t value = 0, result = 0;
	bool flag = false;
	
	/*check if card PAN is valid or not using LUHN number check algorithm */
	for (char i = strlen(cardData->primaryAccountNumber) - 1; i>=0; i--)
	{	
		value = cardData->primaryAccountNumber[i] - '0';
		
		if(flag == true)
			value = value * 2;
		
		result += value / 10;
		result += value % 10;
		flag = !flag;
		
	}
	
	if(result % 10 != 0)
		return INVALID_CARD;
	
	return OK;
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
	
	printf("Please, enter the transcation amount you need to transfer:\n");
	printf("Note: Maximum amount limit is %0.4f\n", termData->maxTransAmount);
	printf("Amount: "); fflush(stdout);
	scanf("%f",&(termData->transAmount));
	
	if ((termData->transAmount <= 0))
		return INVALID_AMOUNT;
	
	return OK;
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{
	
	if ((termData->transAmount) > (termData->maxTransAmount))
		return EXCEED_MAX_AMOUNT;
	
	return OK;
}

EN_terminalError_t setMaxAmount(ST_terminalData_t *termData)
{
	
	termData -> maxTransAmount = 10000.00;
	
	if ((termData->maxTransAmount <= 0))
		return INVALID_MAX_AMOUNT;
	
	return OK;

}
