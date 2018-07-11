#ifndef __EEPROM_H
#define __EEPROM_H


void eewrite(unsigned char rom_address, unsigned char write_data);
unsigned char eeread(unsigned char read_address);
void write_8bit(unsigned char wData);
unsigned char read_8bit(void);




#endif