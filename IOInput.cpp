#include <Arduino.h>
#include <stddef.h>
#include <stdint.h>
#include "IOInput.h"

#define IOINPUT_PORT Serial
#define IOINPUT_DBG(fmt, ...) //IOINPUT_PORT.printf("\r\n>IOINPUT< " fmt, ##__VA_ARGS__)

IOInput::IOInput(short _IO, uint8_t Lever, uint16_t S_To, uint16_t H_Cnt, uint16_t L_Cnt)
    : ToE(100), _IOPIN(_IO), flagInput(Lever), SampleTo(S_To), SampleHigh(H_Cnt), SampleLow(L_Cnt)
{
  pinMode(_IOPIN, INPUT_PULLUP);
}

void IOInput::loop(void)
{
  if (!ToE.ToEExpired())
    return;
  ToE.ToEUpdate(SampleTo);
  if (digitalRead(_IOPIN) == LOW)
  {
    LowCount++;
    if (LowCount == SampleLow)
    {
      flagInput = LOW;
      LowTime = millis();
      IOINPUT_DBG("%u: LOW",_IOPIN);
    }
    if (LowCount >= SampleLow)
    {
      HighCount = 0;
      LowCount = SampleLow;
    }
  }
  else
  {
    HighCount++;
    if (HighCount == SampleHigh)
    {
      flagInput = HIGH;
      HighTime = millis();
      IOINPUT_DBG("%u: HIGH",_IOPIN);
    }
    if (HighCount >= SampleHigh)
    {
      LowCount = 0;
      HighCount = SampleHigh;
    }
  }
}

uint32_t IOInput::GetTime(uint8_t Lever)
{
  if (Lever == flagInput)
  {
    if (flagInput == HIGH)
      return (millis() - HighTime);
    else
      return (millis() - LowTime);
  }
  else
    return 0;
}

uint8_t IOInput::GetStatus(void)
{
  return flagInput;
}

void IOInput::set_high_cnt_ms(uint16_t High)
{
  SampleHigh = High;
}

void IOInput::set_low_cnt_ms(uint16_t Low)
{
  SampleLow = Low;
}

void IOInput::set_status_init(uint8_t St)
{
  flagInput = St;
}

void IOInput::set_sample_ms(uint16_t Sp)
{
  SampleTo = Sp;
  ToE.ToEUpdate(SampleTo);
}

void IOInput::set_low_time_ms(uint32_t Low)
{
  LowTime = millis() - Low;
}

void IOInput::set_high_time_ms(uint32_t High)
{
  HighTime = millis() - High;
}