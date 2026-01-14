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
//TODO: write these as functions 

// turn motor on
Raptor.LeftMtrSpeed(HALF_SPEED);
Raptor.RightMtrSpeed(HALF_SPEED);

// turn motor off
Raptor.LeftMtrSpeed(0);
Raptor.RightMtrSpeed(0);

// get char from keyboard 
Serial.read(); 

// print value to serial monitor
Serial.println("Hello World!");

// read light sensor 
uint16_t light_sensor = Raptor.LightLevel();

// beep the buzzer 
Raptor.Beep(260, 5000); // frequency(Hz), time(ms)

// turn on rgb led 
Raptor.RGB(200, 100, 150); // R, G, B

// test ir bumpers - bitwise tests? 
uint8_t trigger_state = Raptor.ReadTriggers();

// masks 

// and functions 
uint8_t is_line_left = 
uint8_t is_edge_left = 
uint8_t is__line_center = 
uint8_t is_edge_right = 
uint8_t is_line_right = 



