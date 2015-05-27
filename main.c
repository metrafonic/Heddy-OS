#include <stdlib.h>
#include <avr/interrupt.h>
#include <LCD.h>
#include <ButtonPress.h>

void BrightnessScreen(void);
void TimeScreen(void);
void AboutScreen(void);
void menu(int num);

int Avail=1;
int selected=1;

int main(void){
	
	DDRC &= ~(1<< PINC0); //Set som 0
	PORTC |= 1 << PINC0;	// set som 1
	DDRC &= ~(1<< PINC1); //Set som 0
	PORTC |= 1 << PINC1;	// set som 1
	
	
	InitializeLCD();
	LoadingScreen();
	menu(1);

	while (1){
		if (ButtonPressed(0,PINC,1,100)){
			if (Avail){
				Avail=0;
				if(selected==1){
					BrightnessScreen();
				}else if(selected==2){
					TimeScreen();
				}else if(selected==3){
					AboutScreen();
				}
			}else{
				Avail=1;
				ADCSRA =0b00000000;
				ADMUX  =0b00000000;
				ADMUX =0b00000000;
				ADCSRA =0b00000000;
				ADCSRA =0b00000000;
				menu(1);
			}
		}
		if (ButtonPressed(1,PINC,0,100) && Avail==1){
			if(selected==1){
				menu(2);
			}else if(selected==2){
				menu(3);
			}else if(selected==3){
				menu(1);
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
	Message("Bightness");
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
void TimeScreen(void){
	Alert("In Progress!");
	Send_Kort_Streng("- Exit");
	Send_Kommando(0x80+40);
	Send_Kort_Streng("Time:   in progress");	
}
void AboutScreen(void){
	Message("About");
	Send_Streng("Heddy OS - Created by Mathias Hedberg. metrafonic.com");	
}

void menu(int num){
	//Send_Kommando(0b00001101);
	Clear_Screen();
	Send_Kort_Streng("Menu:");
	Send_Kommando(0x80+40);
	Send_Bokstav(0b01111111);
	selected=num;
	if (num==1){
		Send_Kort_Streng("  Brightness");
	}else if (num==2){
		Send_Kort_Streng("     Time");
	}else if (num==3){
		Send_Kort_Streng("     About");
	}
	
	Send_Kommando(0x80+55);
	Send_Bokstav(0b01111110);
	
}
