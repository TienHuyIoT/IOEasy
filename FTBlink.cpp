#include <Arduino.h>
#include <stddef.h>
#include <stdint.h>
#include "FTBlink.h"

FTBlink::FTBlink(void) : TimeOutEvent(500)
{ 
}

void FTBlink::RegCallBack(void (*On)(void), void (*Off)(void)){
  Ft_On = On;
  Ft_Off = Off;
}

void FTBlink::attach_ms(uint8_t Count, uint16_t DelayOn, uint16_t DelayOff)
{
  FTBCount = Count;
  if (Count == 0) {
    TaskFtB = TaskFtBStop;
    Ft_Off();
  }
  FTBDelayOff = DelayOff;
  FTBDelayOn = DelayOn;
}

void FTBlink::On(void)
{
  FTBCount = 0;
  TaskFtB = TaskFtBStop;
  Ft_On();
}

void FTBlink::Off(void)
{
  FTBCount = 0;
  TaskFtB = TaskFtBStop;
  Ft_Off();
}

void FTBlink::Blink(void)
{
  switch (TaskFtB) {
    case TaskFtBStop:
      if (FTBCount > 0) {
        TaskFtB = TaskFtBOn;
        FTBPre = 1;
      }
      break;
    case TaskFtBOn:
      if (FTBPre == 1) {
        FTBPre = 0;
        ToEUpdate(FTBDelayOn);
        //Nếu timeout > 0 thì mới điều khiển IO
        if(FTBDelayOn) Ft_On();
      }
      if (!ToEExpired()) break;
      TaskFtB = TaskFtBOff;
      FTBPre = 1;
      break;
    case TaskFtBOff:
      if (FTBPre == 1) {
        FTBPre = 0;
        ToEUpdate(FTBDelayOff);
        //Nếu timeout > 0 thì mới điều khiển IO
        if(FTBDelayOff) Ft_Off();
      }

      if (!ToEExpired()) break;
      TaskFtB = TaskFtBOn;
      FTBPre = 1;

      if (--FTBCount == 0) {
        TaskFtB = TaskFtBStop;
      } else {
        //Muc dich khi >100 thi led nhay mai mai
        if (FTBCount > 100) FTBCount++;
      }
      break;
  }
}

