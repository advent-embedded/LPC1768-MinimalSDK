#ifndef __UART_H__
#define __UART_H__

#include<LPC17xx.h>
void uart_init(void);
void uart_puts(char *);
void uart_putc(unsigned char);
void uart_getc(unsigned char *);
unsigned char uart_gets(char *);
void uart_init()
{
	uint32_t Fdiv;
	LPC_PINCON->PINSEL0 = 0x00000050;
    LPC_UART0->LCR = 0x83;        /* 8 bits, no Parity, 1 Stop bit */
    Fdiv = (SystemCoreClock/4/16 ) / 115200 ;	/*baud rate, Fpclk: 18MHz */
    LPC_UART0->DLM = Fdiv / 256;							
    LPC_UART0->DLL = Fdiv % 256;
    LPC_UART0->LCR &= ~(0x80);        /* DLAB = 0 */
    LPC_UART0->FCR = 0x07;        /* Enable and reset TX and RX FIFO. */

}
void uart_putc(unsigned char ch)
{
	while((LPC_UART0->LSR & 0x20)==00);
	LPC_UART0->THR=ch;

}

void uart_puts(char *str)
{
	while(*str != '\0')
		uart_putc(*(str++));
}
void uart_getc(unsigned char *data)
{

while((LPC_UART0->LSR & 0x01)!=0x01);

*data= (LPC_UART0->RBR);

}
void uart_num(unsigned short int num)
{
unsigned char r=0,j=0,y=0,a[6];
while(num>0)
{
r=num%10;
a[j]=r;
j++;
num=num/10;
}
for(y=j-1;y!=255;y--)
uart_putc(a[y]+48);
}

unsigned char uart_gets(char *str)
{
unsigned char ch;
do
{
uart_getc(&ch);
//uart_putc(ch);
if(ch==13)
break;
*str=ch;
str++;
}while(ch!=13);
*str='\0';
return 1;
}
#endif
