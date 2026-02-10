// pwm.ino: uses a potentiometer to control a pwm duty cycle for a brushed dc motor
// without motor driver 
// pwm is 1024 resolution 

#include "TimerInterrupt.h"
#include "ISR_Timer.h"

#define USE_TIMER_1   true  //on time 
#define USE_TIMER_2   true //off time 

#define INPUT_PIN       A0 //from pot 
#define OUTPUT_PIN_1    4
#define OUTPUT_PIN_2    5
#define OUTPUT_PIN_3    6
#define OUTPUT_PIN_4    7
#define OUTPUT_PIN_PWM  9

#define T               2040  // frequency = 1 / 2040 µs ≈ 490.2 Hz

/* prototypes */
void CountFallingEdges();
unsigned long CalculateFreq(int, unsigned long);
void stop_motor();
bool is_serial();
void clear_serial();
void Timer1Handler();  // end of ON time -> set LOW
void Timer2Handler();  // end of OFF time -> set HIGH

/* variable initialization */
volatile int counter = 0;           // counts falling edges for frequency
volatile bool pwmState = HIGH;      // current PWM output state
unsigned long curr_time = 0;        // for frequency measurement
volatile uint16_t cur_duty_cycle = 0;   // 0–1023 (resolution)

void setup(){
    Serial.begin(9600);

    // initialize pins 
    pinMode(OUTPUT_PIN_1, OUTPUT);
    pinMode(OUTPUT_PIN_2, OUTPUT);
    pinMode(OUTPUT_PIN_3, OUTPUT);
    pinMode(OUTPUT_PIN_4, OUTPUT);
    pinMode(OUTPUT_PIN_PWM, OUTPUT);

    // start PWM high; timers will drive transitions
    pwmState = HIGH;
    digitalWrite(OUTPUT_PIN_PWM, HIGH);

    // initialize timers
    ITimer1.init();
    ITimer2.init();

    // set initial duty from pot and start both timers (period = T ms)


    cur_duty_cycle = analogRead(INPUT_PIN);

    unsigned long on_us = ((unsigned long)cur_duty_cycle * T) >> 10;
    if (on_us > 0) ITimer1.setInterval(on_us, Timer1Handler);

    // start Timer1 
    if (on_us > 0) ITimer1.setInterval(on_us, Timer1Handler);

    // count falling edges on PWM pin for frequency measurement
    attachInterrupt(digitalPinToInterrupt(OUTPUT_PIN_PWM), CountFallingEdges, FALLING);

    curr_time = millis(); 
}

void loop(){
    // print measured frequency every 2 s
    unsigned long now = millis();
    unsigned long interval = now - curr_time;
    if (interval > 2000){
      Serial.println(CalculateFreq(counter, interval));
      curr_time = now;
    }
  
    //potentiometer logic 
    volatile uint16_t new_duty_cycle = analogRead(INPUT_PIN);
    if (new_duty_cycle != cur_duty_cycle){ 
        cur_duty_cycle = new_duty_cycle;
        float on_us  = ((unsigned long)cur_duty_cycle * T) >> 10;  // bit shift 10 = divide by 1024
        float off_us = T - on_us;
        if (on_us  > 0) ITimer1.setInterval((unsigned long)on_us, Timer1Handler);
        if (off_us > 0) ITimer2.setInterval((unsigned long)off_us, Timer2Handler);
    }

    // stops motor if a key is pressed 
    clear_serial(); //TODO: remove? 
    if (is_serial()){
        stop_motor();
    }
    
}

void CountFallingEdges(){
  counter++; 
}

unsigned long CalculateFreq(int edge_counts, unsigned long time_interval){
  counter = 0; // reset counter
  return edge_counts * 1000.0 / time_interval;
}

void Timer1Handler(){
    pwmState = LOW;
    digitalWrite(OUTPUT_PIN_PWM, LOW);
    unsigned long off_us = T - (((unsigned long)cur_duty_cycle * T) >> 10);
    if (off_us > 0) ITimer2.setInterval(off_us, Timer2Handler);
}

void Timer2Handler(){
    pwmState = HIGH;
    digitalWrite(OUTPUT_PIN_PWM, HIGH);
    unsigned long on_us = ((unsigned long)cur_duty_cycle * T) >> 10;
    if (on_us > 0) ITimer1.setInterval(on_us, Timer1Handler);
}


void stop_motor(){
    digitalWrite(OUTPUT_PIN_PWM, LOW); //output voltage is LOW 
    deleteTimer(ITimer1);
    deleteTimer(ITimer2);
    clear_serial();
    return;
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


