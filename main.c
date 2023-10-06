#include<LPC21XX.h>
#include"lcd4bit.h"
#include"delay.h"
#include"uart.h"
#include"rtc.h"
#include"spi.h"
#include<string.h>
int main()
{
		unsigned char c;
		f32 f;
		int n;
		lcd_init();
	
//	lcd_data('a');
		delay_ms(1);	
		i2c_init();
		Init_SPI0();
		uart0_config();
//		eeprom_write(0x68,0x02,0x00);	
// 		eeprom_write(0x68,0x01,0x0);	
// 	 	eeprom_write(0x68,0x00,0x0);
// 	 	delay_ms(100);

 	 
		while(1){
					
		

			lcd_cmd(0x80);
			lcd_str("Time:") ;
		c=eeprom_read(0x68,0x02);
		delay_ms(100);
		n=(c&0x3f);
		bcd_ascii(n);
		uart0_tx(':');
			lcd_data((n/16)+48);
	lcd_data((n%16)+48);
		lcd_data(':');
			

		
		c=eeprom_read(0x68,0x01);
		delay_ms(100) ;
		n=(c&0x7f);
		bcd_ascii(n);
				uart0_tx(':');
			lcd_data((n/16)+48);
	lcd_data((n%16)+48);
		lcd_data(':');
		
		c=eeprom_read(0x68,0x00);
		delay_ms(100);
		n=(c&0x7f);
		bcd_ascii(n);
		
		uart0_str("\r\n");
		lcd_data((n/16)+48);
	lcd_data((n%16)+48);
		
	
	
		f=Read_ADC_MCP3204(0);
		uart0_str("Temp:");
		uart0_float(f);
		uart0_str("\r\n");
		 delay_ms1(500);
		 lcd_cmd(0xc0);
		 lcd_str("Temp:");
		 lcd_float(f);
}
}
