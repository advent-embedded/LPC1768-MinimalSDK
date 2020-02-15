/********************************************************************************
* Target: Cortex-M3, LPC1768 @ 96 MHz
* Compiler: arm-gcc, Codesourcery Lite
**********************************************************************************/
#ifndef __IIC_H__
#define __IIC_H__

#define SLA_ADDR 0xD0
#define I2EN 6
#define STA 5
#define STO 4
#define SI 3
#define AA 2

#define I2ENC 6
#define STAC 5
#define SIC 3
#define AAC 2

void i2c_init(void);
void i2c_start(void);
void sla_r(void);
void sla_w(void);
void i2c_getdata(unsigned char *);
void i2c_stop();
void i2c_senddata(unsigned char);
void getstatus(unsigned char desired)
{
lcd_setcursor(0,5);
do
{
//lcd_puthex(LPC_I2C1->I2STAT);
}while(LPC_I2C1->I2STAT != desired);
}
void i2c_init()
{
LPC_SC->PCLKSEL1&= ~(3<<6);
LPC_PINCON->PINSEL0|= 0x0F;
LPC_PINCON->PINMODE0 &=~(0x0F);
LPC_PINCON->PINMODE0 |=0x0A;
LPC_PINCON->PINMODE_OD0|=(0x03);
LPC_I2C1->I2CONCLR = (1<<I2ENC)|(1<<STAC)|(1<<SIC)|(1<<AAC); 
LPC_I2C1 -> I2SCLL   = 120;
LPC_I2C1 -> I2SCLH   = 120;

//LPC_I2C1 -> I2CONSET |=(1<<2);
}
void i2c_start() //START Bit
{
LPC_I2C1 -> I2CONSET =(1<<I2EN);
LPC_I2C1 ->I2CONSET |=(1<<STA); 
while((LPC_I2C1->I2STAT) != 0x08);
LPC_I2C1->I2CONCLR=(1<<STAC)|(1<<SIC);
}


void sla_w() //Send Slave Address in Write Mode; Master Transmitter
{
LPC_I2C1->I2DAT=SLA_ADDR;
while((LPC_I2C1->I2STAT) != 0x18);
LPC_I2C1->I2CONCLR=(1<<SIC);
LPC_I2C1->I2CONSET |= (1<<AA); 
}

void sla_r() //Send Slave Address in Read Mode; Master Receiver
{
LPC_I2C1->I2DAT=0xD1;
while((LPC_I2C1->I2STAT) != 0x40);
LPC_I2C1->I2CONCLR=(1<<SIC);
LPC_I2C1->I2CONSET |= (1<<AA); 
}

void i2c_sendregaddrerss(unsigned char addr) //Sending Register Address in Master Transmitter Mode
{
LPC_I2C1->I2DAT=addr;
while((LPC_I2C1->I2STAT) != 0x28);
LPC_I2C1->I2CONCLR=(1<<SIC);
}
void i2c_repeatstart() //Repeat Start, Switching from Master Transmitter to Master Receiver
{
LPC_I2C1 ->I2CONSET |=(1<<STA); 
while((LPC_I2C1->I2STAT) != 0x10);
LPC_I2C1->I2CONCLR=(1<<STAC)|(1<<SIC);
}

void i2c_getdata(unsigned char *val) // Get Data from Slave
{
while((LPC_I2C1->I2STAT) != 0x50);
	LPC_I2C1->I2CONCLR = (1<<SIC);
	*val=LPC_I2C1->I2DAT;
}
void i2c_senddata(unsigned char data)
{
LPC_I2C1->I2DAT=data;
while((LPC_I2C1->I2STAT) != 0x28);
LPC_I2C1->I2CONCLR=(1<<SIC);
}
void i2c_stop()
{
LPC_I2C1->I2CONSET =(1<<STO);
LPC_I2C1->I2CONCLR = (1<<SIC);
//while( LPC_I2C1->I2CONSET & (1<<STO) );   
LPC_I2C1 -> I2CONCLR =(1<<I2ENC);
//LPC_I2C1 -> I2CONSET =(1<<I2EN);
}
#endif
