#include "MoreTimers.h"

hw_timer_t* MoreTimers::My_timer = NULL;
int MoreTimers::_timerNo = 0;
MoreTimers* MoreTimers::_timer[20];
volatile bool MoreTimers::_triggered = false;

MoreTimers::MoreTimers() {
  check = false;
  _triggered = false;
}
void MoreTimers::begin(uint64_t timeInMilliSeconds) {
  _timer[_timerNo] = this;
  if (_timerNo == 0) {
    My_timer = timerBegin(1, 80, true);
    timerAttachInterrupt(My_timer, &TimerIsr, true);
    timerAlarmWrite(My_timer, 10000, true);  // .5s
    timerAlarmEnable(My_timer);
  }
  _timerNo++;
  _time = timeInMilliSeconds;
}

void MoreTimers::alarmEnable(bool Autoreload, bool Async) {
  check = true;
  _counter = _time;
  _autoreload = Autoreload;
  _async = Async;
}
void MoreTimers::alarmDisable() {
  check = false;
  _counter = 0;
  _autoreload = false;
}

void MoreTimers::TimerIsr() {
  for (int i = 0; i < _timerNo; i++) {
    if (_timer[i]->_async) {
      if (_timer[i]->check) {
        _timer[i]->_counter--;
        if (_timer[i]->_counter == 0) {
          if (_timer[i]->_timerCb != NULL) {
            if (_timer[i]->_autoreload) _timer[i]->_counter = _timer[i]->_time;
            _timer[i]->_timerCb(_timer[i]->_timerCb_arg, _timer[i]);
          }
        }
      }
    }
    else _triggered = true;
  }
}


void MoreTimers::onTimer(TimerHandler callbackFunc, void* arg) {
  _timerCb = callbackFunc;
  _timerCb_arg = arg;
}

void MoreTimers::run() {
  if (_triggered) {
    for (int i = 0; i < _timerNo; i++) {
      if (_timer[i]->check) {
        _timer[i]->_counter--;
        if (_timer[i]->_counter == 0) {
          // Serial.println("timerisr");
          if (_timer[i]->_timerCb != NULL) _timer[i]->_timerCb(_timer[i]->_timerCb_arg, _timer[i]);
          if (_timer[i]->_autoreload) _timer[i]->_counter = _timer[i]->_time;
        }
      }
    }
    _triggered = false;
  }
}
