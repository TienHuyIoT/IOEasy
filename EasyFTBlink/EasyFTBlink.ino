#include "FTBlink.h"
/* Khởi động IO LED
LED_BUILTIN: là IO LED cần điều khiển
HIGH: IO LED điều khiển tích cực mức cao.
 */
FTBlink _IoLed;
void Led_On(void){
	digitalWrite(LED_BUILTIN, HIGH);
}
void Led_Off(void){
	digitalWrite(LED_BUILTIN, LOW);
}
void setup() {
	pinMode(LED_BUILTIN, OUTPUT);
	_IoLed.RegCallBack(&Led_On,&Led_Off);
  _IoLed.attach_ms(111,800,200);  
}

void loop() {
  _IoLed.Blink();
}
