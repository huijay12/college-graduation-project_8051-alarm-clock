
#ifndef __I2C_H
#define __I2C_H

// Define i2c pins
sbit SDA = P0^0;		// Data pin for i2c
sbit SCL = P0^1;		// Clock pin for i2c



//Function Declarations
void I2C_Clock(void);
void I2C_Start();
void I2C_Stop(void);
void I2C_Write(unsigned char);
unsigned char I2C_Read(void);
void I2C_Ack();
void I2C_NoAck();

#endif
