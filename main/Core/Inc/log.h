/*
 * log.h
 *
 *  Created on: Mar 2, 2024
 *      Author: Human Gem
 */

#ifndef INC_LOG_H_
#define INC_LOG_H_

#include "main.h"
#include "string.h"
#include "stdio.h"

#include "main.h"
#include "string.h"
#include "stdio.h"

typedef enum DataType{
	TYPE_UINT8,
	TYPE_INT,
	TYPE_FLOAT,
	TYPE_UINT32,
}DataType;


void log_Init(UART_HandleTypeDef *huart);
void log_TransmitCompleteHandle(UART_HandleTypeDef *huart);
void log_AddArgumentToBuffer_float(float data);
void log_AddHeaderArgumentToBuffer(char *name);
void log_SendString();
#endif /* INC_LOG_H_ */
