#include "terminal.h"
#include "data_types.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	printf("Please Enter Transaction Date\n");
	gets(termData->transactionDate);

	uint8_t str_length = strlen(termData->transactionDate);

	uint8_t day[3], month[3], year[5];
	uint8_t day_num = 0, month_num = 0;
	uint16_t year_num = 0;
	//DD/MM/YYYY
	if (str_length == 10 && termData->transactionDate[2] == '/' && termData->transactionDate[5] == '/')
	{
		//if digits
		if (isdigit(termData->transactionDate[0]) && isdigit(termData->transactionDate[1]) && isdigit(termData->transactionDate[3]) && isdigit(termData->transactionDate[4]) && isdigit(termData->transactionDate[6]) && isdigit(termData->transactionDate[7]) && isdigit(termData->transactionDate[8]) && isdigit(termData->transactionDate[9]))
		{


			strncpy_s(day,sizeof(day),&(termData->transactionDate[0]), 2);
			day_num = atoi(day); 
			
			strncpy_s(month, sizeof(month),&(termData->transactionDate[3]), 2);
			month_num = atoi(month); 
			
			strncpy_s(year, sizeof(year),&(termData->transactionDate[6]), 4);
			year_num = atoi(year); 

			if (((day_num <= 31 && day_num > 0)) && (month_num <= 12 && month_num > 0) && (year_num >= 2022) )
			{
				printf("TERMINAL OK\n");
				return TERMINAL_OK;
			}
			else
			{
				printf("WRONG DATE\n");
				return WRONG_DATE;
			}
			
		}
		else
		{
			printf("WRONG DATE\n");
			return WRONG_DATE;
		}
	}
	else
	{
		printf("WRONG DATE\n");
		return WRONG_DATE;
	}

}
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{
	uint8_t month_exp[3], year_exp[5], month_trans[3], year_trans[5];
	uint8_t month_num_exp = 0, year_num_exp = 0, month_num_trans = 0, year_num_trans = 0; 
	
	//Extract Card Expiry Date MM/YY
	strncpy_s(month_exp, sizeof(month_exp), &(cardData.cardExpirationDate[0]), 2);
	month_num_exp = atoi(month_exp);

	strncpy_s(year_exp, sizeof(year_exp), &(cardData.cardExpirationDate[3]), 2);
	year_num_exp = atoi(year_exp);

	//Extract Terminal Transaction Date DD/MM/YYYY
	strncpy_s(month_trans, sizeof(month_trans), &(termData.transactionDate[3]), 2);
	month_num_trans = atoi(month_trans);

	strncpy_s(year_trans, sizeof(year_trans), &(termData.transactionDate[8]), 2);
	year_num_trans = atoi(year_trans);

	if (year_num_trans < year_num_exp)
	{
		printf("TERMINAL OK\n");
		return TERMINAL_OK;
	}
	else if (year_num_trans == year_num_exp && month_num_trans < month_num_exp)
	{
		printf("TERMINAL OK\n");
		return TERMINAL_OK;
		
	}
	else if (year_num_trans == year_num_exp && month_num_trans == month_num_exp)
	{
		printf("DECLINED - EXPIRED CARD\n");
		return EXPIRED_CARD;
	}
	else if (year_num_trans >= year_num_exp)
	{
		printf("DECLINED - EXPIRED CARD\n");
		return EXPIRED_CARD;
	}

}
EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData)
{
	uint8_t valid = 0;
	valid = getCardPAN(cardData->primaryAccountNumber);
	if (valid == 0)
	{
		printf("TERMINAL OK\n");
		return TERMINAL_OK;
	}
	else
	{
		printf("INVALID CARD PAN\n");
		return INVALID_CARD;
	}
}
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	printf("Please Enter Transaction Amount\n");
	scanf_s("%f", &(termData->transAmount));
	if ((termData->transAmount) > 0)
	{
		printf("TERMINAL OK\n");
		return TERMINAL_OK;
	}
	else
	{
		printf("INVALID AMOUNT\n");
		return INVALID_AMOUNT;
	}

}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	if ((termData->transAmount) > (termData->maxTransAmount))
	{
		printf("DECLINED - EXCEEDS MAX ALLOWED AMOUNT\n");
		return EXCEED_MAX_AMOUNT;
	}
	else
	{
		printf("TERMINAL OK\n");
		return TERMINAL_OK;
	}
}
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
	printf("Please Enter Max Transaction Amount\n");
	scanf_s("%f", &(termData->maxTransAmount));

	if ((termData->maxTransAmount) <= 0)
	{
		printf("INVALID MAX AMOUNT\n");
		return INVALID_MAX_AMOUNT;
	}
	else
	{
		printf("TERMINAL OK\n");
		return TERMINAL_OK;
	}
}

