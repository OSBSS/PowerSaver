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

void PowerSaver::turnOffADC()
{
	ADCSRA = ~(1<<ADEN); // This is the ADC enable bit. Writing it to 0 will turn off ADC
}
		  
  //****************************************************************
	
void PowerSaver::turnOnADC()
{
	ADCSRA = (1<<ADEN); // This is the ADC enable bit. Writing it to 1 will turn on ADC
}
	
	//****************************************************************
  
void PowerSaver::goodNight()
{
	d1 = DDRC;	// save direction of analog pins
	p1 = PORTC; // save pinMode of analog pins
	DDRC = 0;		// Setting all analog pins to INPUT 
	PORTC = 0;	// Setting all analog pins to LOW (disable internal pull-ups)
	
  asm("sleep");  // this will put processor in power-down mode
}
	
	//****************************************************************

void PowerSaver::goodMorning()
{
	DDRC = d1;	// restore direction of analog pins
	PORTC = p1;	// restore pinMode of analog pins
}
	
	//****************************************************************

void PowerSaver::turnOffBOD()
{
  // turn off brown-out enable in software (temporary)
  MCUCR |= (1<<BODS) | (1<<BODSE);  // turn on brown-out enable select
  MCUCR |= (1<<BODS);        // this must be done within 4 clock cycles of above
  MCUCR &= ~(1<<BODSE); 	// the processor must sleep within 3 clock cycles after this or BOD disable is cancelled
}

  //****************************************************************
  
  