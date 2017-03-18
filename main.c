#include<reg51.h> 
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "lcd4a.c"
#include "dht11.h"
#include "serial.h"

	
	
unsigned int I_RH,D_RH,I_Temp,D_Temp,CheckSum;  //dht11 variables
unsigned char temp[20],hum[20],cs[10];


int hr ,hr1=21;                       /* rtc variables */
int min,min1=30;
int sec,sec1=0,dig_am_pm=0;
int k;



void delay1(unsigned int msec)   // Time delay funtion
{
int i,j ;
for(i=0;i<msec;i++)
  for(j=0;j<1275;j++);
}


void lcd_data_int(int time_val)   // Function to send number on LCD
{

int int_amt;
int_amt=time_val/10;
LCD_Char(int_amt+48);
int_amt=time_val%10; 
LCD_Char(int_amt+48);
}


void Receive_data()
{
	I_RH=Receive()	;	  		
	D_RH=Receive()	 ; 
	I_Temp=Receive() ;        
	D_Temp=Receive()	 ; 
	CheckSum=Receive() ;      
}

void Dht_Print()
{
	sprintf(temp,"TEM = %d.%d ",I_Temp,D_Temp);   
	LCD_Command(0xC0);
	LCD_String(temp);
	LCD_String(" C");
	sprintf(hum,"HUM = %d.%d ",I_RH,D_RH);
	LCD_Command(0x94);
	LCD_String(hum);
	LCD_String(" %");
	sprintf(cs," CS = %d",CheckSum);
	LCD_Command(0xD4);
	LCD_String(cs);
}

void Dht11_call()
{
	Request();			
	Response();			
	Receive_data();
	Dht_Print();
}


void serial_call()
{
	Serial_Init();
	Tx_Write(temp);
	Tx_Byte(0x0A);
	Tx_Byte(0x0D);
	Tx_Write(hum);
	Tx_Byte(0x0A);
	Tx_Byte(0x0D);
	delay_sec(10);
	
}	

void main()
{
	LCD_Init();
	LCD_Command(0x80);
	LCD_String("DATE:17/02");
	while(1)
	{
		for(k=0;k<2;k++)
  {
   for(hr=hr1;hr<24;hr++)
   {
    for(min=min1;min<60;min++)
     {
      for(sec=0;sec<60;sec++)
      {
       LCD_Command(0x8A);
       delay1(1);
				LCD_String("TIME:");
       lcd_data_int(hr);
				LCD_Char(':');
       lcd_data_int(min); 
       delay1(100);
		
		
	     Dht11_call();
				serial_call();
			}
		}
	}
}
	}
}	