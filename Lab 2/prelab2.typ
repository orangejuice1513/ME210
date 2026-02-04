
#set text(size: 12pt)
#set align(center)
= ME210 Introduction to Mechatronics \ Prelab 2\
Winter 2026 \
Julia Jiang 

#set align(left)
= 0.1 Arduino Pins and Ports 
- 5V: to potentiometer, L298
- GND: to potentiometer, L298
- PIN A0: to potentiometer wiper  
- PIN 9: PWM out 
- PINS 4, 5, 6, 7: to L298 

= 0.2 Pin Initialization 
- no pin initializations for A0 or PWM PIN 9 
- initialization for pins connected to H-bridge: 
```cpp
#define OUTPUT_PIN_1 = 4;
#define OUTPUT_PIN_2 = 5;
#define OUTPUT_PIN_3 = 6;
#define OUTPUT_PIN_4 = 7;

void setup(){
  pinMode(OUTPUT_PIN_1, OUTPUT);
  pinMode(OUTPUT_PIN_2, OUTPUT);
  pinMode(OUTPUT_PIN_3, OUTPUT);
  pinMode(OUTPUT_PIN_4, OUTPUT);
}
void loop(){
  # write later 
}
```