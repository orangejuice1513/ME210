= Lab 0

note: zipped up libraries and imported to arduino


= 2.5
The LED doesn't blink at 0.5Hz because the time interval of 1000ms corresponds to 1Hz and the delay lines in moving forward and backward.

delay(MOTOR_TIME_INTERVAL)

we commented out the delay lines and changed the time interval to 2000ms.

= 2.6
change to get light threshold later
// identify light threshold
void PrintLightThreshold(LIGHT_THRESHOLD){
  Serial.println(LIGHT_THRESHOLD)
}

// identify line threshold
void PrintLineThreshold(LINE_THRESHOLD)){
  Serial.println(LINE_THRESHOLD)
}

LIGHT_THRESHOLD = 0
LINE_THRESHOLD = 0

= 2.8
function implementations


= 2.9
simple test functions

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


hello

= 3.1
finite state diagram ------------------------


pseudocode -----------------------





final source code ----------------------------


