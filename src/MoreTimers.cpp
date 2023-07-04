#include "MoreTimers.h"

hw_timer_t* MoreTimers::My_timer = NULL;
int MoreTimers::_timerCounter = 0;
MoreTimers* _timer[20];

MoreTimers::MoreTimers(){
  MoreTimers[_timerCounter++]=this;
}
void MoreTimers::begin(unsigned long timeInHundredMilliSeconds){
  My_timer = timerBegin(3, 80, true);
  timerAttachInterrupt(My_timer, std::bind(&MoreTimers::TimerIsr, this), true);
  timerAlarmWrite(My_timer, 100000, true);  // .5s
  _time=timeInHundredMilliSeconds;
}

void MoreTimers::alarmEnable(){
  check = true;
  
}
void MoreTimers::alarmDisable(){
  check = false;
}

void MoreTimers::TimerIsr(){
  for(int i= 0;i<_timerCounter;i++){
    if( && MoreTimers[i].ceck) _timerCb(_timerCb_arg,this);
  }
}
// void MoreTimers::run(){
//   for(int i= 0;i<_timerCounter;i++){
//     if(MoreTimers[i].tripped) _timerCb(_timerCb_arg,this);
//   }
// }