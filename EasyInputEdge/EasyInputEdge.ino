#include "IOInput.h"
#define FACTORY_IO    0 //GPIO0
// Cài trạng thái khởi động là mức HIGH
// Cài thời gian lấy mẫu là 10ms, số lần lấy mẫu mức cao là 15(lần), số lần lấy mẫu mức thấp là 5(lần)
// ==> thời gian lấy mẫu mức cao là 10*15 = 150ms, mức thấp là 5*10 = 50ms
IOInput _IoB(FACTORY_IO,HIGH,10,15,5);
void setup() {
	Serial.begin(115200);
}

void loop() {	
  	_IoB.loop();	//Hàm cập nhật trạng thái input, hàm này phải được chạy liên tục
	if(_IoB.GetEdge(FALLING)){
		Serial.println("FALLING");
	}
	if(_IoB.GetEdge(RISING)){
		Serial.println("RISING");
	}	
}
