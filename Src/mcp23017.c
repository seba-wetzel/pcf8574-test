/*
 * mcp23017.c
 *
 *  Created on: 11 sep. 2019
 *      Author: seba
 */
#include "mcp23017.h"

static I2C_HandleTypeDef * I2C;
static uint8_t i2caddr = 0;
static uint8_t data = 0;

/**
 * Bit number associated to a give Pin
 */
uint8_t bitForPin(uint8_t pin){
	return pin%8;
}

/**
 * Register address, port dependent, for a given PIN
 */
uint8_t regForPin(uint8_t pin, uint8_t portAaddr, uint8_t portBaddr){
	return(pin<8) ?portAaddr:portBaddr;
}

void writeRegister(uint8_t regAddr, uint8_t regValue){
	uint8_t temp [] = {regAddr, regValue};

	HAL_I2C_Master_Transmit((I2C_HandleTypeDef*) I2C, (uint16_t)(i2caddr), &temp, 2, 350);
//	wiresend(regAddr);
//	wiresend(regValue);
//	Wire.endTransmission();
}

/**
 * Helper to update a single bit of an A/B register.
 * - Reads the current register value
 * - Writes the new register value
 */
void updateRegisterBit(uint8_t pin, uint8_t pValue, uint8_t portAaddr, uint8_t portBaddr) {
	uint8_t regValue;
	uint8_t regAddr=regForPin(pin,portAaddr,portBaddr);
	uint8_t bit=bitForPin(pin);
	regValue = readRegister(regAddr);

	// set the value for the particular bit
	bitWrite(regValue,bit,pValue);

	writeRegister(regAddr,regValue);
}


/**
 * Reads a given register
 */
uint8_t readRegister(uint8_t addr){
	// read the current GPINTEN
//	Wire.beginTransmission(MCP23017_ADDRESS | i2caddr);
//	wiresend(addr);
//	Wire.endTransmission();
//	Wire.requestFrom(MCP23017_ADDRESS | i2caddr, 1);
//	return wirerecv();
	HAL_I2C_Master_Receive((I2C_HandleTypeDef*) I2C, (uint16_t)(i2caddr), &data, 2, 350);
	return data;
}

// Functions for Arduino like
void begin(I2C_HandleTypeDef * I2C_Handler, uint8_t addr) {

	I2C = I2C_Handler;
	i2caddr = addr<<1;

	// all inputs on port A and B
	writeRegister(MCP23017_IODIRA,0xff);
	writeRegister(MCP23017_IODIRB,0xff);
}

/**
 * Sets the pin mode to either INPUT or OUTPUT
 */
void pinMode(uint8_t p, uint8_t d) {
	updateRegisterBit(p,(d==INPUT),MCP23017_IODIRA,MCP23017_IODIRB);
}

/**
 * Enable a pullUp resistor for a given pin
 */
void pullUp(uint8_t p, uint8_t d) {
	updateRegisterBit(p,d,MCP23017_GPPUA,MCP23017_GPPUB);
}


uint8_t digitalRead(uint8_t pin) {
	uint8_t bit=bitForPin(pin);
	uint8_t regAddr=regForPin(pin,MCP23017_GPIOA,MCP23017_GPIOB);
	return (readRegister(regAddr) >> bit) & 0x1;
}




