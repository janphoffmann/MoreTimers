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
  
  volatile bool check;
  volatile uint32_t _counter;
  volatile bool _autoreload;
  TimerHandler _timerCb = NULL;
  void* _timerCb_arg = NULL;
  static volatile bool _triggered;
  volatile bool _async;
public:
  void run();
  uint64_t _time;
  MoreTimers();
  void begin(uint64_t timeInMilliSeconds);
  void alarmEnable(bool Autoreload = true,bool Async = false);
  void alarmDisable();
  void onTimer(TimerHandler callbackFunc, void* arg = NULL);
};


#endif
