#include<lpc214x.h>
#include"lcd.h"
#include"gpio.h"
#include"serial.h"
#include"adc.h"

#define echo    P1_17		     //p1.17


unsigned int aaa;
unsigned int w,j,cnt=0,count=0,rate=0;
unsigned long int x=0,y=0,z=0;
unsigned char t,tl,th,uh,h,hrh,hrl;


  void pin()
{
 PINSEL0=0x00050005;//SELECTING PIN OPERATION
 PINSEL1=0x15000000;
 PINSEL2=0x00000000;
 IODIR0 =0xFFFFFFFF;// as output	
 IODIR0&=~((1<<20)|(1<<21)|(1<<2)|(1<<2));
 IODIR1&=~(1<<17);
 IOCLR1 =0xFFFFFFFF;
 IOPIN1 =0x0;
 AD0CR  =0x00210600;// ADC0 CONTROL REGISTER

}
char inp0(unsigned long int pinNumber)
{
	unsigned long int pinBlockState =IOPIN0;
	int pinState = (pinBlockState & (pinNumber)) ? 1 : 0;
	return pinState;
}
char inp1(unsigned long int pinNumber)
{
   unsigned long int pinBlockState=IOPIN1;
  int pinState = (pinBlockState &(pinNumber)) ? 1 : 0;
  return pinState;
}

void delay_ms(int l)
{
unsigned char k;

for(;l;l--)
for(k=122;k<=0;k--);
}
int main()
{
			
			pin();
			IODIR1=0XFFFFFFFF;

			IODIR1&=~((1<<20)|(1<<21));
			IODIR1&=~(1<<17);
			initlcd();
			adcinit();
			delay(50);


			ser_init_1(0x61,0x00);  //9600 baudrate
			ser_init_0(0x61,0x00);
			IO1SET=0X00030000;
			clcd(0x01);delay(10);
			stringlcd(0x80,"  IOT-HEALTH ");
			stringlcd(0xC0,"  MONITORING ");
			delay(2000);
		
while(1)
{
					t=0;tl=0;th=0;uh=0;h=0;hrh=0;
					count=0;cnt=0;
					for(w=0;w<10;w++)
					{
					x=as1();								
					
					if(x>103)
					{
						x=102;
					}
					if(x<97)
					{
						x=97;
					}
					stringlcd(0x01,"BodyTemp:");conv(x);	 						//P0.29 X-AXIS
					delay(1000);
					
					if(x>102)
					{
						th=1;stringlcd(0x01,"Body Temp High");delay(500);
					}
					if((x>98)&&(x<102))
					{
						stringlcd(0x01,"Body Temp Normal ");delay(500);
					}

					  		
					aaa=IOPIN1;
					aaa=aaa & 0x00100000;											//p1.21	 light/sw	 
					if(aaa!=0x00100000)
					{	
					stringlcd(0x01,"beats read...");
					delay(1000);
					count=0;rate=0;
							for(j=0;j<71;j++)
							{	
							while((inp1(echo)==1));
							while(inp1(echo)==0)
							{
								stringlcd(0x01,"*HR*");
								count++;
								delay_ms(10);
								conv(count);
								delay_ms(10);
							}
							
							}	
							delay(50);
							stringlcd(0xc0,"beats:");	
							clcd(0xC7);
							conv(count);
							delay(200);
							if(count>82)
							{
								hrh=1;
								stringlcd(0x01,"heart rate high");
								delay(1000);
							}
					}
									
		
				} //end for loop	
					
stringlcd(0x01," DATA UPDATING ");delay(50);
delay(1000);

string_0("AT+CPIN?\r\n");
delay(5000);

string_0("AT+SAPBR=3,1,\"CONTYPE\" ,\"GPRS\" \r\n");
delay(5000);

string_0("AT+SAPBR=3,1,\"APN\",\"airtelgprs.com \"\r\n");
//string_0("AT+SAPBR=3,1,\"APN\",\"live.vodafone.com \"\r\n");
delay(5000);

string_0("AT+SAPBR=1,1\r\n");
delay(5000);

string_0("AT+HTTPINIT \r\n");
delay(5000);

string_0("AT+HTTPPARA=\"CID\",1\r\n");
delay(5000);

string_0("AT+HTTPPARA=\"URL\",\"http://bosembedded.com/GPRS/res10.asp?data=PATIENT_Details:");
																		
delay(5000);
string_0("BODY_TEMP:");
conv_serial_0(x);string_0(",");

string_0("HEART_RATE:");
conv_serial_0(count);string_0(",");
if(th==1)
{string_0("Bodytemphigh");string_0(",");}
else
{string_0("Normal");}


///////////////////////////////////////////////////////////////////////

///delay(5000);
string_0("\"\r\n");
delay(5000);
string_0("AT+HTTPACTION=0\r\n");

delay(5000);

string_0("AT+HTTPREAD\r\n");

delay(5000);

string_0("AT+HTTPTERM\r\n");

delay(5000);

			}		//END OF WHILE

	 
 }


