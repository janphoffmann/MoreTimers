#ifndef MORETIMERS_H
#define MORETIMERS_H

class MoreTimers{
private:
  static void ARDUINO_ISR_ATTR TimerIsr();
  static MoreTimers* _timer[20];
  static int _timerCounter;
  unsigned long _time;
public:
  MoreTimers();
  void begin(unsigned long timeInHundredMilliSeconds);

};




#endif