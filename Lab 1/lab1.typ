#set text(size: 12pt)
#set align(center)
= ME210 Introduction to Mechatronics \ Lab 1 \
Winter 2026 \
Julia Jiang 

#set align(left)
= Part 1: The Arduino as a Controllable Signal Source 
== 1.3 
We don't want a unity gain buffer for this signal because it has low output impedance and a current gain, and we don't want large currents going into the Arduino pins. 
Limitation:   

== 1.5 
resistor size = 270 $Omega$ \
the current the arduino pin takes in is 20mA
$R_L >= (5V) / (20 m A) = 250 Omega$
```cpp
#include "TimerInterrupt.h"
#include "ISR_Timer.h"
#define USE_TIMER_1   true 
#define USE_TIMER_2   false 
#define OUTPUT_PIN 2 
volatile bool toggleState = LOW;
long currentFreq = 12500;

void TimerHandler(){
  //after timer expires, change led state
  toggleState = !toggleState;
  digitalWrite(OUTPUT_PIN, toggleState);
}
void setup(){
  pinMode(OUTPUT_PIN, OUTPUT);
  ITimer1.init();
}
void loop(){
    int potValue = analogRead(A0);
    long newFreq = map(potValue, 0, 1023, 100, 25000); // ×2 for toggle
    if (newFreq != currentFreq){
        currentFreq = newFreq;
        ITimer1.setFrequency(currentFreq, TimerHandler);
    }
}
```

== 1.6 
#image("q1-6.png")
```cpp
#include "TimerInterrupt.h"
#include "ISR_Timer.h"
#define USE_TIMER_1   true 
#define USE_TIMER_2   false 
#define OUTPUT_PIN 2 
volatile bool toggleState = LOW;
void TimerHandler(){
  toggleState = !toggleState;
  digitalWrite(OUTPUT_PIN, toggleState);
}
void setup(){
  pinMode(OUTPUT_PIN, OUTPUT);
  ITimer1.init();
  ITimer1.setFrequency(2500, TimerHandler); //1.25kHz * 2 
}
void loop(){
}
```


= Part 2: The Phototransistor
== 2.2 Sourcing Configuration 
#image("q2-2.png")

== 2.3 Sourcing Configuration Waveform 
#image("q2-3.png")

== 2.5 Sinking Configuration 
#image("q2-5.png")

== 2.6 Sinking Configuration Waveform 
#image("q2-6.png")

== 2.7 Difference between Sourcing and Sinking Waveforms
The waveforms have different voltages because the resistors are in different places. In the sourcing configuration, the waveform measures voltage across the resistor directly but in the sinking configuration the voltage is measured at the node below the load resistor. Either way, the voltages across the resistors are about the same and the currents through the phototransistor are about the same, which makes sense because the current depends on the distance of the IR LED from the phototransistor. 

== 2.9 10k /ohm 
#image("q2-9.png")
The 10k /ohm resistor forces V_o to hit the supply rails since the current through the phototransistor (around 0.7mA) wants to stay constant due to the constant IR LED emmission and the resistance is large. Thus, the the current is limited to an amount where V_o hits the supply rail. 

== 2.11 100 /ohm
#image("q2-11.png")

The waveform is the same as with the 1k /ohm load resistor since V_o doesn't hit the supply rails and the same amount of current can pass through the phototransistor. 

= Part 3: Op-Amps 
== 3.1 
Inverting op amp gain = 10 \
$G = 1 + R_1 / R_2 = 10 $ \
$R_1 / R_2 = 9 $ \
$R_1 = 2 k Omega$ \
$R_2 = 220 k Omega$ 
#image("q3-1.png")

== 3.3 
#image("q3-3.png")

== 3.4 Reversing Phototransistor Polarity 
The signal is noiser and weaker, which makes sense because the phototransistor sensitivity decreases. 
#image("q3-4.png")

== 3.5 Measured vs. Calculated Gain
Measured gain $ = (5V) / (0.75V) = 6.67 V/V$
This agrees with the calculated gain since the output voltage from the phototransistor is around 0.75V and a gain of 10 means the op amp saturates at the supply rails, making the output 5V. 

== 3.6 Oscilloscope Settings  
#image("q3-3.png")
I used Amplitude on the oscilloscope to measure the value of HI on the op amp. I chose this since peak-to-peak was not measuring to the top of the waveform. 

= Part 4: Transresistive Amplifiers
= 4.1 Transresistive Amplifier 

V_CE being 2.5V is not ideal for the phototransistor because from the datasheet, the typical operating voltage is 5V. 

== 4.2
The output of the amplifier at 1mW/cm#super[2] should be low and the output at 5mW/cm#super[2] should be high. 

== 4.4 Op-Amp Output Waveform 
#image("q4-4.png")
The output HI is only around half the voltage of the output HI in part 3. 
We can make the signal amplitude larger by putting the IR LED closer to the phototransistor. 

= Part 5: Comparators 
== 5.2 Comparator Schematic  

== 5.3
Trip points: 2.4V, 2.6V 

== 5.5 Output of Op Amp and Output of Comparator Graph 
#image("q5-5.png")

= Part 6: Capturing the Output 
== 6.2 
```cpp

```

== 6.4 
```cpp


```




