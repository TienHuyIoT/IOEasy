/*
#include "IOInput.h"
#include "TimeOutEvent.h"
TimeOutEvent _ToB(1000);
#define FACTORY_IO    0 //GPIO0
// Cài trạng thái khởi động là mức HIGH
// Cài thời gian lấy mẫu là 10ms, số lần lấy mẫu mức cao là 15(lần), số lần lấy mẫu mức thấp là 5(lần)
// ==> thời gian lấy mẫu mức cao là 10*15 = 150ms, mức thấp là 5*10 = 50ms
IOInput _IoB(FACTORY_IO,HIGH,10,15,5);
void setup() {
	// Có thể thay đổi các tham số qua các hàm sau
  // _IoB.set_status_init(HIGH);	// Cài trạng thái input lúc khởi động là mức HIGH
	// _IoB.set_high_cnt_ms(15);	//Cài số lần lấy mẫu mức cao
	// _IoB.set_low_cnt_ms(5);		//Cài số lần lấy mẫu mức thấp
	// _IoB.set_sample_ms(10);		//Cài thời gian lấy mẫu
}

//	Hàm đọc thời gian trạng thái input: 
//	_IoB.GetTime(HIGH/LOW) sẽ trả về giá trị thời gian đến thời điểm hiện tại tính từ lúc xác nhận thay đổi input.
//	Nếu đọc thời gian của trạng thái input khác trạng thái input hiện tại thì hàm sẽ trả về giá trị 0
//	Ví dụ: Nếu trạng thái input là mức thấp, và thời gian mức thấp (LOW) đến thời điểm hiện tại là 2s
//	Hàm _IoB.GetTime(LOW) sẽ trả về giá trị là 2s. Hàm _IoB.GetTime(HIGH) sẽ trả về giá trị là 0

//	- Có thể thay đổi được thời gian trạng thái input để phục vụ cho 1 vài mục đích khác nhau
//	Hàm _IoB.set_low_time_ms(10000); để gán thời gian mức thấp (LOW) hiện tại là 10s
//	Hàm _IoB.set_high_time_ms(10000); để gán thời gian mức cao (HIGH) hiện tại là 10s
// 	Ví dụ:
//   // Nếu nút nhấn mức thấp 
//   if (_IoB.GetStatus() == LOW)
//   {
//     // Lấy thời gian nhấn nút 
//     uint32_t T = _IoB.GetTime(LOW);
//     Nếu thời gian nút nhấn từ 2s - 10s
//     if (T > 2000 && T < 10000)
//     {
//       // Cài thời gian nút nhấn mức thấp 10s để ko chạy lại điều kiện này 
//       _IoB.set_low_time_ms(10000);
//       //Code here
//     }
//   }

void loop() {
	Serial.begin(115200);
  	_IoB.loop();	//Hàm cập nhật trạng thái input, hàm này phải được chạy liên tục
	// Hết Timeout 1000ms thì kiểm tra trạng thái nút nhấn
	if(Toe1.ToEExpired()){
		// Update lại timeout 1000ms
		Toe1.ToEUpdate(1000);
		if(_IoB.GetStatus()==HIGH){
			Serial.println("INPUT HIGH: ");
			Serial.println(_IoB.GetTime(HIGH),DEC);
		}else{
			Serial.println("INPUT LOW");
			Serial.println(_IoB.GetTime(LOW),DEC);
		}
	}
}

*/

#ifndef _IOInput_H
#define _IOInput_H
#include <Arduino.h>
#include <stdint.h>
#include <stddef.h>
#include "TimeOutEvent.h"

class IOInput
{
  public:
	IOInput(short _IO = 0, uint8_t Lever = HIGH, uint16_t S_To = 10, uint16_t H_Cnt = 10, uint16_t L_Cnt = 10);
	void loop(void);
	uint32_t GetTime(uint8_t);
	uint8_t GetStatus(void);
	void set_high_cnt_ms(uint16_t);
	void set_low_cnt_ms(uint16_t);
	void set_sample_ms(uint16_t);
	void set_status_init(uint8_t);
	void set_low_time_ms(uint32_t Low);
	void set_high_time_ms(uint32_t High);

  protected:	
	uint32_t HighTime = 0;
	uint32_t LowTime = 0;
	uint16_t HighCount = 0;
	uint16_t LowCount = 0;
	uint16_t SampleHigh = 10;
	uint16_t SampleLow = 10;
	uint16_t SampleTo = 10;		
	uint8_t flagInput = HIGH;
	const short _IOPIN;
	TimeOutEvent ToE;
};
#endif
