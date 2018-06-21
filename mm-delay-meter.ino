#include "src/measure_led.h"
//#include "src/input_capture.h"
#include "src/signal_generator_timer.h"
#include "src/timer1.h"
//#include "src/Timer3/Timer3.h"
#include "src/signal_generator_led.h"
#include "src/signal_generator_speaker.h"
#include "src/sd_card_datalogger.h"
#include "src/config.h"
#include <Process.h>

#define MAX_NUM_MEASUREMENTS  5
int num_measurements;

void setup() {
  
  Serial.begin(9600);
  
  while(!Serial);
  Serial.println("Hello Yún!");

//  // Bridge startup
  Bridge.begin();
  Serial.println("Bridge setup complete");
  measureLEDSetup();
  //inputCaptureSetup();
  SGTimerSetup();
  SGLEDSetup();
  SGSpeakerSetup();
  
  SDCardSetup();
  samplingSetup();

  num_measurements = 0;

  
  resumeTimer3();
}

void loop() {
//  if (SGTimerCheckFlag()){
//    SGLEDToggle();
//    SGSpeakerPlaySound();
//  }
  if (timer1CheckResetFlag()){
    // Turn on led and start timer
    SGLEDOn();
    //timer1ClearResetFlag();
  }
  measureLEDRisingEdgeDetection();

//  if (samplingCheckFlag()){
//    measureLEDRisingEdgeDetection();
//  }
  if (measureLEDCheckFlag()){
  //if (inputCaptureCheckFlag()){
    digitalWrite(lightSensorInterruptPin, LOW);
    //measureLEDPrintToSerial();
    /* Save values in SD card */
    SDCardLogger("measurements.txt", num_measurements);
    num_measurements++;
  }
  if (num_measurements >= MAX_NUM_MEASUREMENTS){
    /* Print saved measurements */
    pauseTimer3();
    SDCardPrintContent();
    digitalWrite(ledPin, LOW);
    while(1){};
  
  }
 
}
