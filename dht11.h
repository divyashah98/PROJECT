#include<reg51.h> 
#include<stdio.h>
#include<string.h>
#include<stdlib.h>


sbit DHT11=P2^1;		   


void timer_delay20ms()		
{
  TMOD = 0x01;
  TH0 = 0xB8;				
  TL0 = 0x0C;				
  TR0 = 1;				
  while(TF0 == 0);	    
  TR0 = 0;			
  TF0 = 0;				
}

void timer_delay30us()      
{
  TMOD = 0x01;			
  TH0 = 0xFF;			
  TL0 = 0xF1;			
  TR0 = 1;			
  while(TF0 == 0);	    
  TR0 = 0;			
  TF0 = 0;			
}

void Request()			    
{
  DHT11 = 0;		    
  timer_delay20ms();         
  DHT11 = 1;		    
}

void Response()			    
{
  while(DHT11==1);
  while(DHT11==0);
  while(DHT11==1);
}

int Receive()		  	
{
  unsigned int q,c=0;	
  for (q=0; q<8; q++)
     {
       while(DHT11==0);	
       timer_delay30us();
       if(DHT11 == 1)		
       c = (c<<1)|(0x01);	
       else				
       c = (c<<1);
       while(DHT11==1);
     }
	return c;
}

