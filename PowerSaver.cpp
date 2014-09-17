#include "Arduino.h"
#include "PowerSaver.h"

  //****************************************************************

PowerSaver::PowerSaver()
{

}

  //****************************************************************
  
void PowerSaver::sleepInterruptSetup()
{
	SMCR = (1<<SE) | (1<<SM1);  // sleep pre-setup stuff
  cli();
  PORTB |= (1<<PORTB0); //Activate pullup on PCINT
  PCICR |= (1<<PCIE0);
  PCMSK0 |= (1<<PCINT0);
  sei();
}

  //****************************************************************
	
void PowerSaver::turnOffSPI()
{
  PORTB |= ((1<<DDB5) | (1<<DDB4) | (1<<DDB3) | (1<<DDB2));
  DDRB &= ~((1<<DDB5) | (1<<DDB4) | (1<<DDB3) | (1<<DDB2));  // Clear bits corresponding to data direction for SCK, MISO, MOSI, SS
}
	
  //****************************************************************
	  	
void PowerSaver::turnOnSPI()
{
  DDRB |= (1<<DDB5) | (1<<DDB3) | (1<<DDB2);
  PORTB &= ~((1<<DDB5) | (1<<DDB3));
}
		  
  //****************************************************************

void PowerSaver::turnOffADC()  //Think about and add again later
{
/*
	DDRC &= 0;
	PORTC |= 1;
  /*														//Unsure about best way to configure ADC pin before sleep/ after waking up
	for(byte i=0;i<=A7;i++)
	{
		pinMode(i, INPUT);
		digitalWrite(i, HIGH);
	}
	*/
  pinMode (A0, INPUT);
  digitalWrite (A0, LOW);
  pinMode (A1, INPUT);
  digitalWrite (A1, LOW);
  pinMode (A2, INPUT);
  digitalWrite (A2, LOW);
  pinMode (A3, INPUT);
  digitalWrite (A3, LOW);
  pinMode (A4, INPUT);
  digitalWrite (A4, LOW);
  pinMode (A5, INPUT);
  digitalWrite (A5, LOW);
  pinMode (A6, INPUT);
  digitalWrite (A6, LOW);
  pinMode (A7, INPUT);
  digitalWrite (A7, LOW);
  
  ADCSRA = 0;
}
		  
  //****************************************************************
	
void PowerSaver::turnOnADC()
{
	ADCSRA = 1;
}
	
	//****************************************************************



void PowerSaver::turnOffBOD()
{
  // turn off brown-out enable in software
  MCUCR |= (1<<BODS) | (1<<BODSE);  // turn on brown-out enable select
  MCUCR |= (1<<BODS);        // this must be done within 4 clock cycles of above
  MCUCR &= ~(1<<BODSE);
}

  //****************************************************************
  
  