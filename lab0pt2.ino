#include <Raptor.h>
#include <SPI.h>

#include <SPI.h>
#include <Metro.h>

/*---------------Module Defines-----------------------------*/

#define LIGHT_THRESHOLD          50   // *Choose your own thresholds*
                                    // (this will be smaller at night)
#define LINE_THRESHOLD          350   // *Choose your own thresholds*

#define LED_TIME_INTERVAL       1000 //ms 
#define MOTOR_TIME_INTERVAL     2000  
#define ROTATE_TIME_INTERVAL    3000
#define RETREAT_TIME_INTERVAL  3000

#define HALF_SPEED              50

#define TIMER_0            0
/*---------------Module Function Prototypes-----------------*/
void handleMoveForward(void);
void handleMoveBackward(void);
void handleAdvance(void);
void rotate(void);
void handleRetreat(void);
void respMotorTimerExpired(void);
uint8_t TestLedTimerExpired(void);
uint8_t TestRetreatTimerExpired(void);
uint8_t TestRotateTimerExpired(void);
void RespLedTimerExpired(void);
void RespRotateTimerExpired(void);
void RespRetreatTimerExpired(void);
uint8_t TestForKey(void);
void RespToKey(void);
void checkGlobalEvents(void);
uint8_t TestForLightOn(void);
uint8_t TestForLightOff(void);
void ResptToLightOn(void);
void ResptToLightOff(void);
uint8_t TestForFence(void);
void RespToFence(void);

// Testing Functions 
void PrintLightThreshold(void);
void PrintLineThreshold(void);
void TurnMotorOn(void);
void TurnMotorOff(void);
char GetChar(void);
void PrintValue(void);
void ReadLightSensor(void);
void BeepBuzzer(void);
void TurnOnLed(void);
void IsLeftLine(void);
void IsLeftEdge(void);
void IsCenterLine(void);
void IsRightEdge(void);
void IsRightLine(void);

/*---------------State Definitions--------------------------*/
typedef enum {
  STATE_MOVE_FORWARD, STATE_MOVE_BACKWARD, STATE_LURKING, 
  STATE_ADVANCING, STATE_RETREATING, STATE_ROTATING
} States_t;

/*---------------Module Variables---------------------------*/
States_t state;
static Metro metTimer0 = Metro(LED_TIME_INTERVAL);
static Metro retreatTimer = Metro(RETREAT_TIME_INTERVAL);
static Metro rotateTimer = Metro(ROTATE_TIME_INTERVAL);
static Metro motorTimer = Metro(MOTOR_TIME_INTERVAL); 
uint8_t isLEDOn;

/*---------------raptor Main Functions----------------*/

void setup() {
  // put your setup code here, to run once:
  
  /* Open the serial port for communication using the Serial
     C++ class. On the Leonardo, you must explicitly wait for
   the class to report ready before commanding a println.
  */
  Serial.begin(9600);
  while(!Serial);
  Serial.println("Hello, world!");
  // state = STATE_ADVANCING; 
  state = STATE_MOVE_FORWARD;
  motorTimer.reset();
  isLEDOn = false;
}

// void loop() {
//   checkGlobalEvents();
//   switch (state) {
//     case STATE_ROTATING: 
//       rotate();
//       break;
//     case STATE_ADVANCING: 
//       handleAdvance(); 
//       break;
//     case STATE_RETREATING: 
//       handleRetreat(); 
//       break; 
//     default: //default state is lurking 
//       handleLurk(); 
//   }  
// } 

void loop() {
  checkGlobalEvents();
  static States_t last_state = STATE_MOVE_BACKWARD;
  if (state != last_state) {
    switch (state) {
      case STATE_MOVE_FORWARD:
        handleMoveForward();
        break;
      case STATE_MOVE_BACKWARD:
        handleMoveBackward();
        break;
      default:
        Serial.println("What is this I do not even...");
        break;
    }
    last_state = state;
  }
}
// void loop(){   
//   if (motorTimer.check()) respMotorTimerExpired();
//   checkGlobalEvents(); 
//   switch (state) {
//     case STATE_MOVE_FORWARD:
//       handleMoveForward();
//       break;
//     case STATE_MOVE_BACKWARD:
//       handleMoveForward();
//       break;
//     default:    // Should never get into an unhandled state
//       Serial.println("What is this I do not even...");
//   }
// }

/*----------------Module Functions--------------------------*/


void checkGlobalEvents(void) {
  if (motorTimer.check()) respMotorTimerExpired();

  if (TestLedTimerExpired()) RespLedTimerExpired();
  if (TestForKey()) RespToKey();
  
  // if(TestForLightOff()) RespToLightOff(); 
  // if(state == STATE_LURKING && TestForLightOn()) RespToLightOn(); 

  // if(state == STATE_ROTATING && TestRotateTimerExpired()) RespRotateTimerExpired();
  // if(state == STATE_RETREATING && TestRetreatTimerExpired()) RespRetreatTimerExpired(); 
  // if(TestForFence()) RespToFence(); 
}

//returns 1 if light is on 
uint8_t TestForLightOn(void) { 
  if (raptor.LightLevel() >= LIGHT_THRESHOLD) return 1;
  return 0; 
}

void handleMoveForward(void){
    raptor.LeftMtrSpeed(HALF_SPEED); //move forwards 
    raptor.RightMtrSpeed(HALF_SPEED);
  return;
}

void handleMoveBackward(void){
  raptor.LeftMtrSpeed(-1*HALF_SPEED);  
  raptor.RightMtrSpeed(-1*HALF_SPEED);
  return;
}

void respMotorTimerExpired(void){
  //make the robot change states and then reset the timer 
  motorTimer.reset(); 
  if (state == STATE_MOVE_FORWARD){
    state = STATE_MOVE_BACKWARD; 
    handleMoveBackward();
  }
  else {
    state = STATE_MOVE_FORWARD; 
    handleMoveForward(); 
  } 
  return;
}


void handleAdvance(void) {
  raptor.LeftMtrSpeed(HALF_SPEED); //move forwards 
  raptor.RightMtrSpeed(HALF_SPEED);
  //delay(MOTOR_TIME_INTERVAL);
  //state = STATE_MOVE_BACKWARD;
}

void rotate(void){
  raptor.LeftMtrSpeed(HALF_SPEED);
  raptor.RightMtrSpeed(0);
  return;
}

void handleRetreat(void) {
  state = STATE_RETREATING;
  raptor.LeftMtrSpeed(-25); //robot doesn't back up in straight line 
  raptor.RightMtrSpeed(-1*HALF_SPEED);
  //delay(MOTOR_TIME_INTERVAL);
  //state = STATE_MOVE_FORWARD;
}

void handleLurk(void){
  TurnMotorOff();
  return;
}

uint8_t TestLedTimerExpired(void) {
  return (uint8_t) metTimer0.check();
}

uint8_t TestRetreatTimerExpired(void) {
  return (uint8_t) retreatTimer.check();
}

uint8_t TestRotateTimerExpired(void) {
  return (uint8_t) rotateTimer.check();
}

void RespLedTimerExpired(void) {
  metTimer0.reset();
  if (isLEDOn) {     
    isLEDOn = false;
    raptor.RGB(RGB_OFF);
  } else {
    isLEDOn = true;
    raptor.RGB(RGB_WHITE);
  }
}

void RespRotateTimerExpired(void){
  // transition to advancing state 
  state = STATE_ADVANCING;
}

void RespRetreatTimerExpired(void){
  // transition to rotating state
  state = STATE_ROTATING; 
  rotateTimer.reset(); 
}

uint8_t TestForKey(void) {
  uint8_t KeyEventOccurred;
  KeyEventOccurred = Serial.available();
  return KeyEventOccurred;
}

void RespToKey(void) {
  uint8_t theKey;
  theKey = Serial.read();
  Serial.print(theKey);
  Serial.print(", ASCII=");
  Serial.println(theKey, HEX);
}

//returns 1 if light is off 
uint8_t TestForLightOff(void) {
  if (raptor.LightLevel() < LIGHT_THRESHOLD) return 1;
  return 0;
}

void RespToLightOn(void) {
  state = STATE_ADVANCING; 
  return;
}

void RespToLightOff(void) {
  state = STATE_LURKING;
  return; 
}

//returns 1 if there is fence 
uint8_t TestForFence(void) {
  if (raptor.ReadTriggers(LINE_THRESHOLD)) return 1;
  return 0;
}

void RespToFence(void) {
  state = STATE_RETREATING;
  retreatTimer.reset();
  return;
}


/***********Test Functions for Part II******************************************************/

// identify light threshold
void PrintLightThreshold(void) {
  Serial.println(LIGHT_THRESHOLD);
  return;
}

// identify line threshold 
void PrintLineThreshold(void) {
  Serial.println(LINE_THRESHOLD);
  return;
}

void TurnMotorOn(void){
  raptor.LeftMtrSpeed(HALF_SPEED);
  raptor.RightMtrSpeed(HALF_SPEED);
  return; 
}

void TurnMotorOff(void){
  raptor.LeftMtrSpeed(0);
  raptor.RightMtrSpeed(0);
  return; 
}

char GetChar(void){
  return Serial.read(); 
}

void PrintValue(void){
  Serial.println("Hello World!");
  return;
}

void ReadLightSensor(void){
  int16_t light_sensor = raptor.LightLevel();
  Serial.println(light_sensor);
}


void BeepBuzzer(void){
  raptor.Beep(260, 5000);
  return;
}


void TurnOnLed(void){
  raptor.RGB(200, 100, 150); // R, G, B
  return;
}

void IsLeftLine(void){
   uint8_t trigger_state = raptor.ReadTriggers(LINE_THRESHOLD);
  Serial.println(trigger_state & 0x01);
  return;
}
void IsLeftEdge(void){
   uint8_t trigger_state = raptor.ReadTriggers(LINE_THRESHOLD);
  Serial.println(trigger_state & 0x02);
  return;
}
void IsCenterLine(void){
   uint8_t trigger_state = raptor.ReadTriggers(LINE_THRESHOLD);
  Serial.println(trigger_state & 0x04);
  return;
}
void IsRightEdge(void){
   uint8_t trigger_state = raptor.ReadTriggers(LINE_THRESHOLD);
  Serial.println(trigger_state & 0x08);
  return;
}
void IsRightLine(void){
   uint8_t trigger_state = raptor.ReadTriggers(LINE_THRESHOLD);
  Serial.println(trigger_state & 0x10);
  return;
}

