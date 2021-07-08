void adcinit()								 //151014
{
 PINSEL1=0X15000000;
 AD0CR=0X00210600;// ADC CONTROL REGISTER

}
unsigned long int as1()
{
 AD0CR&=0XFFFFFF00;
 AD0CR|=0X01000002;
 delay(500);
 return ((AD0DR1 >> 6) & 0x03FF);
}
unsigned long int as2()
{
 AD0CR&=0XFFFFFF00;
 AD0CR|=0X01000004;
 delay(500);
 //while(!(AD0DR2&&0X80000000));
 return((AD0DR2 >> 6) & 0x03FF);
}
unsigned long int as3()
{
 AD0CR&=0XFFFFFF00;
 AD0CR|=0X01000008;
delay(500);
 //while(!(AD0DR3&&0X80000000));
 return((AD0DR3 >> 6) & 0x03FF);
}
