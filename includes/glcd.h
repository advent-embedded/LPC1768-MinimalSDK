/*************************************************************
* Author: Kannan P
* E-Mail: kannanetech@gmail.com
* Target: Cortex-M3, LPC1768 @ 96 MHz
*************************************************************/
#ifndef __GLCD_H__
#define __GLCD_H__
#include<delay.h>
/* ========================================
 * Pin 1 (VCC) 			--> 	3.3V	
 * Pin 2 (GND) 			--> 	GND
 * Pin 3 (CE) 			--> 	P0.8 (CS Pin - chip select, enable data transfer)
 * Pin 4 (RST) 			--> 	P0.7  (RESET pin)
 * Pin 5 (D/C) 			--> 	P0.6  (MODE pin - Command/Data)
 * Pin 6 (MOSI) 		--> 	P0.5  (DATA pin)
 * Pin 7 (SCLK) 		--> 	P0.4  (CLOCK pin)
 * Pin 8 (LED) 			--> 	180E to 3.3V
 *
 ========================================== */
//#include<lpc_types.h>
			
#define CS 19			
#define CLK 22			
#define DATA 21			
#define RST 18		
#define MODE 20			

#define MODE_CMD 0
#define MODE_DATA 1

unsigned char  font[][6] =
{
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // sp
    { 0x00, 0x00, 0x00, 0x2f, 0x00, 0x00 },   // !
    { 0x00, 0x00, 0x07, 0x00, 0x07, 0x00 },   // "
    { 0x00, 0x14, 0x7f, 0x14, 0x7f, 0x14 },   // #
    { 0x00, 0x24, 0x2a, 0x7f, 0x2a, 0x12 },   // $
    { 0x00, 0x62, 0x64, 0x08, 0x13, 0x23 },   // %
    { 0x00, 0x36, 0x49, 0x55, 0x22, 0x50 },   // &
    { 0x00, 0x00, 0x05, 0x03, 0x00, 0x00 },   // '
    { 0x00, 0x00, 0x1c, 0x22, 0x41, 0x00 },   // (
    { 0x00, 0x00, 0x41, 0x22, 0x1c, 0x00 },   // )
    { 0x00, 0x14, 0x08, 0x3E, 0x08, 0x14 },   // *
    { 0x00, 0x08, 0x08, 0x3E, 0x08, 0x08 },   // +
    { 0x00, 0x00, 0x00, 0xA0, 0x60, 0x00 },   // ,
    { 0x00, 0x08, 0x08, 0x08, 0x08, 0x08 },   // -
    { 0x00, 0x00, 0x60, 0x60, 0x00, 0x00 },   // .
    { 0x00, 0x20, 0x10, 0x08, 0x04, 0x02 },   // /
    { 0x00, 0x3E, 0x51, 0x49, 0x45, 0x3E },   // 0
    { 0x00, 0x00, 0x42, 0x7F, 0x40, 0x00 },   // 1
    { 0x00, 0x42, 0x61, 0x51, 0x49, 0x46 },   // 2
    { 0x00, 0x21, 0x41, 0x45, 0x4B, 0x31 },   // 3
    { 0x00, 0x18, 0x14, 0x12, 0x7F, 0x10 },   // 4
    { 0x00, 0x27, 0x45, 0x45, 0x45, 0x39 },   // 5
    { 0x00, 0x3C, 0x4A, 0x49, 0x49, 0x30 },   // 6
    { 0x00, 0x01, 0x71, 0x09, 0x05, 0x03 },   // 7
    { 0x00, 0x36, 0x49, 0x49, 0x49, 0x36 },   // 8
    { 0x00, 0x06, 0x49, 0x49, 0x29, 0x1E },   // 9
    { 0x00, 0x00, 0x36, 0x36, 0x00, 0x00 },   // :
    { 0x00, 0x00, 0x56, 0x36, 0x00, 0x00 },   // ;
    { 0x00, 0x08, 0x14, 0x22, 0x41, 0x00 },   // <
    { 0x00, 0x14, 0x14, 0x14, 0x14, 0x14 },   // =
    { 0x00, 0x00, 0x41, 0x22, 0x14, 0x08 },   // >
    { 0x00, 0x02, 0x01, 0x51, 0x09, 0x06 },   // ?
    { 0x00, 0x32, 0x49, 0x59, 0x51, 0x3E },   // @
    { 0x00, 0x7C, 0x12, 0x11, 0x12, 0x7C },   // A
    { 0x00, 0x7F, 0x49, 0x49, 0x49, 0x36 },   // B
    { 0x00, 0x3E, 0x41, 0x41, 0x41, 0x22 },   // C
    { 0x00, 0x7F, 0x41, 0x41, 0x22, 0x1C },   // D
    { 0x00, 0x7F, 0x49, 0x49, 0x49, 0x41 },   // E
    { 0x00, 0x7F, 0x09, 0x09, 0x09, 0x01 },   // F
    { 0x00, 0x3E, 0x41, 0x49, 0x49, 0x7A },   // G
    { 0x00, 0x7F, 0x08, 0x08, 0x08, 0x7F },   // H
    { 0x00, 0x00, 0x41, 0x7F, 0x41, 0x00 },   // I
    { 0x00, 0x20, 0x40, 0x41, 0x3F, 0x01 },   // J
    { 0x00, 0x7F, 0x08, 0x14, 0x22, 0x41 },   // K
    { 0x00, 0x7F, 0x40, 0x40, 0x40, 0x40 },   // L
    { 0x00, 0x7F, 0x02, 0x0C, 0x02, 0x7F },   // M
    { 0x00, 0x7F, 0x04, 0x08, 0x10, 0x7F },   // N
    { 0x00, 0x3E, 0x41, 0x41, 0x41, 0x3E },   // O
    { 0x00, 0x7F, 0x09, 0x09, 0x09, 0x06 },   // P
    { 0x00, 0x3E, 0x41, 0x51, 0x21, 0x5E },   // Q
    { 0x00, 0x7F, 0x09, 0x19, 0x29, 0x46 },   // R
    { 0x00, 0x46, 0x49, 0x49, 0x49, 0x31 },   // S
    { 0x00, 0x01, 0x01, 0x7F, 0x01, 0x01 },   // T
    { 0x00, 0x3F, 0x40, 0x40, 0x40, 0x3F },   // U
    { 0x00, 0x1F, 0x20, 0x40, 0x20, 0x1F },   // V
    { 0x00, 0x3F, 0x40, 0x38, 0x40, 0x3F },   // W
    { 0x00, 0x63, 0x14, 0x08, 0x14, 0x63 },   // X
    { 0x00, 0x07, 0x08, 0x70, 0x08, 0x07 },   // Y
    { 0x00, 0x61, 0x51, 0x49, 0x45, 0x43 },   // Z
    { 0x00, 0x00, 0x7F, 0x41, 0x41, 0x00 },   // [
    { 0x00, 0x55, 0x2A, 0x55, 0x2A, 0x55 },   // 55
    { 0x00, 0x00, 0x41, 0x41, 0x7F, 0x00 },   // ]
    { 0x00, 0x04, 0x02, 0x01, 0x02, 0x04 },   // ^
    { 0x00, 0x40, 0x40, 0x40, 0x40, 0x40 },   // _
    { 0x00, 0x00, 0x01, 0x02, 0x04, 0x00 },   // '
    { 0x00, 0x20, 0x54, 0x54, 0x54, 0x78 },   // a
    { 0x00, 0x7F, 0x48, 0x44, 0x44, 0x38 },   // b
    { 0x00, 0x38, 0x44, 0x44, 0x44, 0x20 },   // c
    { 0x00, 0x38, 0x44, 0x44, 0x48, 0x7F },   // d
    { 0x00, 0x38, 0x54, 0x54, 0x54, 0x18 },   // e
    { 0x00, 0x08, 0x7E, 0x09, 0x01, 0x02 },   // f
    { 0x00, 0x18, 0xA4, 0xA4, 0xA4, 0x7C },   // g
    { 0x00, 0x7F, 0x08, 0x04, 0x04, 0x78 },   // h
    { 0x00, 0x00, 0x44, 0x7D, 0x40, 0x00 },   // i
    { 0x00, 0x40, 0x80, 0x84, 0x7D, 0x00 },   // j
    { 0x00, 0x7F, 0x10, 0x28, 0x44, 0x00 },   // k
    { 0x00, 0x00, 0x41, 0x7F, 0x40, 0x00 },   // l
    { 0x00, 0x7C, 0x04, 0x18, 0x04, 0x78 },   // m
    { 0x00, 0x7C, 0x08, 0x04, 0x04, 0x78 },   // n
    { 0x00, 0x38, 0x44, 0x44, 0x44, 0x38 },   // o
    { 0x00, 0xFC, 0x24, 0x24, 0x24, 0x18 },   // p
    { 0x00, 0x18, 0x24, 0x24, 0x18, 0xFC },   // q
    { 0x00, 0x7C, 0x08, 0x04, 0x04, 0x08 },   // r
    { 0x00, 0x48, 0x54, 0x54, 0x54, 0x20 },   // s
    { 0x00, 0x04, 0x3F, 0x44, 0x40, 0x20 },   // t
    { 0x00, 0x3C, 0x40, 0x40, 0x20, 0x7C },   // u
    { 0x00, 0x1C, 0x20, 0x40, 0x20, 0x1C },   // v
    { 0x00, 0x3C, 0x40, 0x30, 0x40, 0x3C },   // w
    { 0x00, 0x44, 0x28, 0x10, 0x28, 0x44 },   // x
    { 0x00, 0x1C, 0xA0, 0xA0, 0xA0, 0x7C },   // y
    { 0x00, 0x44, 0x64, 0x54, 0x4C, 0x44 },   // z
    { 0x00,0x00, 0x06, 0x09, 0x09, 0x06 }    // horiz lines
};

void lcd_init(void);
void lcd_clear(void);
void lcd_setcursor(uint8_t , uint8_t);
void lcd_putchar(char);
void lcd_write_command(uint8_t);
void lcd_putstring(char *);
void lcd_write_byte(uint8_t,uint8_t);
void lcd_write_data(uint8_t);
void lcd_write_command(uint8_t);
void lcd_image(unsigned char *);
void lcd_num(unsigned long int);
/*void lcd_status(Bool);

void lcd_status(Bool flag)
{
if(flag==TRUE)
lcd_putstring("TRUE");
else
lcd_putstring("FALSE");
}*/

void lcd_init()
{
LPC_GPIO1-> FIODIR =(1<<CS)|(1<<CLK)|(1<<DATA)|(1<<RST)|(1<<MODE);
LPC_GPIO1-> FIOSET =(1<<CS)|(1<<CLK)|(1<<DATA)|(1<<MODE);

LPC_GPIO1->FIOCLR =(1<<RST);
delayus(50);
LPC_GPIO1->FIOSET|=(1<<RST);

	lcd_write_command(0x21); //Functionset- Extended Instruction Set
	lcd_write_command(0xc6); // SetVop
	lcd_write_command(0x06);  // Set Temp coefficent. 
	lcd_write_command(0x13); // LCD Bias System 1:48. //0x13
	lcd_write_command(0x20); //FunctionSet- PD=0/Chip Active, V=0/Horizantal Addressing, H=0/Basic Instruction Set
	lcd_clear();
	lcd_write_command(0x0c); //Display Control in Normal Mode DE=10
}
void lcd_clear( void)
{
	uint8_t i,j;
	for(i=0;i<6;i++)
		for(j=0;j<84;j++)
			lcd_write_data(0);
}
void lcd_write_command(uint8_t data)
{
	lcd_write_byte(data, MODE_CMD);
}
void lcd_write_data(uint8_t data)
{
	lcd_write_byte(data, MODE_DATA);
}
void lcd_write_byte(uint8_t data, uint8_t lcd_mode)
{
uint8_t i;
LPC_GPIO1->FIOCLR|=(1<<CS);

	if (lcd_mode==MODE_CMD)
		LPC_GPIO1->FIOCLR|=(1<<MODE);
	else
		LPC_GPIO1->FIOSET|=(1<<MODE);

	for(i=0; i<8; i++)
	{
 	if(data&0x80)
		{LPC_GPIO1->FIOSET|=(1<<DATA);}
	else
		{LPC_GPIO1->FIOCLR|=(1<<DATA);}

	data = data<<1;
		LPC_GPIO1->FIOCLR|=(1<<CLK);
		delayus(5);
		LPC_GPIO1->FIOSET|=(1<<CLK);
	}
LPC_GPIO1->FIOSET|=(1<<CS);
}
void lcd_putchar(char c)
{
	uint8_t i;
	unsigned char ch = 0;
	for(i=0;i<6;i++)
	{
		ch = font[c-32][i];
		lcd_write_data(ch);
		//lcd_write_data((print_mode==LCD_PRINT_NORMAL)? ch: (ch^ 0xff));
	}
}

void lcd_putstring(char *string)
{
 
  while(*string != '\0')
  {
    lcd_putchar( *string);
    string++;
  }
}
void lcd_image(unsigned char *image)
{
unsigned int i;
for(i=0;i<504;i++)
lcd_write_data(*image++);
}
void lcd_setcursor(uint8_t x, uint8_t y)
{
	lcd_write_command(0x40|y); //Y increments in rows of 8 pixels
	lcd_write_command(0x80|x * 6); // X increments in pixels
}
void lcd_num(unsigned long int num)
{
unsigned char r=0,j=0,y=0,a[10];
while(num>0)
{
r=num%10;
a[j]=r;
j++;
num=num/10;
}
for(y=j-1;y!=255;y--)
lcd_putchar(a[y]+48);
}

#endif
