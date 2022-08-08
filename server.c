#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../STD_TYPE.h"

#include "../Card/card.h"
#include "../Terminal/terminal.h"

#include "server.h"

/*Server's Accounts Database with any initial valid accounts numbers passed the LUHN check */
ST_accountsDB_t accountsDataBase[255] = {{4000.00, "4916945627505481"},{12000.50, "4493625375298262"},
{20000.00,"4929101130212489"},{19000.25, "4485846819394224"},{50000.75, "4539780225981447"},
{67050.00,"4485456770455996"},{86000.00, "4716069021758224"},{13078.30, "4539207880267326"},
{90000.00,"4571065954771386"},{74089.00, "4539101982402479"}};

/*Server's Transaction Database with initial value of ZERO to save any transaction happens */
ST_transaction_t transactionDataBase[255] = {0};

uint8_t member;

uint8_t SearchMember (ST_cardData_t *cardData)
{
	/*search for an account in server database */

	for(uint8_t i=0; i<255 ; i++)
	{
		if(strcmp(cardData->primaryAccountNumber , accountsDataBase[i].primaryAccountNumber) == 0)
			return i;
	}
	
	return -1;
}

EN_transState_t recieveTransactionData(ST_transaction_t *transData)
{
	/*check if the account in the server database or not*/

	EN_transState_t transLocalError = isValidAccount(&(transData->cardHolderData));
	
	if(transLocalError == DECLINED_STOLEN_CARD)
	{
		transData->transState = DECLINED_STOLEN_CARD;
		return DECLINED_STOLEN_CARD;
	}
	
	/*check if the account has any valid balance in the server database or not*/
	EN_serverError_t serverLocalError = isAmountAvailable(&(transData->terminalData));
	
	if(serverLocalError == LOW_BALANCE)
	{
		transData->transState = DECLINED_INSUFFECIENT_FUND;
		return DECLINED_INSUFFECIENT_FUND;
	}
	
	/*update the balance*/
	accountsDataBase[member].balance -= transData->terminalData.transAmount;
	
	/*save the transaction in the server database*/
	serverLocalError = saveTransaction(transData);
	if(serverLocalError == SAVING_FAILED)
	{
		transData->transState = INTERNAL_SERVER_ERROR;
		return INTERNAL_SERVER_ERROR;
	}

	
	return ACCEPTED;
}

EN_transState_t isValidAccount(ST_cardData_t *cardData)
{
	if(member == 255)
		return DECLINED_STOLEN_CARD;
	else
		return ACCEPTED;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t *termData)
{
	if((termData->transAmount) > (accountsDataBase[member].balance))
		return LOW_BALANCE;
	
	return ACCEPTED;
}

EN_serverError_t saveTransaction(ST_transaction_t *transData)
{
	static uint8_t iterator = 0;

	transactionDataBase[member].cardHolderData = transData->cardHolderData;
	transactionDataBase[member].terminalData = transData->terminalData;
	transactionDataBase[member].transState = transData->transState;
	
	transData->transactionSequenceNumber = rand();
	transactionDataBase[member].transactionSequenceNumber = transData->transactionSequenceNumber;

	if(transactionDataBase[member].transactionSequenceNumber == 0)
	{
		transData->transState = SAVING_FAILED;
		return SAVING_FAILED;
	}else if(iterator >254)
	{
		transData->transState = SAVING_FAILED;
		return SAVING_FAILED;
	}
	
	iterator++;
	
	return ACCEPTED;
}

EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t *transData)
{
	
	if(member == 255)
		return ACCOUNT_NOT_FOUND;
	
	
	if(transactionDataBase[member].transactionSequenceNumber != transactionSequenceNumber)
	{
		transData->transState = TRANSACTION_NOT_FOUND;
		return TRANSACTION_NOT_FOUND;
	}
	
	
	return ACCEPTED;
}