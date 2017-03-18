#include<reg51.h>

void Serial_Init()
{
	TMOD = 0x20;		  
	TH1 = 0xFD;			  
	SCON = 0x50;			 
	TR1 = 1;			    
}

void Tx_Byte(unsigned char tx_data)
{
	SBUF = tx_data;		
	while (TI==0);		
	TI = 0;				    
}

void Tx_Write(unsigned char *str)
{
  while(*str)
   {
    Tx_Byte(*str);
    str++;
   }
}	

 void delay_sec(unsigned char j)
 {
   unsigned char j1;
   unsigned int i;
   
   for(j1=0;j1<j;j++)
   {
     for(i=0;i<1000;i++)
	 {
	   TMOD=0x01;
	   TH0=0xFC;
	   TL0=0x67;
	   TR0=1;
	   while(!TF0);
	   TF0=0;
	   }
    }
 }	   
