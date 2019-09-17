/*
 * mcp23017.h
 *
 *  Created on: 11 sep. 2019
 *      Author: seba
 */

#ifndef MCP23017_H_
#define MCP23017_H_

#include "stm32f1xx_hal.h"

#define MCP23017_ADDRESS 0x20 //Direction default

// Registros
#define MCP23017_IODIRA 0x00
#define MCP23017_IPOLA 0x02
#define MCP23017_GPINTENA 0x04
#define MCP23017_DEFVALA 0x06
#define MCP23017_INTCONA 0x08
#define MCP23017_IOCONA 0x0A
#define MCP23017_GPPUA 0x0C
#define MCP23017_INTFA 0x0E
#define MCP23017_INTCAPA 0x10
#define MCP23017_GPIOA 0x12
#define MCP23017_OLATA 0x14

#define MCP23017_IODIRB 0x01
#define MCP23017_IPOLB 0x03
#define MCP23017_GPINTENB 0x05
#define MCP23017_DEFVALB 0x07
#define MCP23017_INTCONB 0x09
#define MCP23017_IOCONB 0x0B
#define MCP23017_GPPUB 0x0D
#define MCP23017_INTFB 0x0F
#define MCP23017_INTCAPB 0x11
#define MCP23017_GPIOB 0x13
#define MCP23017_OLATB 0x15

#define MCP23017_INT_ERR 255


#define lowByte(w) ((uint8_t) ((w) & 0xff))
#define highByte(w) ((uint8_t) ((w) >> 8))

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

typedef enum{
	INPUT,
	OUTPUT
} pinModeIO;

typedef enum{
	LOW,
	HIGH
} pinModeState;

//Functions prototypes for communication
uint8_t bitForPin(uint8_t);
uint8_t regForPin(uint8_t , uint8_t , uint8_t );
void writeRegister(uint8_t, uint8_t);
void updateRegisterBit(uint8_t, uint8_t, uint8_t, uint8_t);
uint8_t readRegister(uint8_t);

//Functions prototypes for hardware abstraction
void begin(I2C_HandleTypeDef * ,uint16_t);
void pinMode(uint8_t, uint8_t);
void pullUp(uint8_t, uint8_t);
uint8_t digitalRead(uint8_t);

#endif /* MCP23017_H_ */
