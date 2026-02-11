// pwm.ino: uses a potentiometer to control a pwm duty cycle for a brushed dc motor
// without motor driver 
// pwm is 1024 resolution 
// use 1 timer 
// use interrupt and the function should be toggling the state 
// 2 functions that attatch different interrupts to the same frequency 
// those functions also call each other 
// timers don't expire 

#define USE_TIMER_1   true  

#include "TimerInterrupt.h"
#include "ISR_Timer.h"

#define INPUT_PIN       A0 //from pot 
#define OUTPUT_PIN_1    4
#define OUTPUT_PIN_2    5
#define OUTPUT_PIN_3    6
#define OUTPUT_PIN_4    7
#define OUTPUT_PIN_PWM  9

#define FREQUENCY       490  //Hz
#define PERIOD          2.0  //ms 

/* prototypes */
void stop_motor();
bool is_serial();
void clear_serial();
void pull_high();
void pull_low();  

/* variable initialization */
volatile bool pwmState = HIGH;      // current PWM output state
unsigned long curr_time = 0;        // for frequency measurement
volatile uint16_t cur_duty_cycle = 0.50;   // default is 50% duty cycle 
volatile uint16_t on_duration = 1.0 //ms 
volatile uint16_t off_duration = 1.0 //ms

void setup(){
    Serial.begin(9600);

    // initialize pins 
    pinMode(OUTPUT_PIN_1, OUTPUT);
    pinMode(OUTPUT_PIN_2, OUTPUT);
    pinMode(OUTPUT_PIN_3, OUTPUT);
    pinMode(OUTPUT_PIN_4, OUTPUT);
    pinMode(OUTPUT_PIN_PWM, OUTPUT);

    ITimer1.init();     // initialize timer

    // interrupts at different times 
    ITimer1.attachInterruptInterval(off_duration, pull_high()); // pull high after 1 - duty cycle 
    ITimer1.attachInterruptInterval(on_duration, pull_low()); //pull low after duty cycle  
}

void loop(){
  
    //potentiometer logic 
    volatile uint16_t new_duty_cycle = analogRead(INPUT_PIN) << 10; 
    if (new_duty_cycle != cur_duty_cycle){ 
        cur_duty_cycle = new_duty_cycle;
        on_duration = cur_duty_cycle * PERIOD;
        off_duration = PERIOD - on_duration;
    }

    // stops motor if a key is pressed 
    clear_serial(); 
    if (is_serial()){
        digitalWrite(OUTPUT_PIN_PWM, LOW); //to stop the motor, just output LO 
    }
}

void pull_high(){
    // pulls the pwm pin to high 
    pwmState = HIGH;
    digitalWrite(OUTPUT_PIN_PWM, HIGH);
}

void pull_low(){
    // pulls the pwm pin to low 
    pwmState = LOW;
    digitalWrite(OUTPUT_PIN_PWM, LOW);
}

bool is_serial(){
    // returns true if the user types in something in the 
    // serial monitor 
    return Serial.available();
}

void clear_serial(){
    // clears serial buffer
    while (Serial.available()){
        Serial.read();
    }
}

