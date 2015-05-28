#include <stdlib.h>
#include <avr/interrupt.h>
#include <LCD.h>
#include <ButtonPress.h>

void BrightnessScreen(void);
void TimeScreen(void);
void AboutScreen(void);
void ContrastScreen(void);
void TXScreen(void);
void RXScreen(void);
void menu(int num);

int Avail=1;
int selected=1;
int Backlight=1;

int main(void){
	
	DDRC &= ~(1<< PINC0); //Set som 0
	PORTC |= 1 << PINC0;	// set som 1
	DDRC &= ~(1<< PINC1); //Set som 0
	PORTC |= 1 << PINC1;	// set som 1
	DDRC |= 1 << PINC7;
	PORTC ^= 1 << PINC7;
	
	InitializeLCD();
	LoadingScreen();
	menu(1);

	while (1){
		if (ButtonPressed(0,PINC,1,100)){
			if (Avail){
				Avail=0;
				if(selected==1){
					ContrastScreen();
				}else if(selected==2){
					TimeScreen();
				}else if(selected==3){
					AboutScreen();
				}else if(selected==4){
					BacklightScreen();
				}else if(selected==5){
					TXScreen();
				}else if(selected==6){
					RXScreen();
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
		if (Avail==1 && ButtonPressed(1,PINC,0,100)){
			if(selected==1){
				menu(2);
			}else if(selected==2){
				menu(3);
			}else if(selected==3){
				menu(4);
			}else if(selected==4){
				menu(5);
			}else if(selected==5){
				menu(6);
			}else if(selected==6){
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

void ContrastScreen(void){
	Send_Kommando(0b00001100);
	Message("Contrast");
	Send_Kort_Streng("- Exit");
	Send_Kommando(0x80+40);
	Send_Kort_Streng("Contrast:");
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
void BacklightScreen(void){
	Message("Backlight");
	Send_Kort_Streng("- Save");
	Send_Kommando(0x80+40);
	if (Backlight){
		Send_Kort_Streng("Backlight:   ON ");
	}else{
		Send_Kort_Streng("Backlight:   OFF");
	}
	while(1){
		if (ButtonPressed(1,PINC,0,100)){
			Send_Kommando(0x80+40);
			PORTC ^= 1 << PINC7;
			if (Backlight){
				Send_Kort_Streng("Backlight:   OFF ");
				Backlight=0;
			}else{
				Send_Kort_Streng("Backlight:   ON  ");
				Backlight=1;
			}
			//break;
		}
		if (ButtonPressed(0,PINC,1,100)){
			Clear_Screen();
			Send_Kort_Streng("Saved");
			Send_Kommando(0x80+40);
			Send_Kort_Streng("       OK");
			break;
			
		}
	}
}
void TXScreen(void){
	int i=0;
	char antall[4];
	Message("");
	Send_Kort_Streng("- Exit");
	int UBBRValue = 25;
	unsigned char receiveData;
	UBRRH = (unsigned char) (UBBRValue >> 8);
	UBRRL = (unsigned char) UBBRValue; 
	UCSRB = (1 << RXEN) | (1 << TXEN);
	UCSRC = (1 << USBS) | (3 << UCSZ0); 
	Send_Kommando(0x80+40);
	Send_Kort_Streng("Sent:  ");
	while(1){
		if (ButtonPressed(1,PINC,0,100)){
			Send_Kommando(0x80+53);
			i++;
			itoa(i, antall, 10);
			Send_Kort_Streng(antall);
			
		}
		if (ButtonPressed(0,PINC,1,100)){
				Clear_Screen();
				Send_Kort_Streng("Thank you!");
				Send_Kommando(0x80+40);
				Send_Kort_Streng("       OK");
				break;
				
		}
		
	}
	
}
void RXScreen(void){
	int i=0;
	Message("");
	Send_Kort_Streng("- Exit");
	int UBBRValue = 25;
	unsigned char receiveData;
	UBRRH = (unsigned char) (UBBRValue >> 8);
	UBRRL = (unsigned char) UBBRValue; 
	UCSRB = (1 << RXEN) | (1 << TXEN);
	UCSRC = (1 << USBS) | (3 << UCSZ0); 

		while (! (UCSRA & (1 << RXC)) ){

			receiveData = UDR;
			if ((receiveData == 0b11111111)){
				//Clear_Screen();
				Send_Kommando(0x80+52);
				char antall[4];
				itoa(i, antall, 10);
				Send_Kort_Streng(antall);
				i++;
			}
			if (ButtonPressed(0,PINC,1,100)){
				Clear_Screen();
				Send_Kort_Streng("Thank you!");
				Send_Kommando(0x80+40);
				Send_Kort_Streng("       OK");
				break;
			
			}
		}
		
	
	
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
		Send_Kort_Streng("  Contrast");
	}else if (num==2){
		Send_Kort_Streng("     Time");
	}else if (num==3){
		Send_Kort_Streng("     About");
	}else if (num==4){
		Send_Kort_Streng("  Backlight");
	}else if (num==5){
		Send_Kort_Streng(" UART Transmit");
	}else if (num==6){
		Send_Kort_Streng(" UART Recieve");
	}
	
	Send_Kommando(0x80+55);
	Send_Bokstav(0b01111110);
	
}
