#ifndef MORETIMERS_H
#define MORETIMERS_H

#include <Arduino.h>
#include <functional>

class MoreTimers;

typedef std::function<void(void*, MoreTimers*)> TimerHandler;

class MoreTimers{
private:
  static hw_timer_t* My_timer;
  static void ARDUINO_ISR_ATTR TimerIsr();
  static MoreTimers* _timer[20];
  static int _timerNo;
  unsigned long _time;
  volatile bool check;
  volatile uint16_t _counter;
  bool _autoreload;
  TimerHandler _timerCb = NULL;
  void* _timerCb_arg = NULL;
public:
  MoreTimers();
  void begin(unsigned long timeInHundredMilliSeconds);
  void alarmEnable(bool Autoreload = true);
  void alarmDisable();
  void onTimer(TimerHandler callbackFunc, void* arg);
};


#endif
