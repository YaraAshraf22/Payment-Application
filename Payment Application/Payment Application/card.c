#include "card.h"
#include "data_types.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	printf("Please Enter Card Holder Name\n");

	gets(cardData->cardHolderName);
	uint8_t str_length=strlen(cardData->cardHolderName);
	if (str_length <= 24 && str_length >= 20)
	{
		printf("CARD OK\n");
		return CARD_OK;
	}
	else if (str_length == NULL)
	{
		printf("WRONG NAME\n");
		return WRONG_NAME;
	}
	else
	{
		printf("WRONG NAME\n");
		return WRONG_NAME;
	}

}
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	printf("Please Enter Card Expiry Date\n");
	gets(cardData->cardExpirationDate);
	uint8_t str_length = strlen(cardData->cardExpirationDate);

	uint8_t  month[3], year[3];
	uint8_t  month_num = 0, year_num = 0;


	if (str_length == 5 && cardData->cardExpirationDate[2]=='/')
	{
		if (isdigit(cardData->cardExpirationDate[0]) && isdigit(cardData->cardExpirationDate[1]) && isdigit(cardData->cardExpirationDate[3]) && isdigit(cardData->cardExpirationDate[4]))
		{
			
			strncpy_s(month, sizeof(month), &(cardData->cardExpirationDate[0]), 2);
			month_num = atoi(month);

			strncpy_s(year, sizeof(year), &(cardData->cardExpirationDate[3]), 2);
			year_num = atoi(year); 
			
			if ( (month_num <= 12 && month_num > 0) && (year_num >= 22))
			{
				printf("CARD OK\n");
				return CARD_OK;
			}
			else
			{
				printf("WRONG EXP DATE\n");
				return WRONG_EXP_DATE;
			}
			
		}
		else
		{
			printf("WRONG EXP DATE\n");
			return WRONG_EXP_DATE;
		}
			
	}
	else
	{
		printf("WRONG EXP DATE\n");
		return WRONG_EXP_DATE;
	}

}
EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	printf("Please Enter Your Primary Account Number\n");
	gets(cardData->primaryAccountNumber);
	uint8_t str_length = strlen(cardData->primaryAccountNumber);
	uint8_t i;

	if (str_length >= 16 && str_length <= 19)
	{
		for (i = 0; i < str_length; i++) //check if alphanumeric
		{
			if (!(isalpha(cardData->primaryAccountNumber[i]) || isdigit(cardData->primaryAccountNumber[i])))
			{
				printf("WRONG PAN\n");
				return WRONG_PAN;
			}
			
		}
		printf("CARD OK\n");
		return CARD_OK;
	}
	else
	{
		printf("WRONG PAN\n");
		return WRONG_PAN;
	}
}
