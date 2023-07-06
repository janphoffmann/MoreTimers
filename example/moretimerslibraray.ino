#include <Arduino.h>
#include "MoreTimers.h"

// declare instances
MoreTimers firstTimer,secondTimer;

//describe Callbacks
void firstTimerCb(void* arg, MoreTimers* t){
  Serial.printf("Timer mit time %d triggered\r\n",t->_time);
}
void secondTimerCb(void* arg, MoreTimers* t){
  Serial.printf("Timer mit time %d triggered\r\n",t->_time);
}

void setup() {
  Serial.begin(115200);
  Serial.println("starting");
  // attatch interrupts to timers
  firstTimer.onTimer(firstTimerCb);
  secondTimer.onTimer(secondTimerCb);

  // begin functions with time in ms
  firstTimer.begin(100);//25000
  secondTimer.begin(500);

  // enable the alarm sytax: MoreTimers::alarmEnable(bool autoreload = true, bool Async=false)
  //enable alarm for first timer, that autoreloads and the callback is not in the ISR, so you have plenty of time
  firstTimer.alarmEnable();
  //enable second alarm that autoreloads after every alarm, and callback is inside the ISR, so hurry 
  secondTimer.alarmEnable(true,true);
}

void loop() {
  // if you have a timer that is not async, like the first one in this example, you have to call MoreTimers::run() but only one run() for all is needed...
  firstTimer.run();
}
