#include <Arduino.h>
#include <stddef.h>
#include <stdint.h>
#include "TimeOutEvent.h"
TimeOutEvent::TimeOutEvent(uint32_t Tio)
{
  ToEUpdate(Tio);
  /*Nếu khởi động timeout = 0 thì mặc định disable*/
  if (Tio == 0) this->En = false;
}

void TimeOutEvent::ToEUpdate(uint32_t Tio)
{
  this->TSta = millis();
  this->Tio = Tio;
  this->En = true;
}

bool TimeOutEvent::ToEExpired(void)
{
  if ((this->En) && ((millis() - this->TSta) >= this->Tio))
  {
    this->En = false;
    return true;
  }
  return false;
}

void TimeOutEvent::ToEDisable(void){
  this->En = false;
}

bool TimeOutEvent::ToEGetStatus(void){
  return this->En;
}