/*
#include "IOBlink.h"
IOBlink _IoB(LED_BUILTIN, HIGH);
void setup() {
  _IoB.attach_ms(111,800,200);
  //_IoB.attach_ms(111,1,0); // luôn on
  //_IoB.attach_ms(111,0,1); // luôn off
}

void loop() {
  _IoB.Blink();
}

*/

#ifndef	_IOBLINK_H
#define _IOBLINK_H
#include <Arduino.h>
#include <stdint.h>
#include <stddef.h>
#include "TimeOutEvent.h"

#define TaskIoBDelay               0
#define TaskIoBStop                1
#define TaskIoBOn                  2
#define TaskIoBOff                 3

class IOBlink : public TimeOutEvent {
public:
	IOBlink(short _IO = 2, bool Lever = LOW);
	void attach_ms(uint8_t Count, uint16_t DelayOn, uint16_t DelayOff);
	void On(void);
	void Off(void);
	void Blink(void);	

protected:
	const short _IOPIN;
	uint8_t TaskIoB = TaskIoBStop;
	uint16_t IoBDelayOff = 200;
	uint16_t IoBDelayOn = 800;
	uint8_t IoBPre = 1;
	uint8_t IoBCount = 0;
	bool On_Status = LOW;
	bool Off_Status = HIGH;
};
#endif
