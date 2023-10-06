#ifndef __SPI_DEFINES_H__
#define __SPI_DEFINES_H__

#define CS 7

//defines for clock /baudrate

#define FOSC 12000000
#define CCLK (5*FOSC)
#define PCLK (CCLK/4)
#define SPCCR_VAL 60
#define SPI_RATE (u8)(PCLK/SPCCR_VAL)

// SPCR Bits Setting 
#define Mode_0     0x00  // CPOL 0 CPHA 0
#define Mode_1     0x08  // CPOL 0 CPHA 1
#define Mode_2     0x10  // CPOL 1 CPHA 0
#define Mode_3  		0x18   // CPOL 1 CPHA 1
#define MSTR_BIT   5     // SPI0 as Master 
#define LSBF_BIT   6     // default MSB first,if set LSB first
#define SPIE_BIT   7     //SPI Interrupt Enable Bit

// SPSR bits
#define SPIF_BIT   7    // Data Transfer Completion Flag

//SPINT bit
#define SPIINTF_BIT 0   //SPI Interrupt Flag Bit
#endif

#ifndef __DEFINES_H__
#define __DEFINES_H__

#define SETBIT(WORD,BITPOS)         (WORD|=1<<BITPOS)
#define CLRBIT(WORD,BITPOS)         (WORD&=~(1<<BITPOS))
#define CPLBIT(WORD,BITPOS)         (WORD^=(1<<BITPOS))
#define WRITEBIT(WORD,BITPOS,BIT)   (BIT ? SETBIT(WORD,BITPOS): CLRBIT(WORD,BITPOS))
#define READBIT(WORD,BITPOS)        ((WORD>>BITPOS)&1)

#endif

typedef float f32;
typedef unsigned char u8;
typedef unsigned int u32;
void Init_SPI0(void);
u8 SPI0(u8 data1);
f32 Read_ADC_MCP3204(u8 channelNo);

// int main()
// {
// 	f32 f;
// 	Init_SPI0(); //hw SPI initialisation
// 	//lcd_init();	
// 	uart0_config();
// 	uart0_str("MCP3204--");
//   while(1)
//   {
//     f=Read_ADC_MCP3204(0);
// 		//lcd_cmd(0xc0);
// 		uart0_float(f);
// 		uart0_str("\r\n");
// 		 delay_ms1(500);
// 	}	
// }

void Init_SPI0(void)
{
	
	PINSEL0 |=0X00001500; 
  S0SPCCR = SPI_RATE;             // cfg bit clock rate 
  S0SPCR  =(1<<MSTR_BIT|Mode_3);
	SETBIT(IOPIN0,CS);
	SETBIT(IODIR0,CS);
}

u8 SPI0(u8 data1)
{
   u8 stat = S0SPSR;    //clear SPIF 
   S0SPDR = data1;   // load spi tx reg
   while(READBIT(S0SPSR,SPIF_BIT)==0); // wait for transmission to complete
   return S0SPDR;    // read data from SPI data reg, place into buffer 
}
	



f32 Read_ADC_MCP3204(u8 channelNo)
{
  u8 hByte,lByte;
  u32 adcVal=0;
   
  //select/activate chip 
  CLRBIT(IOPIN0,CS);
	//delay_ms(100);
	
  SPI0(0x06);
  hByte = SPI0(channelNo<<6);
  lByte = SPI0(0x00);
	
	//de-select/de-activate chp
	SETBIT(IOPIN0,CS);
	//delay_ms(100);
  adcVal=((hByte&0x0f)<<8)|lByte;
  return (((adcVal*3.3)/4096)*100);
}
