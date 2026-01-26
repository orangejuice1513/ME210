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

== 1.6 

= Part 2: The Phototransistor

= Part 3: Op-Amps 

= Part 4: Transresistive Amplifiers 

= Part 5: Comparators 

= Part 6: Capturing the Output 

