void delay_ms(int i){
T0PR=15000-1;
T0TCR=0x01;
while(T0TC<i);
T0TCR=0x03;
T0TCR=0x00;
}
void delay_s(int i){
T0PR=15000000-1;
T0TCR=0x01;
while(T0TC<i);
T0TCR=0x03;
T0TCR=0x00;
}
void delay_micros(int i){
T0PR=15-1;
T0TCR=0x01;
while(T0TC<i);
T0TCR=0x03;
T0TCR=0x00;
}
