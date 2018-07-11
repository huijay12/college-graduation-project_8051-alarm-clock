#include "Includes.h"

/*************************小蜜蜂樂譜陣列************************/
code unsigned int music_Table[]={G,24,E,24,E,48,F,24,D,24,D,48,C,24,D,24,E,24,F,24,G,24,G,24,G,48
,G,24,E,24,E,48,F,24,D,24,D,48,C,24,E,24,G,24,G,24,E,72
,D,24,D,24,D,24,D,24,D,24,E,24,F,48,E,24,E,24,E,24,E,24,E,24,F,24,G,48,
G,24,E,24,E,48,F,24,D,24,D,48,C,24,E,24,G,24,G,24,C,72,end};

unsigned int buttonSignal= 0, bbb=0;

unsigned char   z=0;    //資料計數 
unsigned int voice_Now;

unsigned char i=0,j=0, k=0, l=0, nullIsFound=0, tableNum=0;
xdata unsigned char lcd_day[15] = "";	//日期陣列
//unsigned char lcd_time[15] = "";	//時間陣列
//unsigned char received[20];


unsigned char receiving;   //是否接收藍芽訊息flag
xdata unsigned char receivString[20];  //接收藍芽用字串

/*******************************************************************************/
//規定 EEPROM中	的鬧鐘表
//	no	 星期	   時	分	isset
//	1  0x11~0x17  0x18 0x19 0x1A
//	2  0x21~0x27  0x28 0x29 0x2A
//	.
//	.
//	.
//  10 0xA1~0xA7  0xA8 0xA9 0xAA
//
// if "value == 0xAA means null, 0xBB means isset
/*******************************************************************************/

unsigned char mode=0x00, h1=0x00, h2=0x00, h3=0x00, m1=0x00, m2=0x00, m3=0x00, Y1=0x00, Y2=0x00, Y3=0x00, Mon1=0x00, 
              Mon2=0x00, Mon3=0x00, D1=0x00, D2=0x00, D3=0x00, wd1=0x00;

unsigned char alsec=0x00, almin=0xAA, alhour=0xAA, alweekday[8];

//變數鬧鐘表: 1~7星期  8時 9分 10isset
xdata unsigned char altable[11][11];

void resSetting();
void UART_int();				//宣告UART中斷服務程式
void bee();


// Main function
void main()
{	

	unsigned char sec,min,hour,day,month,year,weekday;


	EA=1;          //致能整體中斷

	TMOD=0x21;	//設定Timer1在mode2	 Timer0在mode1
	PCON=PCON&0x7f;	//清除SMOD
	TH1=0xFD;	//設定baud rate=9600
	TR1=1;		//啟動Timer1

	SCON=0x50;	//UART Mode1,REN=1
	IP=0x10;	//設定UART中斷為高優先權,PS=1
	IE=0x90;	//致能UART中斷,EA=1 & ES=1

	
	ET0= 1;

  /* Initilize the lcd before displaying any thing on the lcd */
    LCD_Init();

  /* Initilize the RTC(ds1307) before reading or writing time/date */
    DS1307_Init();


  /*Set the time and Date only once */
   //DS1307_SetTime(0x23,0x59,0x00);  //  10:40:20
   //DS1307_SetDate(Thursday,0x14,0x08,0x14);  //  Thur 14th July 2014
   //DS1307_SetDate(0x14,0x08,0x14); 

	LCD_DisplayString("Loading...");

   ///////////////////////////////////////////////////////////////////////////第一次要先設定EEPROM && 全部清空
	/* for(i=1; i<=10; i++)							
		for(j=1; j<=10; j++)
			eewrite(i*16+j, 0xAA);				 
	  */


	P11 = button;



	//////////////////////////////////////////////////////////////////////////////////////////////////////////////   
	for(i=1; i<=10; i++)								//從EEPROM讀出整個鬧鐘表  丟進陣列							 
		for(j=1; j<=10; j++)
			altable[i][j] = eeread(j+16*i);

//altable[i][j] = 0xAA;
			
	/////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////
	//
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////

    for(i=0; i<50; i++){write_pos(60);}   //馬達定位
	resSetting();



   /* Display the Time and Date continously */ 
   while(receiving==0)
    {

		P11 = button;

	    LCD_GoToLineOne();
 		LCD_DisplayString("    ");

	   /* Read the Time from RTC(ds1307) */
        DS1307_GetTime(&hour,&min,&sec);        

		/* Display the time on Firstline-7th position*/
        LCD_GoToXY(0,4); 		 
        LCD_DisplayRtcTime(hour,min,sec);

   		/* Display "Date" on Second line*/
  		LCD_GoToLineTwo();
  		//LCD_DisplayString("Date: ");

	    /* Read the Date from RTC(ds1307) */ 
        DS1307_GetDate(&weekday,&day,&month,&year);   
		//DS1307_GetDate(&day,&month,&year);       

		/* Display the Date on Secondline-7th position*/
        LCD_GoToXY(1,0); 

		LCD_DisplayString("  ");

		LCD_DisplayRtcDate(day,month,year);	
	
		switch(weekday)
		{
			case Monday:	LCD_DisplayString("  MON ");	break;
			case Tuesday:	LCD_DisplayString("  TUE ");	break;
			case Wednesday:	LCD_DisplayString("  WED ");	break;
			case Thursday:	LCD_DisplayString("  THU ");	break;
			case Friday:	LCD_DisplayString("  FRI ");	break;
			case Saturday:	LCD_DisplayString("  SAT ");	break;
			case Sunday:	LCD_DisplayString("  SUN ");	break;

			default: LCD_DisplayString("  ???");	break;
		}


	//j=0x01;
	for(i=1;i<=10;i++)		 //鬧鐘星期判斷
  	{
		 if(altable[i][weekday] == 0xBB)
		 {
		 	//鬧鐘時間判斷
		 	if(altable[i][8]==hour && altable[i][9]==min && sec==0)
		 	{

				for(k=0; k<20; k++){write_pos(90);}
				for(k=0; k<40; k++){write_pos(60);}
				k=0;
				resSetting();

				delay_ms(1000);

				//button = 0;
				buttonSignal = 0;

		 		LCD_GoToLineTwo();
		    	LCD_DisplayString("                ");
		    	LCD_GoToLineOne();
				LCD_DisplayString("alarm clock!!!");
				while(buttonSignal==0){bee();}			 //嗡嗡嗡  嗡嗡嗡
				buttonSignal = 0;
				LCD_GoToLineOne();
				LCD_DisplayString("                ");
				
				//delay_ms(50000);
			
		 	} //end of if

		  } //end of if

		////////////////////	j++;

	}  //end of for

			delay_ms(1000);
	  }  //endofwhile	
  

}

/******************************************************
中斷副程式：UART_int() interrupt 4
******************************************************/
void UART_int() interrupt 4
{


	if(RI==1)	//若RI=1,為接收中斷
	{
			receiving = 1;

			receivString[k] = SBUF;
	
			k++;    
	}

	  if(receivString[k-1] == 0x23)	// if == "#"
	  {
		
		LCD_GoToLineOne();
		LCD_DisplayString("                ");
		LCD_GoToLineTwo();
		LCD_DisplayString("                ");
		LCD_GoToLineOne();

		for(j=0;j<k;j++)
		LCD_DataWrite(receivString[j]);



		/*************解析App訊號******************/

		mode = receivString[0];
		h1 = receivString[1];
		h2 = receivString[2];	
		m1 = receivString[3];
		m2 = receivString[4];

		h1 = h1 - 0x30;
		h2 = h2 - 0x30;
		m1 = m1 - 0x30;
		m2 = m2 - 0x30;

		h3 = ((h1 << 4) & 0xf0) | (h2 & 0x0f) ;
		m3 = ((m1 << 4) & 0xf0) | (m2 & 0x0f) ;
	
	   
		switch(mode)
		{
		
			case 0x61:   //"a"

				//for迴圈1~10在鬧鐘陣列裡找出空位   鬧鐘設進去
				for(l=1; l<=10; l++)
				{
					if(altable[l][10] == 0xAA)
					{
					 	tableNum = l;
						nullIsFound = 1;
						break;
					 }
				
				}	

				////////////////////////////////////////////////////////////////if nullIsFound != 1???   沒空位了咧??
				
				altable[tableNum][8] = h3;			
				altable[tableNum][9] = m3;				

	            //鬧鐘設定資料寫入EEPROM
				eewrite(8+tableNum*16,h3);
				eewrite(9+tableNum*16,m3);
				eewrite(10+tableNum*16,0xBB);


				/*設定星期~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				
				 k = 5;							 //若沒設星期，視為每天都響

				 if(receivString[k] == 0x23){
				 
				 	for(l=1; l<=7; l++){
					
						altable[tableNum][l] = 0xBB;
						eewrite(l+tableNum*16,0xBB);
					}
				 }


				 while(receivString[k] != 0x23)  //while != "#"
				 {
				 	 
				 	switch(receivString[k])
					{
						 case 0x31:	              	//Mon is set
							altable[tableNum][1] = 0xBB;
							eewrite(1+tableNum*16,0xBB);		//eewrite(MonAddress, isset)
						 	break;
					
						 case 0x32:	              	//Tue is set
						 	altable[tableNum][2] = 0xBB;
							eewrite(2+tableNum*16,0xBB);		//eewrite(TueAddress, isset)
						 	break;
					
						 case 0x33:	              	//Wed is set
						 	altable[tableNum][3] = 0xBB;
							eewrite(3+tableNum*16,0xBB);		//eewrite(WedAddress, isset)
						 	break;
					
						 case 0x34:	              	//Thur is set
						 	altable[tableNum][4] = 0xBB;
							eewrite(4+tableNum*16,0xBB);		//eewrite(ThhurAddress, isset)
						 	break;
					
						 case 0x35:	              	//Fri is set
							altable[tableNum][5] = 0xBB;
							eewrite(5+tableNum*16,0xBB);		//eewrite(FriAddress, isset)
						 	break;
					
						 case 0x36:	              	//Sat is set
						 	altable[tableNum][6] = 0xBB;
							eewrite(6+tableNum*16,0xBB);		//eewrite(SatAddress, isset)
						 	break;
					
						 case 0x37:	              	//Sun is set
						 	altable[tableNum][7] = 0xBB;
							eewrite(7+tableNum*16,0xBB);		//eewrite(SunAddress, isset)
						 	break;
					
					}
					altable[tableNum][10] = 0xBB;
					

					k++;
				 
				 }
				/*設定星期~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		   
				break;


			case 0x62:   //"b"	                                                //送亮燈訊號給小球
		
				
				buttonSignal = 1 ;



				break;


			case 0x63:   //"c"                                                    //金手指，清空所有鬧鐘

				for(i=1; i<=10; i++)												 
					for(j=1; j<=10; j++){
						  eewrite(i*16+j, 0xAA);
						  altable[i][j] = 0xAA;
					}

				break;


			case 0x64:   //"d"

				for(l=0; l<=10; l++)
				{
					 if(altable[l][8] == h3 && altable[l][9] == m3)		////////////////////////////////////沒看星期喔/////////////////
					 {
					 	 tableNum = l;
					 	 break;
					   }   
				 }	//end for


				 for(l=1; l<=7; l++)
					altable[tableNum][l] = 0xAA;

				 for(l=1; l<=7; l++)
				    eewrite(tableNum*16+l,0xAA);

				 altable[tableNum][10] = 0xAA;
				 eewrite(tableNum*16+10,0xAA);

				break;

		
			case 0x6D:   //"m"

				 for(l=1; l<=10; l++)
				{
					 if(altable[l][8] == h3 && altable[l][9] == m3)		 	////////////////////////////////////沒看星期喔/////////////////
					 {
					 	 tableNum = l;
					 	 break;
					   }   
				 }	//end for

				k=5;

				while(receivString[k] != 0x2A)
				k++;						 // 抓到"*"

				k++;

				h1 = receivString[k++];
				h2 = receivString[k++];	
				m1 = receivString[k++];
				m2 = receivString[k++];

				h1 = h1 - 0x30;
				h2 = h2 - 0x30;
				m1 = m1 - 0x30;
				m2 = m2 - 0x30;

				h3 = ((h1 << 4) & 0xf0) | (h2 & 0x0f) ;
				m3 = ((m1 << 4) & 0xf0) | (m2 & 0x0f) ;

				altable[tableNum][8] = h3;			
				altable[tableNum][9] = m3;				

	            //鬧鐘設定資料寫入EEPROM
				eewrite(8+tableNum*16,h3);
				eewrite(9+tableNum*16,m3);

				for(l=1; l<=7; l++)
					altable[tableNum][l] = 0xAA;

				 for(l=1; l<=7; l++)
				    eewrite(tableNum*16+l,0xAA);


				/*設定星期~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				
				 while(receivString[k] != 0x23)  //while != "#"
				 {
				 	 
				 	switch(receivString[k])
					{
						 case 0x31:	              	//Mon is set
							altable[tableNum][1] = 0xBB;
							eewrite(1+tableNum*16,0xBB);		//eewrite(MonAddress, isset)
						 	break;
					
						 case 0x32:	              	//Tue is set
						 	altable[tableNum][2] = 0xBB;
							eewrite(2+tableNum*16,0xBB);		//eewrite(TueAddress, isset)
						 	break;
					
						 case 0x33:	              	//Wed is set
						 	altable[tableNum][3] = 0xBB;
							eewrite(3+tableNum*16,0xBB);		//eewrite(WedAddress, isset)
						 	break;
					
						 case 0x34:	              	//Thur is set
						 	altable[tableNum][4] = 0xBB;
							eewrite(4+tableNum*16,0xBB);		//eewrite(ThhurAddress, isset)
						 	break;
					
						 case 0x35:	              	//Fri is set
							altable[tableNum][5] = 0xBB;
							eewrite(5+tableNum*16,0xBB);		//eewrite(FriAddress, isset)
						 	break;
					
						 case 0x36:	              	//Sat is set
						 	altable[tableNum][6] = 0xBB;
							eewrite(6+tableNum*16,0xBB);		//eewrite(SatAddress, isset)
						 	break;
					
						 case 0x37:	              	//Sun is set
						 	altable[tableNum][7] = 0xBB;
							eewrite(7+tableNum*16,0xBB);		//eewrite(SunAddress, isset)
						 	break;
					
					}
					
					k++;
				 
				 }
				/*設定星期~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


				break;


		
		    case 0x69:   //"i"

				Y1 = receivString[5];
				Y2 = receivString[6];
				Mon1 = receivString[7];
				Mon2 = receivString[8];
				D1 = receivString[9];
				D2 = receivString[10];
				wd1= receivString[11];
				
				Y1 = Y1 - 0x30;
				Y2 = Y2 - 0x30;
				Mon1 = Mon1 - 0x30;
				Mon2 = Mon2 - 0x30;
				D1 = D1 - 0x30;
				D2 = D2 - 0x30;
				wd1 = wd1 - 0x30;	
				
				Y3 = ((Y1 << 4) & 0xf0) | (Y2 & 0x0f) ;
				Mon3 = ((Mon1 << 4) & 0xf0) | (Mon2 & 0x0f) ;
				D3 = ((D1 << 4) & 0xf0) | (D2 & 0x0f);
				wd1 = ((wd1 << 4) & 0xf0) | (wd1 & 0x0f);	
				
				DS1307_SetTime(h3,m3,0x00);  // hour min sec 
   				DS1307_SetDate(wd1,D3,Mon3,Y3);  //	weekday day mon year					

				break;


			

		}

		/*************解析App訊號******************/

		LCD_GoToLineOne();					    //清除接收訊號畫面
		LCD_DisplayString("                "); 

		for(i=0; i<=k; i++)
		  receivString[i] = " ";

		k = 0;

		//delay_ms(10000);

		receiving = 0;

	   }	 //end of IF(receivString[k-1] == "#")

  

	   RI=0;	//清除接收中斷旗標

	
	if(TI==1)
		TI=0;	//若RI=0,為傳送中斷,清除傳送中斷旗標
}
/*******************************************************
*******************************************************/

void bee(){
	
		   
	 
			//SW1 ON 播放
			while(music_Table[z] != 0)
			{


				//buttonSignal = button;
				//if(buttonSignal == 1)
				//break;
				
				
				bbb = button;
				if(buttonSignal == 1 || bbb ==1){
					buttonSignal = 1;
					break;}

				voice_Now = music_Table[z];
				//音頻資料存入計數值
				TL0 = voice_Now;
				TH0 = voice_Now>>8;								
				TR0 = 1;//啟動計時				
				delay(music_Table[z+1]*18);//延時,發音的時間				
				TR0 = 0;//停止timer0計時
				
				delay(1);
				z+=2;
			}
	
			z = 0;
}


/*******************************************************
*******************************************************/


//Time0中斷函數
void voice_T1_int(void) interrupt 1
{
	if(voice_Now==s)
		Speaker = 1;
	else{
		
		//重新設定計時值
		TL0 = voice_Now;
		TH0 = voice_Now>>8;
		Speaker= ~Speaker;
		
		}
	}


/***********************************************/
//暫存器設定
void resSetting(void)
{

	EA=1;          //致能整體中斷

	TMOD=0x21;	//設定Timer1在mode2	 Timer0在mode1
	PCON=PCON&0x7f;	//清除SMOD
	TH1=0xFD;	//設定baud rate=9600
	TR1=1;		//啟動Timer1

	SCON=0x50;	//UART Mode1,REN=1
	IP=0x10;	//設定UART中斷為高優先權,PS=1
	IE=0x90;	//致能UART中斷,EA=1 & ES=1

	
	ET0= 1;


}