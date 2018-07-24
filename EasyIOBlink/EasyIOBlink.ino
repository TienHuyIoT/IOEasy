#include "IOBlink.h"
/* Khởi động IO LED
LED_BUILTIN: là IO LED cần điều khiển
HIGH: IO LED điều khiển tích cực mức cao.
 */
#ifndef LED_BUILTIN
#define LED_BUILTIN	2 //IO LED on ESP8266-V12
#endif
IOBlink _IoLed(LED_BUILTIN, HIGH);
/* Khởi động IO điều khiển còi
5: là IO còi cần điều khiển
LOW: IO còi điều khiển tích cực mức thấp.
 */
IOBlink _IoBuzz(5, LOW);
void setup() {
	/* 
	5: Nếu số lần nháy lớn hơn 100 thì nháy mãi
	100: Thời gian ON(ms)
	1900: Thời gian OFF(ms)
	*/
	_IoBuzz.attach_ms(5,100,1900);  
   
	/* 
	111: Nếu số lần nháy lớn hơn 100 thì nháy mãi
	800: Thời gian ON(ms)
	200: Thời gian OFF(ms)
	*/
	_IoLed.attach_ms(111,800,200);  
	//_IoLed.attach_ms(10,800,200);	// Nháy 10 lần
	//_IoLed.attach_ms(111,1,0); 		// luôn ON
	//_IoLed.attach_ms(111,0,1); 		// luôn OFF
}

void loop() {
  _IoLed.Blink();
  _IoBuzz.Blink();
}