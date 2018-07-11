#ifndef __LCD_H
#define __LCD_H

//*******************
//Pin description
/*
P2.4 to P2.7 is data bus
P1.0 is RS
P1.1 is E
*/
//********************

// Defines Pins
sbit rs = P0^2;
sbit en  = P0^3;
sbit rw  = P0^6;

#define databus	P2 

// Constants
#define E_Delay       250       

// Function Declarations
void LCD_Init();
void LCD_CmdWrite(char);
void LCD_DataWrite(char);
void LCD_Clear();
void LCD_GoToLineOne();
void LCD_GoToLineTwo();
void LCD_GoToXY(char, char);
void LCD_DisplayString(char *);
void LCD_ScrollMessage(char *);
void LCD_DisplayNumber(unsigned int);
void LCD_DisplayRtcTime(char, char, char);
void LCD_DisplayRtcDate(char, char, char);

#endif