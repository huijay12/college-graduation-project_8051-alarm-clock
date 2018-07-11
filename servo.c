#include "Includes.h"

void write_pos(int position){

int msec;

switch(position){

	case 60:
		msec = 30;
		//while(!RI){
		servo_signal1 = 1;
		set_timer(msec);
		servo_signal1 = 0;
		set_timer(675 -msec);//}
		//RI = 0;
	break;

	case 90:
		msec = 60;
		//while(!RI){
		servo_signal1 = 1;
		set_timer(msec);
		servo_signal1 = 0;
		set_timer(667 -msec);//}
		//RI = 0;
	break;

	case 120:
		msec = 90;
		//while(!RI){
		servo_signal1 = 1;
		set_timer(msec);
		servo_signal1 = 0;
		set_timer(667 -msec);
		//}

	//RI = 0;
	break;
	//default:
	//;
	}	  //end switch

}      //end write_pos



									   
void set_timer(int x){		//time=50us*x

	int a;
	// To run the loop given below once it takes approx 50us
	// Since I have already used the timer 1 for serial communication, I use
	// the timer 0 to give PWM signal to the servo motor.

	for(a=0;a<x;a++)		   
	{
		
			TMOD=0x22;
			TH0=0xFF;
			//TL0=0x00;
			//TL0=0xE9;
			TL0=0xD1;

			TR0=1;
			while(TF0==0);
			TF0=0;
			TR0=0;	 
		
	}
}			  
