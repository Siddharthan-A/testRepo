void uart0_tx(unsigned char );
void uart0_config(void);
unsigned char uart0_rx(void);
void uart0_str(char *);
void uart0_integer(int );
void uart0_float(float );


void uart0_config(void)
{
PINSEL0|=0X00000005;
U0LCR=0x00000083;
U0DLL=0x61;
U0DLM=0x00;
U0LCR=0x00000003;
}
void uart0_tx(unsigned char d)
{
while((U0LSR&(1<<5))==0);
	U0THR=d;

}
unsigned char uart0_rx(void)
{
	while((U0LSR&(1<<0))==0);
	return U0RBR;


}
void uart0_str(char *s)
{
while(*s)
	uart0_tx(*s++);


}
void uart0_integer(int i)
{
	unsigned char a[5];
	int n=0;
if(i==0)
	uart0_tx('0');
if(i<0)
{
	uart0_tx('-');
	i=-i;

}

while(i){
a[n++]=i%10;
i=i/10;
}
for(--n;n>=0;n--)
uart0_tx(a[n]+48);

}
void uart0_float(float num)
{ int temp;
	temp=num;
	uart0_integer(temp);
	uart0_tx('.');
	temp=(num-temp)*1000;
	uart0_integer(temp);


}
