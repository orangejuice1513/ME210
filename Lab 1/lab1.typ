#set text(size: 12pt)
#set align(center)
= ME210 Introduction to Mechatronics \ Lab 1 \
Winter 2026 \
Julia Jiang 

#set align(left)
= Part 1: The Arduino as a Controllable Signal Source 

== 1.2 (don't need to submit)
```cpp
pinMode(5,OUTPUT);
digitalWrite(5,LOW); // writes to output 

void setup(){
  Serial.begin(9600);
}

void loop(){
  int voltage = analogRead(A0); //replace with whatever pin 
  Serial.println(voltage);
}
```
== 1.3 
We don't want a unity gain buffer for this signal because it has low output impedance and a current gain, and we don't want large currents going into the Arduino pins. 
Limitation:   

== 1.5 
```cpp
#define USE_TIMER_1   true 
#define USE_TIMER_2   false 

#include "TimerInterrupt.h"
#include "ISR_Timer.h"
volatile bool toggleState = LOW;
long currentFreq = 12500;
int lastPot = -1;

void TimerHandler(){
  //after timer expires 
  toggleState = !toggleState;
  digitalWrite(2, toggleState);
}
void setup(){
  pinMode(2, OUTPUT);
  ITimer1.init();
  ITimer1.setFrequency(currentFreq, TimerHandler);
}

void loop(){
    int potValue = analogRead(A0);
    lastPot = potValue;
    long newFreq = map(potValue, 0, 1023, 100, 25000); // ×2 for toggle
    if (newFreq != currentFreq){
        currentFreq = newFreq;
        ITimer1.setFrequency(currentFreq, TimerHandler);
    }
}

```
== 1.6 
```cpp
#define USE_TIMER_1   true 
#define USE_TIMER_2   false 

#include "TimerInterrupt.h"
#include "ISR_Timer.h"
volatile bool toggleState = LOW;
void TimerHandler(){
  toggleState = !toggleState;
  digitalWrite(2, toggleState);
}
void setup(){
  pinMode(2, OUTPUT);
  ITimer1.init();
  ITimer1.setFrequency(2500, TimerHandler); //1.25kHz * 2 
}
void loop(){
}
```
= Part 2: The Phototransistor

== 2.2 Sourcing Configuration 

== 2.3 Sourcing Configuration Waveform 

== 2.5 Sinking Configuration 

== 2.6 Sinking Configuration Waveform 

== 2.7 Difference between Sourcing and Sinking Waveforms
The waveforms have different voltages because the resistors are in different places. In the sourcing configuration, the waveform measures voltage across the resistor directly but in the sinking configuration the voltage is measured at the node below the load resistor. Either way, the voltages across the resistors are about the same and the currents through the phototransistor are about the same, which makes sense because the current depends on the distance of the IR LED from the phototransistor. 
== 2.9 10k /ohm 

The 10k /ohm resistor forces V_o to hit the supply rails since the current through the phototransistor (around 0.7mA) wants to stay constant due to the constant IR LED emmission and the resistance is large. Thus, the the current is limited to an amount where V_o hits the supply rail. 

== 2.11 100 /ohm

The waveform is the same as with the 1k /ohm load resistor since V_o doesn't hit the supply rails and the same amount of current can pass through the phototransistor. 

= Part 3: Op-Amps 
== 3.1 

== 3.3 

== 3.4 Reversing Phototransistor Polarity 

== 3.5 Measured vs. Calculated Gain

== 3.6 Oscilloscope Settings  


= Part 4: Transresistive Amplifiers



= Part 5: Comparators 

= Part 6: Capturing the Output 

