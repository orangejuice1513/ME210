
#set text(size: 12pt)
#set align(center)
= ME210 Introduction to Mechatronics \ Lab 0\
Winter 2026 \
Julia Jiang 

#set align(left)
= Section 2 
== 2.5 LED Blinking Frequency 
The LED doesn't blink at 0.5Hz because the time interval of 1000ms corresponds to 1Hz and the delay lines in moving forward and backward. 

== 2.6 Identifying Light and Line Thresholds 
LIGHT_THRESHOLD = 0 \
LINE_THRESHOLD = 0
```cpp
void PrintLightThreshold(LIGHT_THRESHOLD){
  //identify light threshold 
  Serial.println(LIGHT_THRESHOLD)
}
void PrintLineThreshold(LINE_THRESHOLD)){
  //identify line threshold 
  Serial.println(LINE_THRESHOLD)
}
```

== 2.7 Given Functions 
```cpp
uint8_t TestForLightOn(void) { 
  //returns 1 if light is on 
  if (raptor.LightLevel() >= LIGHT_THRESHOLD) return 1;
  return 0; 
}
uint8_t TestForLightOff(void) {
  //returns 1 if light is off 
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
uint8_t TestForFence(void) {
  //returns 1 if there is fence 
  if (raptor.ReadTriggers(LINE_THRESHOLD)) return 1;
  return 0;
}
void RespToFence(void) {
  state = STATE_RETREATING;
  return;
}

```


== 2.8 Simple Testing Programs 
```cpp
void TurnMotorOn(){
  Raptor.LeftMtrSpeed(HALF_SPEED);
  Raptor.RightMtrSpeed(HALF_SPEED);
  return;
}
void TurnMotorOff(){
  Raptor.LeftMtrSpeed(0);
  Raptor.RightMtrSpeed(0);
  return;
}
char GetChar(){
  return Serial.read();
}
void PrintValue(){
  Serial.println("Hello World!");
  return;
}
void ReadLightSensor(){
  int16_t light_sensor = Raptor.LightLevel();
  Serial.println(light_sensor);
}
void BeepBuzzer(){
  Raptor.Beep(260, 5000);
  return;
}
void TurnOnLed(){
  Raptor.RGB(200, 100, 150); // R, G, B
  return;
}
// test ir bumpers
void IsLeftLine(){
  trigger_state = Raptor.ReadTriggers();
  return (trigger_state & 0x01);
}
void IsLeftEdge(){
  trigger_state = Raptor.ReadTriggers();
  return (trigger_state & 0x02);
}
void IsCenterLine(){
  trigger_state = Raptor.ReadTriggers();
  return (trigger_state & 0x04);
}
void IsRightEdge(){
  trigger_state = Raptor.ReadTriggers();
  return (trigger_state & 0x08);
}
void IsRightLine(){
  trigger_state = Raptor.ReadTriggers();
  return (trigger_state & 0x10);
}
```

= Section 3 
== 3.1
=== Finite State Diagram 
#figure(image("image.png"))

=== Pseudocode


=== Final Source Code 


void handleAdvance(void) {
  raptor.LeftMtrSpeed(HALF_SPEED); //move forwards 
  raptor.RightMtrSpeed(HALF_SPEED);
  //delay(MOTOR_TIME_INTERVAL);
  //state = STATE_MOVE_BACKWARD;
}

void rotate(void){
  rotateTimer.reset(); 
  raptor.LeftMtrSpeed(HALF_SPEED);
  raptor.RightMtrSpeed(0);
}

void handleRetreat(void) {
  retreatTimer.reset(); 
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

void checkGlobalEvents(void) {
  if (TestLedTimerExpired()) RespLedTimerExpired();
  if (TestForKey()) RespToKey();
  
  if(TestForLightOff()) RespToLightOff(); 
  if(TestForLightOn()) RespToLightOn(); 

  if(TestRotateTimerExpired()) RespRotateTimerExpired();
  if(TestRetreatTimerExpired()) RespRetreatTimerExpired(); 
  if(TestForFence()) RespToFence(); 
}

//returns 1 if light is on 
uint8_t TestForLightOn(void) { 
  if (raptor.LightLevel() >= LIGHT_THRESHOLD) return 1;
  return 0; 
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
  return;
}


