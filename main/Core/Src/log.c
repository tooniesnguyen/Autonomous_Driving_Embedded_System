/*
 * log.c
 *
 *  Created on: Mar 2, 2024
 *      Author: Human Gem
 */

#include "log.h"

char txLogBuffer[100] = {0};
UART_HandleTypeDef *targetUART;

static HAL_StatusTypeDef checkNull(){
	if(targetUART != NULL) return HAL_OK;
	return HAL_ERROR;
}

void log_Init(UART_HandleTypeDef *huart){

	targetUART = huart;
}

void log_TransmitCompleteHandle(UART_HandleTypeDef *huart){
	if(huart != targetUART) return;
	memset(txLogBuffer,0,strlen(txLogBuffer));

}

void log_SendString(){
	if(checkNull() != HAL_OK) return;
	txLogBuffer[strlen(txLogBuffer) -1] = '\n';  //xóa dấu phẩy cuối cùng, thay bằng \n
	HAL_UART_Transmit_IT(targetUART, (uint8_t*)txLogBuffer, strlen(txLogBuffer));
}


void log_AddHeaderArgumentToBuffer(char *name){
	char s[10] = {0};
	strcpy(s,name);
	sprintf(txLogBuffer+strlen(txLogBuffer),"%s,",s);
}

void log_AddArgumentToBuffer_float(float data){
	sprintf(txLogBuffer+strlen(txLogBuffer),"%.2f,",data);
}
