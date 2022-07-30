#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../STD_TYPE.h"

#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include "../Server/server.h"
#include "app.h"

extern ST_accountsDB_t accountsDataBase[255];
extern uint8_t member;

void main()
{
	appStart();
}

void appStart(void)
{
	uint8_t choice;
	uint32_t number;
	float balance, deposit;
	EN_cardError_t CardError;
	EN_terminalError_t TerminalError;
	EN_transState_t TransStateError;
	EN_serverError_t ServerError;
	
	ST_transaction_t userData = {{"","",""}, {0,0,""}, APPROVED, 0};
	printf("Welcome to Bank egFWd!\n\n");
	
	while(true)
	{		
		CardError = getCardHolderName(&userData.cardHolderData);
		if (CardError == WRONG_NAME)
		{
			printf("The name is less than 20 characters or greater than 24. \nOr, contains any special character or numbers.\n");
			printf("Please, enter acceptable name.\n\n");
			continue;
		}
		
		CardError = getCardExpiryDate(&userData.cardHolderData);
		if (CardError == WRONG_EXP_DATE)
		{
			printf("Wrong Expiration Date.\n");
			break;
		}
		CardError = getCardPAN(&userData.cardHolderData);
		if (CardError == WRONG_PAN)
		{
			printf("Wrong Primary Account Number.\n");
			break;
		}
		
		TerminalError = isValidCardPAN(&userData.cardHolderData);
		if (TerminalError == INVALID_CARD)
		{
			printf("Invalid Card PAN.\n");
			break;
		}
		if(userData.transState == DECLINED_STOLEN_CARD)
		{
			printf("Declined Invalid Account or Blocked Account!\n");
			break;
		}
		
		printf("Welcome, %s !\n\n",userData.cardHolderData.cardHolderName);
		
		while(true)
		{
			member = SearchMember (&userData.cardHolderData);
			
			printf("What do you want to do?\n");
			printf("1: Make new Transaction.\n");
			printf("2: Check Transaction.\n");
			printf("3: Check Balance.\n");
			printf("4: Deposit money.\n");
			printf("5: Report Stolen Card.\n");
			printf("6: Exit.\n"); fflush(stdout);
			scanf("%d",&choice);
			if(choice == 1)
			{
				if(userData.transState == DECLINED_STOLEN_CARD)
				{
					printf("Declined Invalid Account or Blocked Account!\n\n");
				}else{
					TerminalError = getTransactionDate(&userData.terminalData);
					if (TerminalError == WRONG_DATE)
					{
						printf("Wrong Date.\n");
						break;
					}
					
					if(isCardExpired(userData.cardHolderData, userData.terminalData))
					{
						printf("Declined Expired Card!\n");
						printf("Exitiiiing\n");
						break;
					}else{
						printf("Accepted Card.\nwelcome!\n\n");
					}
					
					setMaxAmount(&userData.terminalData);
					if (TerminalError == INVALID_MAX_AMOUNT)
					{
						printf("INVALID MAX AMOUNT.\n");
						break;
					}
					TerminalError = getTransactionAmount(&userData.terminalData);
					if (TerminalError == INVALID_AMOUNT)
					{
						printf("INVALID AMOUNT.\n");
						break;
					}
					
					if(isBelowMaxAmount(&userData.terminalData))
					{
						printf("Declined Amount Exceeding Limit!\n");
						printf("Exitiiiing\n");
						break;
					}
					
					TransStateError = recieveTransactionData(&userData);
					
					if(TransStateError == DECLINED_STOLEN_CARD)
					{
						printf("Declined Invalid Account or Blocked Account!\n");
						break;
					}else if(TransStateError == DECLINED_INSUFFECIENT_FUND)
					{
						printf("Declined Insufficient Funds!\n");
						break;
					}else if(TransStateError == INTERNAL_SERVER_ERROR)
					{
						printf("Server is down, please try again later!\n");
						break;
					}
					
					
					balance = accountsDataBase[member].balance + userData.terminalData.transAmount;
					printf("Your curent balance is %0.4f.\n",balance);
					printf("Amount to be withdrawn = %0.4f.\n",userData.terminalData.transAmount);
					printf("Current Balance = %0.4f.\n",accountsDataBase[member].balance);
					printf("Transaction Number: %d\n",userData.transactionSequenceNumber);
					printf("Transaction Completed.\n");
				}
			}else if(choice == 2)
			{
				if(userData.transState == DECLINED_STOLEN_CARD)
				{
					printf("Declined Invalid Account or Blocked Account!\n\n");
				}else{
					printf("Enetr Transaction sequence number to be searched:  "); fflush(stdout);
					scanf("%d",&number);
					ServerError = getTransaction(number, &userData);
					if(ServerError == ACCOUNT_NOT_FOUND)
					{
						printf("Declined Invalid Account!\n");
						break;
					}else if(ServerError == TRANSACTION_NOT_FOUND)
					{
						printf("Declined TRANSACTION NOT FOUND!\n");
						break;
					}
					printf("Transaction sequence number: %d\n",userData.transactionSequenceNumber);
					printf("Details of the Transaction owner.\n");
					printf("Name: %s.\n",userData.cardHolderData.cardHolderName);
					printf("PAN: %s.\n",userData.cardHolderData.primaryAccountNumber);
					printf("Transaction Date: %s.\n",userData.terminalData.transactionDate);
					printf("Transaction money = %0.4f.\n",userData.terminalData.transAmount);
					printf("Current Balance = %0.4f.\n",accountsDataBase[member].balance);
				}
			}else if(choice == 3)
			{
				if(userData.transState == DECLINED_STOLEN_CARD)
				{
					printf("Declined Invalid Account or Blocked Account!\n\n");
				}else{
					balance = accountsDataBase[member].balance;
					printf("Your curent balance is %0.4f.\n",balance);
				}
			}else if(choice == 4)
			{
				if(userData.transState == DECLINED_STOLEN_CARD)
				{
					printf("Declined Invalid Account or Blocked Account!\n\n");
				}else{
					printf("Enter the amount of money: "); fflush(stdout);
					scanf("%f",&deposit);
					accountsDataBase[member].balance += deposit;
					printf("Current Balance = %0.4f.\n",accountsDataBase[member].balance);
					printf("Amount added successfully.\n");
				}
			}else if(choice == 5)
			{
				if(userData.transState == DECLINED_STOLEN_CARD)
				{
					printf("Declined Invalid Account or Blocked Account!\n\n");
				}else{
					userData.transState = DECLINED_STOLEN_CARD;
					printf("Reported successfully.\n\n");
				}
				
			}else if(choice == 6)
			{
				printf("Shutting Down.\n");
				break;
			}
			else{
				printf("Wrong answer.\n");   
				break;
			}
		
		}
		break;
		
	}
	
}