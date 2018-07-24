/*

#include "TimeOutEvent.h"
TimeOutEvent Toe1(500);
bool st=false;
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);  
}

void loop() {
  if(Toe1.ToEExpired()){
    Toe1.ToEUpdate(500);
    digitalWrite(LED_BUILTIN, st^=1);
  }
}
	
*/

#ifndef	_TIMEOUTEVENT_H
#define _TIMEOUTEVENT_H
#include <Arduino.h>
#include <stdint.h>
#include <stddef.h>

class TimeOutEvent {
public:
	TimeOutEvent(uint32_t Tio = 0);
	void ToEUpdate(uint32_t Tio);
	bool ToEExpired(void);
  void ToEDisable(void); 
  bool ToEGetStatus(void);

protected:
	uint32_t TSta;  //Time Start
	uint32_t Tio;   //Timeout
  bool En;
};

#endif
