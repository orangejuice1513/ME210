#set text(size: 12pt)
#set align(center)
= ME210 Introduction to Mechatronics \ Lab 1 Prelab\
Winter 2026 \
Julia Jiang 

#set align(left)
= Prelab 
== 0.1)
=== a. $220 Omega$
=== b. $1k Omega$
=== c. $47k Omega$ 
=== d. $1M Omega$

== 0.2)
=== a. $22 * 10^(3) "pF" = 22"nF"$
=== b. $47 * 10^(6) "pF" = 47mu"F"$

== 0.3)  
#image("prelab1.png")

== 0.4)
```cpp 
#include <SPI.h>

void setup(){
  Serial.begin(9600);
}

void loop(){
  delay(1000) //1000ms;
  Serial.println("Hello, World!");
}
```