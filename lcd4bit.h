#define data 0xf0<<16
#define rs 1<<17
#define en 1<<19
#define rw 1<<18
void lcd_init(void);
void lcd_float(float );
void lcd_integer(int );
void delay_ms1(int );
typedef void fundec(unsigned char);
void lcd_str(char *);
//void str(char *p);
fundec lcd_cmd,lcd_data;


// int main()

// {  lcd_init();
//   while(1){
//   lcd_cmd(0x80);
// lcd_data('a');
// lcd_str("hello");
// lcd_str("Sid");
// lcd_cmd(0xc0);
// lcd_str("I love you");
// 	 }

// }
void lcd_init(void)
{
IODIR1|=data|rs|en|rw;
lcd_cmd(0x01);
lcd_cmd(0x02);
lcd_cmd(0x0c);
lcd_cmd(0x28);
lcd_cmd(0x80);

}
void lcd_cmd(unsigned char cmd)
{
IOCLR1=data|rw;
IOSET1=(cmd&0xf0)<<16;
IOCLR1=rs;
IOSET1=en;
delay_ms1(2);
IOCLR1=en;
IOCLR1=data;
IOSET1=((cmd&0x0f))<<20;
IOCLR1=rs;
IOSET1=en;
delay_ms1(2);
IOCLR1=en;


}
void lcd_data(unsigned char d)
{
IOCLR1=data|rw;
IOSET1=(d&0xf0)<<16;
IOSET1=rs;
IOSET1=en;
delay_ms1(2);
IOCLR1=en;
IOCLR1=data;
IOSET1=((d&0x0f))<<20;
IOSET1=rs;
IOSET1=en;
delay_ms1(2);
IOCLR1=en;
}
void delay_ms1(int i)
{
T0PR=15000-1;
T0TCR=0x01;
while(T0TC<i);
T0TCR=0x03;
T0TCR=0x00;
}
void lcd_str(char *p)
{
while(*p)
lcd_data(*p++);

}
void lcd_integer(int n)
{
signed char i=0;
unsigned char a[5];
if(n==0)
lcd_data('0');
if(n<0)
{
lcd_data('-');
n=-n;
}
	         while(n){
	         a[i++]=n%10;
	         n=n/10;
	         
	         
	         }
	         for(--i;i>=0;i--)
	         lcd_data(a[i]+48);


}
void lcd_float(float num)
{

int temp;
temp=num;
lcd_integer(temp);
lcd_data('.');
temp=(num-temp)*1000;
lcd_integer(temp);

}
