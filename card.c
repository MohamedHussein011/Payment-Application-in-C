/*
 * Name: Mohamed Hussein Mohamed Salem
 * card.c
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "../STD_TYPE.h"

#include "card.h"

EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{
	/*get user name with spaces*/
	printf("Please, enter your name: "); fflush(stdout);
	scanf("%[^\n]%*c",&cardData -> cardHolderName);
	
	/*check if user name is valid or not*/
	if ((strlen(cardData->cardHolderName) < 20) || (strlen(cardData->cardHolderName) > 24) || (cardData -> cardHolderName == NULL))
		return WRONG_NAME;
	
	/*check if user name contains any number or special characters*/
	for(uint8_t i = 0; i<strlen(cardData->cardHolderName); i++)
	{
		if((cardData->cardHolderName[i] == '!') || (cardData->cardHolderName[i] == '@') || (cardData->cardHolderName[i] == '#') || 
	       (cardData->cardHolderName[i] == '$') || (cardData->cardHolderName[i] == '%') || (cardData->cardHolderName[i] == '^') || 
	       (cardData->cardHolderName[i] == '&') || (cardData->cardHolderName[i] == '*') || (cardData->cardHolderName[i] == '(') || 
	       (cardData->cardHolderName[i] == ')') || (cardData->cardHolderName[i] == '-') || (cardData->cardHolderName[i] == '_') || 
	       (cardData->cardHolderName[i] == '=') || (cardData->cardHolderName[i] == '+') || (cardData->cardHolderName[i] == '/') ||
		   (cardData->cardHolderName[i] == ']') || (cardData->cardHolderName[i] == '[') || (cardData->cardHolderName[i] == '{') ||
		   (cardData->cardHolderName[i] == '}') || (cardData->cardHolderName[i] == '"') || (cardData->cardHolderName[i] == '\'') ||
		   (cardData->cardHolderName[i] == ';') || (cardData->cardHolderName[i] == ':') || (cardData->cardHolderName[i] == '?') ||
		   (cardData->cardHolderName[i] == '~') || (cardData->cardHolderName[i] == '`') || (cardData->cardHolderName[i] == '>') ||
		   (cardData->cardHolderName[i] == '<') || (cardData->cardHolderName[i] == '.') || (cardData->cardHolderName[i] == '0') ||
		   (cardData->cardHolderName[i] == '1') || (cardData->cardHolderName[i] == '2') || (cardData->cardHolderName[i] == '3') ||
		   (cardData->cardHolderName[i] == '4') || (cardData->cardHolderName[i] == '5') || (cardData->cardHolderName[i] == '6') ||
		   (cardData->cardHolderName[i] == '7') || (cardData->cardHolderName[i] == '8') || (cardData->cardHolderName[i] == '9'))
		   return WRONG_NAME;
	}
	
	/*check if user name contains more than 3 spaces*/
	for(uint8_t i = 0; i<strlen(cardData->cardHolderName); i++)
	{
		uint8_t z = 0;
		if(cardData->cardHolderName[i] == ' ')
			z++;
		
		if(z > 3)
		   return WRONG_NAME;
	}
	
	return K;
}
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
{
	/*get expiration date*/
	printf("Note: the date must be entered as MM/YY\n");
	printf("Please, enter your card expiry date: "); fflush(stdout);
	scanf("%s",&cardData -> cardExpirationDate);
	
	/*check if expiration date is valid or not*/
	if ((strlen(cardData->cardExpirationDate) < 5) || (strlen(cardData->cardExpirationDate) > 5) || (cardData -> cardExpirationDate == NULL))
		return WRONG_EXP_DATE;
	
	/*check if expiration date contains nothing than numbers*/
	for (uint8_t i = 0; i<strlen(cardData -> cardExpirationDate); i++)
	{
		if(i == 2)
		{
			if(cardData -> cardExpirationDate[i] != '/')
				return WRONG_EXP_DATE;
			else
				continue;
		}
		
		if(isdigit(cardData -> cardExpirationDate[i] - '0') != 0)
			return WRONG_EXP_DATE;
		
	}
		
	/*check if expiration date month is bigger than 12 or not */
	if(cardData -> cardExpirationDate[0] - '0' > 1)
		return WRONG_EXP_DATE;
	
	if((cardData -> cardExpirationDate[0] - '0' == 1) && (cardData -> cardExpirationDate[1] - '0' > 2))
		return WRONG_EXP_DATE;
	
	if(cardData -> cardExpirationDate[3] - '0' < 2)
		return WRONG_EXP_DATE;
	
	return K;
}
EN_cardError_t getCardPAN(ST_cardData_t *cardData)
{
	/*get PAN*/
	printf("Please, enter your Primary Account Number: ");  fflush(stdout);
	scanf("%s",&cardData -> primaryAccountNumber);
	
	/*check if PAN is valid or not*/
	if ((strlen(cardData->primaryAccountNumber) < 16) || (strlen(cardData->primaryAccountNumber) > 19) || (cardData -> primaryAccountNumber == NULL))
		return WRONG_PAN;
	
	/*check if PAN contains nothing than numbers*/
	for (uint8_t i = 0; i<strlen(cardData->primaryAccountNumber); i++)
	{
		if(isdigit(cardData->primaryAccountNumber[i] - '0') != 0)
			return WRONG_PAN;
	}
	
	return K;
}