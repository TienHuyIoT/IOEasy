#include "TimeOutEvent.h"
#ifndef LED_BUILTIN
#define LED_BUILTIN  2 //IO LED on ESP8266-V12
#endif
/* Khởi động TimeOutEvent 500ms */
TimeOutEvent To500ms(500);
bool st = 0;
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);  
}

void loop() {
  /* Kiểm tra, nếu hết Timeout 500ms */
  if(To500ms.ToEExpired()){
    /* Update lại Timout 500ms */
    To500ms.ToEUpdate(500);
    digitalWrite(LED_BUILTIN, st^=1);
  }
}
