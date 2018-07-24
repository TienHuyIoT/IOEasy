#include "IOInput.h"
#include "TimeOutEvent.h"
TimeOutEvent _ToB(1000);
#define FACTORY_IO    0 //GPIO0
// Cài trạng thái khởi động là mức HIGH
// Cài thời gian lấy mẫu là 10ms, số lần lấy mẫu mức cao là 15(lần), số lần lấy mẫu mức thấp là 5(lần)
// ==> thời gian lấy mẫu mức cao là 10*15 = 150ms, mức thấp là 5*10 = 50ms
IOInput _IoB(FACTORY_IO,HIGH,10,15,5);
void setup() {
	Serial.begin(115200);
	// Có thể thay đổi các tham số qua các hàm sau
	// _IoB.set_status_init(HIGH);	// Cài trạng thái input lúc khởi động là mức HIGH
	// _IoB.set_high_cnt_ms(15);	//Cài số lần lấy mẫu mức cao
	// _IoB.set_low_cnt_ms(5);		//Cài số lần lấy mẫu mức thấp
	// _IoB.set_sample_ms(10);		//Cài thời gian lấy mẫu
}

/*
	Hàm đọc thời gian trạng thái input: 
	_IoB.GetTime(HIGH/LOW) sẽ trả về giá trị thời gian đến thời điểm hiện tại tính từ lúc xác nhận thay đổi input.
	Nếu đọc thời gian của trạng thái input khác trạng thái input hiện tại thì hàm sẽ trả về giá trị 0
	Ví dụ: Nếu trạng thái input là mức thấp, và thời gian mức thấp (LOW) đến thời điểm hiện tại là 2s
	Hàm _IoB.GetTime(LOW) sẽ trả về giá trị là 2s. Hàm _IoB.GetTime(HIGH) sẽ trả về giá trị là 0

	- Có thể thay đổi được thời gian trạng thái input để phục vụ cho 1 vài mục đích khác nhau
	Hàm _IoB.set_low_time_ms(10000); để gán thời gian mức thấp (LOW) hiện tại là 10s
	Hàm _IoB.set_high_time_ms(10000); để gán thời gian mức cao (HIGH) hiện tại là 10s
 	Ví dụ:
   // Nếu nút nhấn mức thấp 
   if (_IoB.GetStatus() == LOW)
   {
     // Lấy thời gian nhấn nút 
     uint32_t T = _IoB.GetTime(LOW);
     Nếu thời gian nút nhấn từ 2s - 10s
     if (T > 2000 && T < 10000)
     {
       // Cài thời gian nút nhấn mức thấp 10s để ko chạy lại điều kiện này 
       _IoB.set_low_time_ms(10000);
       //Code here
     }
   }
*/

void loop() {	
  	_IoB.loop();	//Hàm cập nhật trạng thái input, hàm này phải được chạy liên tục
	// Hết Timeout 1000ms thì kiểm tra trạng thái nút nhấn và in thời gian trạng thái nút nhất.
	// Mục đích tạo timeout để 1s in một lần. Nếu không sẽ in Serial liên tục khó nhìn.
	if(_ToB.ToEExpired()){
		// Update lại timeout 1000ms
		_ToB.ToEUpdate(1000);
		if(_IoB.GetStatus()==HIGH){
			Serial.print("INPUT HIGH: ");
			Serial.println(_IoB.GetTime(HIGH),DEC);
		}else{
			Serial.print("INPUT LOW");
			Serial.println(_IoB.GetTime(LOW),DEC);
		}
	}
}
