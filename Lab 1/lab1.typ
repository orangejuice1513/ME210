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
```
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

= Part 3: Op-Amps 

= Part 4: Transresistive Amplifiers 

= Part 5: Comparators 

= Part 6: Capturing the Output 

