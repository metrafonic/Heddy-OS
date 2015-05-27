#include <stdlib.h>
#include <avr/interrupt.h>
#include <LCD.h>


int main(void){
	InitializeLCD();
	while(1){
		Clear_Screen();
		Send_Kort_Streng("Menu: ");
		Send_Kommando(0x40+40);
		Send_Kort_Streng("|Brightness|");
		while(1){
			
		}
	}
	
	Alert("ADC Mode");
	Send_Kort_Streng("Brightness: ");
	ADCSRA |= 1<<ADPS2;
	ADMUX  |=1<<ADLAR;
	ADMUX |= 1<<REFS0;
	ADCSRA |=1<<ADIE;
	ADCSRA |= 1<<ADEN;
	
	sei();
	
	ADCSRA |=1<<ADSC;
	
	
	
	while(1){

	}
}
ISR(ADC_vect){
	Send_Kommando(0x80+52);
	char adcResult[4];
	itoa(ADCH, adcResult, 10);
	Send_Kort_Streng(adcResult);
	Send_Kort_Streng("  ");

	ADCSRA |=1<<ADSC;
}

