#define USE_TIMER_1   true 
#define USE_TIMER_2   false 
// #define USE_TIMER_3   false 
// #define USE_TIMER_4   false 
// #define USE_TIMER_5   false 

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

//   // turn on LED using timer interrupt 
//   float frequency = 12500.0; //12.5kHz 
//   bool setFrequency(frequency, timer_callback callback, unsigned long duration = 0);

// }



// #include "TimerInterrupt.h"
// #include "ISR_Timer.h"

// #define OUTPUT_PIN 8

// void TimerHandler()
// {
//   static bool pinState = false;
//   pinState = !pinState;
//   digitalWrite(OUTPUT_PIN, pinState);
// }

// void setup()
// {
//   pinMode(OUTPUT_PIN, OUTPUT);
//   ITimer1.init();
//   ITimer1.setFrequency(12500, TimerHandler);
// }

// void loop()
// {
//   float sensor_value = analogRead(A5);
//   float frequency; 
//   frequency = map(sensor_value, 0.0, 1023.0, 50.0, 12500.0);
// }




#include "TimerInterrupt.h"
#include "ISR_Timer.h"

// #define OUTPUT_PIN 8

// volatile bool pinState = false;
// float currentFrequency = 12500;  // start value

// void TimerHandler()
// {
//   pinState = !pinState;
//   digitalWrite(OUTPUT_PIN, pinState);
// }

// void setup()
// {
//   pinMode(OUTPUT_PIN, OUTPUT);

//   ITimer1.init();
//   ITimer1.setFrequency(currentFrequency, TimerHandler);
// }

// void loop()
// {
//   int sensor_value = analogRead(A5);

//   float newFrequency = map(sensor_value, 0, 1023, 50, 12500);

//   // Only update timer if frequency actually changed
//   if (abs(newFrequency - currentFrequency) > 1)
//   {
//     currentFrequency = newFrequency;
//     ITimer1.setFrequency(currentFrequency, TimerHandler);
//   }
// }

// volatile bool toggleState = LOW; // "volatile" because it's shared with ISR

// void setup() {
//     // pinMode(LED_PIN, OUTPUT);
//     pinMode(2, OUTPUT); 
//     ITimer1.init();
    
//     // Start with a default frequency
//     ITimer1.attachInterrupt(1250, TimerHandler);
// }

// void loop() {
//     // 1. Read the potentiometer
//     int potValue = analogRead(A0);
//     // 2. Map the 0-1023 pot value to your target frequency range (50Hz - 12500Hz)
//     long newFreq = map(potValue, 0, 1023, 50, 12500);
//     // 3. Update the timer frequency
//     // The library function setFrequency allows you to update the rate
//     // dynamically without stopping/restarting the timer manually.
//     ITimer1.setFrequency(newFreq, TimerHandler);
// }

// This only runs when the timer triggers!
void TimerHandler() {
    //toggle the LED state here
    toggleState = !toggleState;
    digitalWrite(2, toggleState);
}

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
