/********************************************************************************
* Target: Cortex-M3, LPC1768 @ 96 MHz
* Compiler: arm-gcc, Codesourcery Lite
**********************************************************************************/
#ifndef _RTC_H_
#define _RTC_H_
#include"iic.h"

uint8_t bcdtodecimal(uint8_t num)
{
	return ((((num & 0xF0) >> 4) * 10) + (num & 0x0F));
}
uint8_t decimaltobcd(uint8_t num)
{
	return (((num / 10) << 4) | (num % 10));
}

void rtc_write(unsigned char addr,unsigned char data)
{

i2c_start();

sla_w();   //Master Transmit Mode

i2c_sendregaddrerss(addr);

i2c_senddata(data);

i2c_stop();
}


void rtc_read(unsigned char addr,unsigned char *data)  
{
	i2c_start();
	sla_w();
	//getstatus(0x18);
	i2c_sendregaddrerss(addr);
	i2c_repeatstart();
	sla_r();
	i2c_getdata(data);
	i2c_stop();
}

void rtc_init(void)
{
unsigned char temp;
rtc_read(0x02,&temp);
temp|=0x40;                 //Enable 12-hour Format
rtc_write(0x02,temp);
}
void rtc_set(
unsigned char hour, //1-12
unsigned char minute, //0-59
unsigned char second,  //1-12
unsigned char session, //AM or PM 1-Pm ,0-AM
unsigned char date,  //1-31
unsigned char month, //1-12
unsigned char year,   //0-99
unsigned char dow   //1-7
)
{
unsigned char temp;

rtc_read(0x00,&temp);
temp&=~0x7F;
temp|=decimaltobcd(second);
rtc_write(0x00,temp);

rtc_read(0x01,&temp);
temp&=~0x7F;
temp|=decimaltobcd(minute);
rtc_write(0x01,temp);

rtc_read(0x02,&temp);
temp&=~0x1F;
temp|=decimaltobcd(hour);
if(session)
temp|=0x20;
else
temp&=~0x20;
rtc_write(0x02,temp);

rtc_read(0x03,&temp);
temp&=~0x07;
temp|=decimaltobcd(dow);
rtc_write(0x03,temp);

rtc_read(0x04,&temp);
temp&=~0x3F;
temp|=decimaltobcd(date);
rtc_write(0x04,temp);

rtc_read(0x05,&temp);
temp&=~0x1F;
temp|=decimaltobcd(month);
rtc_write(0x05,temp);

rtc_read(0x06,&temp);
temp&=~(0xFF);
temp=decimaltobcd(year);
rtc_write(0x06,temp);
}

#endif

