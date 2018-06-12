/* Detects recieved light at sensor using hardware interrupt.
 * Measures delay of recieved light.
 * This timer should be reset in the function generating pulses */

#include "Arduino.h"
#include "measure_led.h"

volatile int led_flag;
int samples[NUM_SAMPLES];

void measureLEDSetup(){
    // Timer 3 for measuring delay

    led_flag = 0;
    pinMode(lightSensorInterruptPin, INPUT); // or INPUT_PULLUP?
    attachInterrupt(digitalPinToInterrupt(lightSensorInterruptPin), measureLEDDelay, RISING);
}

/* Interrupt service routine for external interrupt at pin 3, triggers when light is recieved at sensor */
void measureLEDDelay(){
    led_flag = 1;
    // Stop timer
    // Save delay measurement

    // readTimer1() returns a maximum value of 65535
    // That means the maximum possible delta one can measure with this
    // function (when in slow counting mode) is 1048ms on 16 MHz boards,
    // and 2097ms on 8 MHz boards
    //unsigned short delta = readTimer1() - lastTickCount;

    // If you estimate deltaMicros could be > 65 ms, or 65535 us,
    // delta should be cast to unsigned long, and deltaMicros should be
    // created as an unsigned long variable
    //unsigned long deltaMicros = microsFromSlowCounting((unsigned long)delta);

}
// debug only
void printSensorValue(){
    // Read analog value (for "debug")
    int raw_sample = analogRead(lightSensorPin);
    Serial.print("Light sensor: ");
    Serial.println(raw_sample);
}


// void lightSetup()
// {
//   initializeSamples();
// }

// /* Maximum smoothing filter */
// void initializeSamples()
// {
//   for (int i = 0; i < NUM_SAMPLES; i++){
//     samples[i] = 0;
//   }
// }

// void readLightInput()
// {
//   static int current_index;
  
//   int raw_sample = analogRead(lightSensorPin);
//   Serial.print("Light sensor: ");
//   Serial.println(raw_sample);

//   // Add sample to saved samples
//   samples[current_index] = raw_sample;

//   if (current_index < NUM_SAMPLES - 1){
//     current_index++;
//   }
//   else{
//     current_index = 0;
//   }
// }

// int findMax()
// {
//   // Find the maximum of NUM_SAMPLES previous samples
//   int max_sample = 0;
//   for (int i = 0; i < NUM_SAMPLES; i++){
//     if (samples[i] > max_sample){
//       max_sample = samples[i];
//     }
//   }
//   return max_sample;
// }


// int maxSmoothingFilter()
// {
//   readLightInput();
//   return findMax();
// }

// // Rising edge detection
// bool risingEdgeDetection()
// {
//   int current_max = maxSmoothingFilter();
//   static int prev_max = current_max;
//   static int prev_prev_max = current_max;

//   bool edge_detected = false;
  
//   // Compare with previous max value
//   if (current_max - prev_max > 20){
//     edge_detected = true;
//   }

//   // Otherwise, compare previous 3 values
//   else if (current_max - prev_prev_max > 20){
//     edge_detected = true;
//   }

//   prev_prev_max = prev_max;
//   prev_max = current_max;
//   return edge_detected;
// }



