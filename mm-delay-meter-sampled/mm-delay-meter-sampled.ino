#include "src/config.h"
#include "src/timer1.h"
#include "src/timer3.h"
#include "src/signal_generator.h"
#include "src/measurement_samples.h"
#include "src/sd_card_datalogger.h"
#include <Process.h>

#define MAX_NUM_MEASUREMENTS  20
int num_measurements;

void setup() {
  
  Serial.begin(9600);
  while(!Serial);
  Serial.println("Hello Yún!");

  // Bridge startup
  Bridge.begin();
  Serial.println("Bridge setup complete");

  SDCardSetup();
  signalGeneratorSetup();
  measurementSamplesSetup();
  
  resumeTimer1();
  resumeTimer3();
  num_measurements = 0;
}

void loop() {
  if (timer1CheckOvfFlag()){
    // Turn on led and start stopwatch
    signalGeneratorLEDOn();
    // Turn on speaker
    signalGeneratorSpeakerOn();
  }
  if (timer1CheckCompFlag()){
    // Turn off LED
    signalGeneratorLEDOff();
    // Turn off speaker
    signalGeneratorSpeakerOff();
  }
  if (timer3CheckSamplingFlag()){
    // Measure light
    // measurementSamplesRisingEdgeDetection();
    // Measure sound
    measurementSamplesRisingEdgeDetectionSound();
  }
  if (measurementSamplesCheckMeasuredFlag()){
    SDCardLogger("measurements.txt", num_measurements);
    num_measurements++;
  }
}
