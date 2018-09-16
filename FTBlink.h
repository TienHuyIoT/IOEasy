/*
#include "FTBlink.h"
IOBlink _IoB(, _OFF);
void setup() {
  _IoB.attach_ms(111,800,200);
  //_IoB.attach_ms(111,1,0); // luôn on
  //_IoB.attach_ms(111,0,1); // luôn off
}

void loop() {
  _IoB.Blink();
}

*/

#ifndef  _FTBLINK_H
#define _FTBLINK_H
#include <Arduino.h>
#include <stdint.h>
#include <stddef.h>
#include "TimeOutEvent.h"

#define TaskFtBDelay               0
#define TaskFtBStop                1
#define TaskFtBOn                  2
#define TaskFtBOff                 3

class FTBlink : public TimeOutEvent {
public:
  FTBlink(void);
  void RegCallBack(void (*On)(void), void (*Off)(void));
  void attach_ms(uint8_t Count, uint16_t DelayOn, uint16_t DelayOff);
  void On(void);
  void Off(void);
  void Blink(void); 

protected:
  void (*Ft_On)(void);
  void (*Ft_Off)(void);
  uint8_t TaskFtB = TaskFtBStop;
  uint16_t FTBDelayOff = 200;
  uint16_t FTBDelayOn = 800;
  uint8_t FTBPre = 1;
   uint8_t FTBCount = 0;
};
#endif

