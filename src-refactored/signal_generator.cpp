/* Generates the speaker and LED signals.
 * Speaker generates a square wave w/ frequency 500 Hz on pin 11 (for now at least),
 * using 8-bit Timer0 on Atmega32u4. */

#include "signal_generator.h"
#include "timer1.h"
#include "measurement_samples.h"
#include "config.h"

//bool light_recieved_at_sensor;

void signalGeneratorSetup()
{
	// LED setup
	timer1ClearFlags();
	startTimer1();
	pauseTimer1();

	pinMode(ledPin, OUTPUT);
	digitalWrite(ledPin, LOW);

	// Speaker setup
	pinMode(speakerPin, OUTPUT);

 	TCNT0 = 0;
	// Toggle OC0A on compare match in CTC mode
	TCCR0A = B01000010;
	// Prescaler = 64
	TCCR0B = B00000011;
	// Compare match at 16MHz/(ps*f*2), ps = 64, f = 500Hz
	OCR0A = 250;
	signalGeneratorSpeakerOff();

}

void signalGeneratorLEDOn()
{
	//light_recieved_at_sensor = 0;
	measurementSamplesClearLightRecievedFlag();
	resetTimer1();		// Redundant? It has already overflowed		
	digitalWrite(ledPin, HIGH);
}

void signalGeneratorLEDOff()
{
	digitalWrite(ledPin, LOW);
}

void signalGeneratorSpeakerOn()
{
	resumeTimer0();
}

void signalGeneratorSpeakerOff()
{
	pauseTimer0();
	resetTimer0Unsafe();
}