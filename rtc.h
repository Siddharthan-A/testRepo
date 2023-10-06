//speed setting
#define cclk 60000000
#define pclk  cclk/4
#define speed  100000
#define loadval  ((pclk/speed)/2)


//fun dec
void bcd_ascii(unsigned char );
void eeprom_write(unsigned char ,unsigned char ,unsigned char );
unsigned char eeprom_read(unsigned char ,unsigned char );
void start(void);
void stop(void);
void write(unsigned char );
unsigned char nack(void);
void restart(void);
void i2c_init(void);
unsigned char mastack(void);
void eeprom_page_write(unsigned char ,unsigned char ,unsigned char *,int);
void eeprom_page_read(unsigned char ,unsigned char ,unsigned  char *,int);



// int main()
// {
// 	unsigned char c;
// 	int n;
// 	//lcd_init();
// 	i2c_init();
// 	uart0_config();
// 	

// eeprom_write(0x68,0x02,0x04);	
// eeprom_write(0x68,0x01,0x03);	
// eeprom_write(0x68,0x00,0x02);
// delay_ms(100);

// 	while(1){
// c=eeprom_read(0x68,0x02);
// 	delay_ms(1000);
// 	n=(c&0x3f);
// 	bcd_ascii(n);
// 		uart0_tx(':');
// 		uart0_tx(' ');

// 	
// 	c=eeprom_read(0x68,0x01);
// 	delay_ms(1000) ;
// 	 n=(c&0x7f);
// 	bcd_ascii(n);
// 	
// 	uart0_tx(':');
// 	uart0_tx(' ');
// 		c=eeprom_read(0x68,0x00);
// 	delay_ms(1000);
// 	n=(c&0x7f);
// 	bcd_ascii(n);
// 		uart0_tx('\n');
// 		uart0_tx(' ');

// }


//congig i2c
void i2c_init(void)
{

PINSEL0|=0x50;
	
	I2SCLH=loadval;
	I2SCLL=loadval;
	I2CONSET=1<<6;

}
	


//restart con bus
void restart(void)
{
I2CONSET=1<<5;
I2CONCLR=1<<3;
while(((I2CONSET>>3)&1)==0);
I2CONCLR=1<<5;
}


//start con
void start(void)
{
I2CONSET=1<<5;
while(((I2CONSET>>3)&1)==0);
I2CONCLR=1<<5;
}


//stop con
void stop(void)
{
I2CONSET=1<<4;
I2CONCLR=1<<3;

}

//write in eeprom
void eeprom_write(unsigned char dev,unsigned char word_add,unsigned char c)
{		start();
		write(dev<<1);
		write(word_add);
		write(c);
		stop();
		delay_ms(10);
}

//data trans
void write(unsigned char bdata)
{
I2DAT=bdata;
	I2CONCLR=1<<3;
while(((I2CONSET>>3)&1)==0);

}

//read eeprom
unsigned char eeprom_read(unsigned char dev,unsigned char word_add)
{	
	unsigned char data1;
	start();
	write(dev<<1);
		write(word_add);
	restart();
	write((dev<<1)|1);
		//write(word_add);
	data1=nack();
	stop();
	return data1;
}


unsigned char nack(void)
{	
	I2CONSET=0x00;
	I2CONCLR=1<<3;
	while(((I2CONSET>>3)&1)==0);
return I2DAT;
	
}



void eeprom_page_write(unsigned char dev,unsigned char word_add,unsigned char *c,int nbytes)
{	
	int i;
	start();
	write(dev<<1);
		write(word_add);
	for(i=0;i<nbytes;i++)
	write(c[i]);
stop();
	delay_ms(10);

}


void eeprom_page_read(unsigned char dev,unsigned char word_add,unsigned char *p,int nbytes)
{	
	int i;
	start();
	write(dev<<1);
		write(word_add);
	restart();
	write(dev<<1|1);
	for(i=0;i<nbytes;i++)
	p[i]=mastack();
	//p[i]=nack();
stop();
	//delay_ms(10);

}



unsigned char mastack(void)
{
	I2CONSET=1<<2;
	I2CONCLR=1<<3;
	while((I2CONSET>>3&1)==0);
	I2CONCLR=1<<2;
	return I2DAT;


}
void bcd_ascii(unsigned char data2)
{

	

	uart0_tx((data2/16)+48);
	uart0_tx((data2%16)+48);
	

}



