/* 
* SoftTimer.h
*
* Created: 3/28/2015 2:57:59 PM
* Author: huszty
*/


#ifndef __SOFTTIMER_H__
#define __SOFTTIMER_H__

#define SET_EVENT_MASK 0x01
#define RESET_EVENT_MASK 0x02
#define TIMEOUT_EVENT_MASK 0x04

#define MSEC 8

class SoftTimerHandler;

class SoftTimer {
  unsigned short remaining;
  SoftTimerHandler *handler;
  unsigned char subscriptions;
public:
  SoftTimer();
  SoftTimer(SoftTimerHandler *newHandler, bool useSet, bool useReset, bool useTimeout);
  void set(unsigned short value);
  void reset();
  unsigned short get();
  void tick();
};

class SoftTimerHandler {
protected:
  SoftTimer myTimer;
public:
  SoftTimerHandler(bool useSet, bool useReset, bool useTimeout);
  virtual unsigned short handleTimerSet(unsigned short oldValue, unsigned short newValue);
  virtual void handleTimerReset(unsigned short oldValue);
  virtual void handleTimeout();
  SoftTimer* getTimer();
};

#endif //__SOFTTIMER_H__
