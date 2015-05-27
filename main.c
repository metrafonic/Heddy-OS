#include <stdlib.h>
#include <avr/interrupt.h>
#include <LCD.h>
#include <ButtonPress.h>

void BrightnessScreen(void);
void menu(void);

int Avail=1;

int main(void){
	DDRC |= 1 << PINC0;
	PORTC ^=1 << PINC0;
	DDRC |= 1 << PINC2;
	DDRC &= ~(1<< PINC1); //Set som 0
	PORTC |= 1 << PINC1;	// set som 1
	
	InitializeLCD();
	menu();

	while (1){
		if (ButtonPressed(0,PINC,1,100)){
			if (Avail){
				Avail=0;
				BrightnessScreen();
			}else{
				Avail=1;
				ADCSRA =0b00000000;
				ADMUX  =0b00000000;
				ADMUX =0b00000000;
				ADCSRA =0b00000000;
				ADCSRA =0b00000000;
				menu();
			}
		}	
		
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

void BrightnessScreen(void){
	Send_Kommando(0b00001100);
	Alert("View Bightness");
	Send_Kort_Streng("- Exit");
	Send_Kommando(0x80+40);
	Send_Kort_Streng("Brightness:");
	ADCSRA |= 1<<ADPS2;
	ADMUX  |=1<<ADLAR;
	ADMUX |= 1<<REFS0;
	ADCSRA |=1<<ADIE;
	ADCSRA |= 1<<ADEN;
	
	sei();
	
		ADCSRA |=1<<ADSC;
	
}

void menu(){
	Send_Kommando(0b00001101);
	Clear_Screen();
	Send_Kort_Streng("-Brightness");
	Send_Kommando(0x80+40);
	Send_Kort_Streng("-Change LED");
	Send_Kommando(0x80);
}
