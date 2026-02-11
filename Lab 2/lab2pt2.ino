// ME 210 Lab 2 Part 2:
// source code for controlling the speed and direction of rottion of a 
// dc brushless motor 

#define USE_TIMER_1   true  //on time 
#define USE_TIMER_2   true //off time 

#include "TimerInterrupt.h"
#include "ISR_Timer.h"

#define INPUT_PIN = A0;
#define OUTPUT_PIN_1 = 4; 
#define OUTPUT_PIN_2 = 5;
#define OUTPUT_PIN_PWM = 9;

void setup(){
    // initialize pins 
    pinMode(OUTPUT_PIN_1, OUTPUT);
    pinMode(OUTPUT_PIN_2, OUTPUT);
    pinMode(OUTPUT_PIN_3, OUTPUT);
    pinMode(OUTPUT_PIN_4, OUTPUT);

    // initialize timers 
    ITimer1.init();
    ITimer2.init();

  attachInterrupt(digitalPinToInterrupt(PIN_SIGNAL_IN), CountFallingEdges, FALLING);

}
void loop(){ 
    // calculate detected frequency logic 
    unsigned long interval = millis() - curr_time;
    if (interval > 2000){
      Serial.println(CalculateFreq(counter, interval)); 
      curr_time = millis(); // update to current time 
    }
  
    //potentiometer logic 
    int potValue = analogRead(INPUT_PIN);
    long new_duty_cycle = map(potValue, 0, 1023, 0, 100) // translate pot -> duty cycle 
    analogWrite(OUTPUT_PIN_PWM, new_duty_cycle)
    if (new_duty_cycle != cur_duty_cycle){ 
        cur_duty_cycle = new_duty_cycle;
        ITimer1.setFrequency(currentFreq, TimerHandler);
    }
  }
  
void TimerHandler(){
    //when timer expires 
    toggleState = !toggleState;
    digitalWrite(OUTPUT_PIN_PWM, toggleState);
  }

bool is_serial(){
    // returns true if the user types in something in the 
    // serial monitor 
    return Serial.available();
}

void clear_serial(){
    // clears serial buffer 
    while(!Serial.available()){
        Serial.read()
    }
}




