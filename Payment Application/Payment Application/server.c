#include "server.h"
#include "data_types.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define database_size 10

uint8_t		database_index;
uint32_t	num_of_transactions = 0;


struct ST_accountsDB_t bank_accounts[database_size] =
{
	{1000,"validaccountpan1000"},{2000,"validaccountpan2000"},{3000,"validaccountpan3000"},
	{4000,"validaccountpan4000"},{5000,"validaccountpan5000"},{6000,"validaccountpan6000"},
	{7000,"validaccountpan7000"},{8000,"validaccountpan8000"},{9000,"validaccountpan9000"},
	{10000,"validaccountpan10000"}
};


struct ST_transaction_t transaction_database [database_size] = { 0 };

//   ptr to struct1[]->struct2.element

EN_serverError_t isValidAccount(ST_cardData_t* cardData)
{
	
	uint8_t flag = 0;
	for (database_index =0; database_index < database_size; database_index++)
	{
		if ((strcmp(cardData->primaryAccountNumber, bank_accounts[database_index].primaryAccountNumber))==0)
		{
			flag = 1;
			break;
		}	
	}
	if (flag == 1)
	{
		printf("VALID ACCOUNT\n");
		return SERVER_OK;
	}
	else //if (database_index == database_size - 1 && flag == 0)
	{
		printf("ACCOUNT NOT FOUND\n");
		return ACCOUNT_NOT_FOUND;
	}
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData)
{
	//termData->maxTransAmount = bank_accounts[database_index].balance;

	if (termData->transAmount > bank_accounts[database_index].balance)
	{
		printf("LOW BALANCE AMOUNT UNAVAILABLE\n");
		return LOW_BALANCE;
	}
	else
	{
		printf("AMOUNT AVAILABLE\n");
		return SERVER_OK;
	}
}


EN_serverError_t saveTransaction(ST_transaction_t* transData) //if approved
{	
	//Increment Transaction sequence number and save to database
	num_of_transactions++;
	transaction_database[num_of_transactions-1].transactionSequenceNumber = num_of_transactions;

	//Save transaction data to Transaction Database
	transaction_database[num_of_transactions - 1].cardHolderData = (transData->cardHolderData);
		/*
		uint8_t cardHolderName[25];
		uint8_t primaryAccountNumber[20];
		uint8_t cardExpirationDate[6];
		*/

	transaction_database[num_of_transactions - 1].terminalData = (transData->terminalData);
		/*
		float transAmount;
		float maxTransAmount;
		uint8_t transactionDate[11];
		*/

	transaction_database[num_of_transactions - 1].transState = (transData->transState);
		/*
		typedef enum EN_transState_t
		{
		APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, INTERNAL_SERVER_ERROR
		}EN_transState_t;
		*/

	//Saves  transaction, APPROVED or DECLINED , with the specific reason for declining/transaction state.
	//If transaction can't be saved return SAVING_FAILED, will return OK
	uint8_t get_flag;
	get_flag = getTransaction(num_of_transactions, transData);

	if (get_flag == SERVER_OK)
	{
		//printf("TRANSACTION SAVED\n");
		return SERVER_OK;
	}
	else if (get_flag == TRANSACTION_NOT_FOUND)
	{
		//printf("SAVING FAILED\n");
		return SAVING_FAILED;
	}
}

EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData)
{
	//Search for sequence no. in the database
	//return SERVER_OK - TRANSACTION_NOT_FOUND
	uint8_t i;
	for (i=0; i< database_size; i++)
	{
		if (transaction_database[i].transactionSequenceNumber == transactionSequenceNumber)
		{
			return SERVER_OK;
		}	
	}
	return TRANSACTION_NOT_FOUND;
}


EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
	 

	uint8_t amount_flag, valid_flag, saved_flag;

	if ((valid_flag = isValidAccount(&(transData->cardHolderData))) == ACCOUNT_NOT_FOUND) 			
	{
		printf("DECLINED STOLEN CARD\n");
		return DECLINED_STOLEN_CARD;
	}
	else if ((amount_flag = isAmountAvailable(&(transData->terminalData))) == LOW_BALANCE) 
	{
		printf("DECLINED INSUFFECIENT FUND\n");
		return DECLINED_INSUFFECIENT_FUND;
	}	
	else if ((valid_flag == SERVER_OK) && (amount_flag == SERVER_OK))
	{
		printf("TRANSACTION APPROVED\n");
		//Update Balance
		bank_accounts[database_index].balance = (bank_accounts[database_index].balance) - transData->terminalData.transAmount;
		printf("CURRENT BALANCE:	%f\n", bank_accounts[database_index].balance);

		//Check if Transaction is saved 
		if ((saved_flag = saveTransaction(transData)) == SAVING_FAILED)
		{
			printf("INTERNAL SERVER ERROR\n");
			return INTERNAL_SERVER_ERROR;
		}
		else if (saved_flag == SERVER_OK)
		{
			printf("TRANSACTION COMPLETE\n");
			return APPROVED;
		}
	}


}



