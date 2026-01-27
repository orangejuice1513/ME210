#define USE_TIMER_1   true 
#define USE_TIMER_2   false 

// #define TIMER_FREQ = 12500 

// TIMER1.init(); 

// void TimerHandler(){
//   // turn the LED on 


// }

// void setup() {
//   Serial.begin(9600);
//   pinMode(2, OUTPUT);

//   if(Timer1.attachInterrupt(TIMER_FREQ, TimerHandler))
//     Serial.println("Starting ITIMER OK, millis() = ");
//   else
//     Serial.println("Can't set ITIMER.");
// }

// void loop() {
//   // // take measurement from analog pin and print (1.3) 
//   // float sensor_value = analogRead(A5);
//   // // map from 0 to 1023 to 50Hz-12.5kHz
//   // float frequency; 
//   // frequency = map(sensor_value, 0.0, 1023.0, 50.0, 12500.0);
//   // long duty = 0.5 / frequency; 
//   // digitalWrite(2, HIGH);
//   // delayMicroseconds(duty);
//   // digitalWrite(2, LOW);
//   // delayMicroseconds(duty);
// }
#include "TimerInterrupt.h"
#include "ISR_Timer.h"

//////////////////////1.4//////////////////////////////
// #include "TimerInterrupt.h"
// #include "ISR_Timer.h"
// #define OUTPUT_PIN 2
// volatile bool toggleState = LOW;
// long currentFreq = 12500;
// int lastPot = -1;

// void TimerHandler()
// {
//   toggleState = !toggleState;
//   digitalWrite(OUTPUT_PIN, toggleState);
// }

// void setup()
// {
//   pinMode(OUTPUT_PIN, OUTPUT);

//   ITimer1.init();
//   ITimer1.setFrequency(currentFreq, TimerHandler);
// }

// void loop(){
//     int potValue = analogRead(A0);
//     lastPot = potValue;
//     long newFreq = map(potValue, 0, 1023, 100, 25000); // ×2 for toggle
//     if (newFreq != currentFreq)
//     {
//         currentFreq = newFreq;
//         ITimer1.setFrequency(currentFreq, TimerHandler);
//     }
// }



//////////////////1.5-1.6//////////////////////////
#include "TimerInterrupt.h"
#include "ISR_Timer.h"
#define OUTPUT_PIN 2
volatile bool toggleState = LOW;
void TimerHandler(){
  toggleState = !toggleState;
  digitalWrite(OUTPUT_PIN, toggleState);
}
void setup(){
  pinMode(OUTPUT_PIN, OUTPUT);
  ITimer1.init();
  ITimer1.setFrequency(2500, TimerHandler);
}
void loop(){
}

