#include "MoreTimers.h"

hw_timer_t* MoreTimers::My_timer = NULL;
int MoreTimers::_timerNo = 0;
MoreTimers* _timer[20];

MoreTimers::MoreTimers(){
  check=false;
}
void MoreTimers::begin(unsigned long timeInHundredMilliSeconds){
  _timer[_timerNo]=this;
  if(_timerNo== 0){
    My_timer = timerBegin(3, 80, true);
    timerAttachInterrupt(My_timer, &TimerIsr, true);
    timerAlarmWrite(My_timer, 100000, true);  // .5s
  }
  _timerNo++;
  _time=timeInHundredMilliSeconds;
}

void MoreTimers::alarmEnable(bool Autoreload){
  check = true;
  _counter=_time/100000;
  _autoreload= Autoreload;
}
void MoreTimers::alarmDisable(){
  check = false;
  _counter = 0;
  _autoreload= false;
}

void MoreTimers::TimerIsr(){
  for(int i= 0;i<_timerNo;i++){
    if(_timer[i]->check){
      _timer[i]->_counter--;
      if(_timer[i]->_counter == 0) {
        if(_timer[i]->_timerCb != NULL) _timer[i]->_timerCb(_timer[i]->_timerCb_arg, _timer[i]);
        if(_timer[i]->_autoreload)_timer[i]->_counter=_timer[i]->_time/100000;
      }
    }
  }
}

void MoreTimers::onTimer(TimerHandler callbackFunc, void* arg){
    _timerCb = callbackFunc;
    _timerCb_arg = arg;
}

// void MoreTimers::run(){
//   for(int i= 0;i<_timerCounter;i++){
//     if(MoreTimers[i].tripped) _timerCb(_timerCb_arg,this);
//   }
// }
