/*
 * pcf8574.h
 *
 *  Created on: Jul 22, 2019
 *      Author: seba
 */

#ifndef PCF8574_H_
#define PCF8574_H_
#ifdef __cplusplus
extern "C" {
#endif

/* Defines ------------------------------------------------------------------*/
#define delay(x) HAL_Delay(x)

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

uint8_t digitalRead(uint8_t);
static void I2C_PCF8574_Read(void);
void initPCF8574 (I2C_HandleTypeDef * , uint8_t );

#ifdef __cplusplus
}
#endif
#endif /* PCF8574_H_ */
