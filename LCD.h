/*
 * LCD.h
 *
 * Created: 06.05.2015 13:13:30
 *  Author: Ringstad, modified by Hedberg
 */ 


#ifndef LCD
#define LCD

#include <avr/io.h>
#include <util/delay.h>

#define Port_LCD PORTB
#define DataDir_LCD DDRB
#define Port_LCDControl PORTD
#define DataDir_LCDControl DDRD
#define Enable_Pin 5
#define RW_Pin 7
#define RS_Pin 2

void Sjekk_Opptatt(void);
void Clear_Screen(void);
void InitializeLCD(void);
void AlleTegn(void);
void LoadingScreen(void);
void Enable_Vent_Disable(void);
void Send_Kommando(unsigned char command);
void Send_Bokstav(unsigned char character);
void Send_Streng(char *StringOfCharacters);
void Send_Kort_Streng(char *StringOfCharacters);
void Send_Alert(char *StringOfCharacters);


void Sjekk_Opptatt()
{
DataDir_LCD = 0;
Port_LCDControl |= 1<<RW_Pin;
Port_LCDControl &= ~1<<RS_Pin;

while (Port_LCD >= 0x80)
{
Enable_Vent_Disable();
}
DataDir_LCD = 0xFF; //0xFF means 0b11111111
}

void Enable_Vent_Disable()
{
Port_LCDControl |= 1<<Enable_Pin;
asm volatile ("nop");
asm volatile ("nop");
Port_LCDControl &= ~1<<Enable_Pin; //0
}

void Send_Kommando(unsigned char command)
{
Sjekk_Opptatt();
Port_LCD = command;
Port_LCDControl &= ~ ((1<<RW_Pin)|(1<<RS_Pin));
Enable_Vent_Disable();
Port_LCD = 0;
}

void Send_Bokstav(unsigned char character)
{
Sjekk_Opptatt();
Port_LCD = character;
Port_LCDControl &= ~ (1<<RW_Pin);
Port_LCDControl |= 1<<RS_Pin;
Enable_Vent_Disable();
Port_LCD = 0;
}

void Send_Streng(char *StringOfCharacters){
	int i=0, j=0, space=0,plass=1, start=1,line=1;
	
	while(*(&*StringOfCharacters+i)>0){
		
		for(j=0;j<18 && start==1;j++){
			if(*(&*StringOfCharacters+i+j-1)==0x20){
				space=j;
				
			}
		}
		
		start=0;
		Send_Bokstav(*(&*StringOfCharacters+i));
		_delay_ms(10);
		if (plass==space | (plass>15 && space==0)){
			if(line==1){
				Send_Kommando(0x80+40);line=2;
			}else{
				_delay_ms(15);
				Send_Kommando(0x01);line=1;
			}
			Send_Kommando(0x80+40);
			//Send_Kommando(0x01);
			_delay_ms(15);
			start=1;
			plass=0;
			space=0;
			
		}
		i++;
		plass++;
	}
}
void Send_Kort_Streng(char *StringOfCharacters){
	int i=0;
	while(*StringOfCharacters > 0){
		Send_Bokstav(*StringOfCharacters++);

	}
}
void AlleTegn(){
	char *j="a";
	int i;
	for(i=0;i<110;i++){
		j[i]=0x41+i;
	}
	Send_Streng(*j);
}
void LoadingScreen(){
	int i;
	_delay_ms(20);
	Send_Kort_Streng("Loading OS");
	_delay_ms(10);
	Send_Kommando(0x80+40);
	_delay_ms(10);
	for(i=0;i<16;i++){
		Send_Bokstav(0b11111111);
		_delay_ms(30);
	}
	_delay_ms(15);
	Send_Kommando(0x01);
	_delay_ms(15);
}
void Alert(char *StringOfCharacters){
	int i;
	_delay_ms(15);
	Send_Kommando(0x01);
	_delay_ms(15);
	for(i=0;i<1;i++){
		Send_Kort_Streng("ÿÿÿÿÿALERT!ÿÿÿÿÿ");
		_delay_ms(30);
		Send_Kommando(0x01);
		_delay_ms(30);
	}
	Send_Kort_Streng("ÿÿÿÿÿALERT!ÿÿÿÿÿ");
	Send_Kommando(0x80+40);
	Send_Kort_Streng(StringOfCharacters);
	Send_Kommando(0x80+70);
	_delay_ms(170);
	Send_Kommando(0x01);
	_delay_ms(15);
	
}
void InitializeLCD(){
	DataDir_LCDControl |= 1<<Enable_Pin | 1<<RW_Pin | 1<<RS_Pin;
	_delay_ms(15);
	Send_Kommando(0x01); //Clear Screen 0x01 = 00000001
	_delay_ms(2);
	Send_Kommando(0x38);
	_delay_us(50);
	Send_Kommando(0b00001100);
	_delay_ms(50);
}
void Clear_Screen(){
	_delay_ms(15);
	Send_Kommando(0x01);
	_delay_ms(15);
}

#endif
