#set text(size: 12pt)
#set align(center)
= ME210 Introduction to Mechatronics \ Prelab 2\
Winter 2026 \
Julia Jiang 

#set align(left)

= Part 1 
== Source Code
```cpp

```

== 1.4 Frequency of Duty Cycle Waveform 

== 1.5 Increasing Operating Frequency

== 1.6 
If we want more duty cycle resolution, the upper frequency limit decreases because the hardware counter has to count higher (for more resolution) in each cycle, which takes more time and decreases the number of cycles possible in each second (frequency).

== 1.7 
At 0% or 100% duty cycle, one of the on/off intervals becomes zero, which cannot be scheduled by a timer interrupt. The output therefore saturates HIGH or LOW depending on state.
== 1.8 
Error sources: 
- 
- 
- 

== 1.9 
A higher PWM frequency decreases voltage ripple, but this means the resolution is smaller. 

= Part 2 
