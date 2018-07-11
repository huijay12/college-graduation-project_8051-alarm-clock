#include "Includes.h"

void eewrite(unsigned char rom_address, unsigned char write_data){
	unsigned int ii;
	I2C_Start();
	write_8bit(0xA0);
	I2C_Ack();
	//write_8bit(rom_addressHigh);
	//EEI2C_ACK();
	//write_8bit(rom_addressLow);
	//EEI2C_ACK();
	write_8bit(rom_address);
	I2C_Ack();
	write_8bit(write_data);
	I2C_Ack();
	I2C_Stop();
	// Delay only
	for(ii=0;ii<100;ii++){
		delay_us(1000);
	}
}

void write_8bit(wData){
	unsigned char i;
	SCL = 0;
	delay_us(1000);
	for(i=0;i<8;i++)
	{
		if((wData & 0x80 ) == 0x80)
			SDA = 1;
		else
		SDA = 0;
		delay_us(1000);
		SCL = 1;
		delay_us(1000);
		SCL = 0;
		delay_us(1000);
		wData=wData<<1;
	}
	SDA = 1;
	delay_us(1000);
	SCL = 1;
	delay_us(1000);
}


unsigned char eeread(unsigned char read_address){
	unsigned char read_data;
	I2C_Start();
	write_8bit(0xA0);
	I2C_Ack();
	//write_8bit(rom_addressHigh);
	//EEI2C_ACK();
	//write_8bit(rom_addressLow);
	//EEI2C_ACK();
	 write_8bit(read_address);
	 I2C_Ack();
	I2C_Start();
	write_8bit(0xA1);
	I2C_Ack();
	read_data = read_8bit();
	I2C_Ack();
	I2C_Stop();
	return (read_data);
}

unsigned char read_8bit(void){
	unsigned char rdata,i;
	rdata = 0x00;
	for(i=0;i<8;i++){
		rdata = rdata<<1;
		SDA = 1;
		delay_us(1000);
		SCL = 0;
		delay_us(1000);
		SCL = 1;
		delay_us(1000);
		if(SDA==1)
		rdata|=0x01;
	}
	return (rdata);
}