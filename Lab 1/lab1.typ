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

volatile bool toggleState = false; // "volatile" because it's shared with ISR

void setup() {
    pinMode(LED_PIN, OUTPUT);
    ITimer1.init();
    
    // Start with a default frequency
    ITimer1.attachInterrupt(1250, TimerHandler);
}

void loop() {
    // 1. Read the potentiometer
    int potValue = analogRead(A0);

    // 2. Map the 0-1023 pot value to your target frequency range (50Hz - 12500Hz)
    // Note: map returns integers, so ensure your variables handle the math correctly
    long newFreq = map(potValue, 0, 1023, 50, 12500);

    // 3. Update the timer frequency
    // The library function setFrequency allows you to update the rate
    // dynamically without stopping/restarting the timer manually.
    ITimer1.setFrequency(newFreq, TimerHandler);
}

// ---------------------------------------------------------
// Interrupt Service Routine (ISR)
// This only runs when the timer triggers!
// ---------------------------------------------------------
void TimerHandler() {
    // Just toggle the LED state here
    toggleState = !toggleState;
    digitalWrite(LED_PIN, toggleState);
}



```
== 1.6 

= Part 2: The Phototransistor

= Part 3: Op-Amps 
== 3.1 

== 3.3 

== 3.4 Reversing Phototransistor Polarity 

== 3.5 Measured vs. Calculated Gain

== 3.6 Oscilloscope Settings  


= Part 4: Transresistive Amplifiers



= Part 5: Comparators 

= Part 6: Capturing the Output 

