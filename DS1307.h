
#ifndef __DS1307_H
#define __DS1307_H


// Define DS1307 i2c device address
#define Device_Address_DS1307_EEPROM	0xD0

// Define Time Modes
#define AM_Time					0
#define PM_Time					1
#define TwentyFourHoursMode		2

// Define days
#define Monday		0x01
#define Tuesday		0x02
#define Wednesday	0x03	
#define Thursday	0x04
#define Friday		0x05
#define Saturday	0x06
#define Sunday		0x07

// Function Declarations
void DS1307_Init();
void DS1307_Write(unsigned char);
unsigned char DS1307_Read();
void DS1307_SetTime(unsigned char, unsigned char, unsigned char);
void DS1307_SetDate(unsigned char, unsigned char, unsigned char, unsigned char);
//void DS1307_SetDate(unsigned char, unsigned char, unsigned char);
void DS1307_GetTime(unsigned char *,unsigned char *,unsigned char *);
void DS1307_GetDate(unsigned char *,unsigned char *,unsigned char *,unsigned char *);

#endif