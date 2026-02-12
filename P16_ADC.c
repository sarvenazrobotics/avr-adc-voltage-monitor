#include <io.h>
#include <stdio.h>
#include <alcd.h>
#include <delay.h>

int read_adc(void);
void sel_chan(char ch);
char buff[16];
void main(void)
{

    lcd_init(16);  
    ADCSRA=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
    DIDR0=0x3F;
    sel_chan(0);
while (1)
    { 
       
       sprintf(buff,"%u   ",read_adc());
       lcd_gotoxy(0,0);
       lcd_puts(buff);
       delay_ms(100);
    }  
    
}

void sel_chan(char ch)
{
 ADMUX=ch |(1<<REFS1)|(1<<REFS0);//internal 1.1v
 delay_ms(100);
}

int read_adc(void)
{
    
    ADCSRA|=(1<<ADSC);//SATRT CONVERT
    while (!(ADCSRA & (1<<ADIF)));//wait until conversion is finished 
    ADCSRA|=(1<<ADIF);//CLEAR ADIF
    return ADCW;

}
