

#include <stdio.h>
#include "app.h"
#include "data_types.h"

#include "app.h"
#include "card.h"
#include "server.h"
#include "terminal.h"

struct ST_cardData_t card_data;
EN_cardError_t card_return;

struct ST_terminalData_t terminal_data;
EN_terminalError_t terminal_return;

struct ST_transaction_t transaction_data;
EN_transState_t server_transState_return;
EN_serverError_t server_error_return;

void appStart(void)
{
	while (1)
	{
		


		/************Card Module Start************/

		//Get card holder name
		card_return = getCardHolderName(&card_data);
		while (card_return != 0)
		{
			card_return = getCardHolderName(&card_data);
		}

		//get card expiration date
		card_return = getCardExpiryDate(&card_data);
		while (card_return != 0)
		{
			card_return = getCardExpiryDate(&card_data);
		}

		//get card pan
		card_return = getCardPAN(&card_data);
		while (card_return != 0)
		{
			card_return = getCardPAN(&card_data);
		}


		/***********Terminal Module Start***********/

		//get card data
		//get transaction date
		terminal_return = getTransactionDate(&terminal_data);
		while (terminal_return != 0)
		{
			terminal_return = getTransactionDate(&terminal_data);
		}

		//is card expired?
		terminal_return = isCardExpired(card_data, terminal_data);
		if (terminal_return != 0)
		{
			//Declined Expired Card
			break;
		}
	

		//Get Transaction Amount
		terminal_return = getTransactionAmount(&terminal_data);
		while (terminal_return != 0)
		{
			terminal_return = getTransactionAmount(&terminal_data);
		}

		//Set Maximum Amount
		terminal_return = setMaxAmount(&terminal_data);
		while (terminal_return != 0)
		{
			terminal_return = setMaxAmount(&terminal_data);
		}

		terminal_return = isBelowMaxAmount(&terminal_data);
		if (terminal_return != 0)
		{
			//Transaction Declined Restart Program
			break;
		}

		/***********Server Module Start***********/

		//Pass all card and terminal data to server
		transaction_data.terminalData = terminal_data;
		transaction_data.cardHolderData = card_data;


		//Check Account validity
		//Check Amount availability
		//Update balance and Save transaction
		server_transState_return = recieveTransactionData(&transaction_data);
		break;
	}
}

int main()
{
	
	while (1)
	{
		printf("Application Start\n");
		printf("\n");
		appStart();
		printf("Thank You\n");
		printf("\n");
	}
	return 0;
}



//Fuction testing
//int main()
//{	
// struct ST_cardData_t card_data;
//EN_cardError_t card_return;
//
//struct ST_terminalData_t terminal_data;
//EN_terminalError_t terminal_return;
//
//struct ST_transaction_t transaction_data;
//EN_transState_t server_transState_return;
//EN_serverError_t server_error_return;
//	
//		
//	/************Card Module Check************/
//	
//	card_return = getCardHolderName(&card_data);
//	printf("%d\n", card_return);
//
//	card_return = getCardExpiryDate(&card_data);
//	printf("%d\n", card_return);
//	
//	card_return = getCardPAN(&card_data);
//	printf("%d\n", card_return);
//	
//	/***********Terminal Module Check***********/
//	
//	terminal_return = getTransactionDate(&terminal_data);
//	printf("%d\n", terminal_return);
//
//	terminal_return = isCardExpired(card_data,terminal_data);
//	printf("%d\n", terminal_return);
//
//	/*terminal_return = isValidCardPAN(&card_data);
//	printf("%d\n", terminal_return);*/
//	
//	terminal_return = getTransactionAmount(&terminal_data);
//	printf("%d\n", terminal_return);
//
//	terminal_return = setMaxAmount(&terminal_data);
//	printf("%d\n", terminal_return);
//
//	terminal_return = isBelowMaxAmount(&terminal_data);
//	printf("%d\n", terminal_return);
//	
//
//	/***********Server Module Check***********/
//
//	server_error_return = isValidAccount(&card_data);
//	printf("%d\n", server_error_return);
//
//	server_error_return = isAmountAvailable(&terminal_data);
//	printf("%d\n", server_error_return);
//
//	transaction_data.terminalData = terminal_data;
//	transaction_data.cardHolderData = card_data;
//
//	server_error_return = saveTransaction(&transaction_data);
//	printf("%d\n", server_error_return);
//
//
//	server_transState_return = recieveTransactionData(&transaction_data);
//	printf("%d\n", server_transState_return);
//	
//	while (1)
//	{
//
//	}
//	return 0;
//}

