/*
 * pcf8574.c
 *
 *  Created on: Jul 22, 2019
 *      Author: seba
 */
#include "pcf8574.h"

I2C_HandleTypeDef * I2C;
uint8_t dir = 0;
uint8_t data = 0;


uint8_t digitalRead (uint8_t pin){
	I2C_PCF8574_Read();
	/* Read and return the pin state */
	return (~data & (1 << pin)) ? 1u : 0u;
}

static void I2C_PCF8574_Read (void){
	  while (HAL_I2C_Master_Receive((I2C_HandleTypeDef*) I2C, (uint16_t)(dir<<1), &data, 2, 350) != HAL_OK){
			delay(10);
	  }
}

uint8_t digitalWrite (uint8_t pin, uint8_t state){
	return 0;
}

void initPCF8574 (I2C_HandleTypeDef * I2C_Handler, uint8_t ADDR){
	I2C = I2C_Handler;
	dir = ADDR;
}
