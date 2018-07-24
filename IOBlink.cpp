#include <Arduino.h>
#include <stddef.h>
#include <stdint.h>
#include "IOBlink.h"

IOBlink::IOBlink(short _IO, bool Lever)
  : _IOPIN(_IO), On_Status(Lever), TimeOutEvent(500)
{
  pinMode(_IOPIN, OUTPUT);
  Off_Status = !On_Status;
  digitalWrite(_IOPIN, Off_Status);
}

void IOBlink::attach_ms(uint8_t Count, uint16_t DelayOn, uint16_t DelayOff)
{
  IoBCount = Count;
  if (Count == 0) {
    TaskIoB = TaskIoBStop;
    digitalWrite(_IOPIN, Off_Status);
  }
  IoBDelayOff = DelayOff;
  IoBDelayOn = DelayOn;
}

void IOBlink::Blink(void)
{
  switch (TaskIoB) {
    case TaskIoBStop:
      if (IoBCount > 0) {
        TaskIoB = TaskIoBOn;
        IoBPre = 1;
        pinMode(_IOPIN, OUTPUT);
      }
      break;
    case TaskIoBOn:
      if (IoBPre == 1) {
        IoBPre = 0;
        ToEUpdate(IoBDelayOn);
        //Nếu timeout > 0 thì mới điều khiển IO
        if(IoBDelayOn) digitalWrite(_IOPIN, On_Status);
      }
      if (!ToEExpired()) break;
      TaskIoB = TaskIoBOff;
      IoBPre = 1;
      break;
    case TaskIoBOff:
      if (IoBPre == 1) {
        IoBPre = 0;
        ToEUpdate(IoBDelayOff);
        //Nếu timeout > 0 thì mới điều khiển IO
        if(IoBDelayOff) digitalWrite(_IOPIN, Off_Status);
      }

      if (!ToEExpired()) break;
      TaskIoB = TaskIoBOn;
      IoBPre = 1;

      if (--IoBCount == 0) {
        TaskIoB = TaskIoBStop;
      } else {
        //Muc dich khi >100 thi led nhay mai mai
        if (IoBCount > 100) IoBCount++;
      }
      break;
  }
}
