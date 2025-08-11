#include "RTCController.h"

RTCController::RTCController(int CLK, int DAT, int RST)
    : myWire(DAT, CLK, RST), Rtc(myWire) {
    // 생성자 본문은 비워두거나 필요한 초기화 코드를 추가합니다.
}

void RTCController::begin() {
    // Serial.begin()은 메인 스케치(setup())에서 호출하는 것을 권장합니다.
    Rtc.Begin(); // <-- Rtc.Begin()으로 수정

}
    
    // 컴파일 시간을 기반으로 'compiled' 객체 선언

    //초기 시간을 세팅하는 코드

//     RtcDateTime compiled = RtcDateTime(2025,8,11,9,19,0);

//     if (!Rtc.IsDateTimeValid()) {
//         Serial.println("RTC의 시간이 유효하지 않습니다!");
//         Rtc.SetDateTime(compiled);
//     }

//     if (Rtc.GetIsWriteProtected()) {
//         Serial.println("RTC가 쓰기 방지되어 있습니다. 쓰기 기능을 활성화합니다.");
//         Rtc.SetIsWriteProtected(false);
//     }

//     if (!Rtc.GetIsRunning()) {
//         Serial.println("RTC가 작동하지 않고 있습니다. 지금 시작합니다.");
//         Rtc.SetIsRunning(true);
//     }

//     RtcDateTime now = Rtc.GetDateTime();
//     if (now < compiled) {
//         Serial.println("RTC 시간이 컴파일 시간보다 이전입니다! (업데이트)");
//         Rtc.SetDateTime(compiled);
//     } else if (now > compiled) {
//         Serial.println("RTC 시간이 컴파일 시간보다 최신입니다. (정상)");
//     } else if (now == compiled) {
//         Serial.println("RTC 시간이 컴파일 시간과 동일합니다! (정상)");
//     }
// }

int RTCController::getHour() {
    return Rtc.GetDateTime().Hour(); // <-- GetDateTime()으로 수정
}

int RTCController::getMinute() {
    return Rtc.GetDateTime().Minute(); // <-- GetDateTime()으로 수정
}

int RTCController::getSecond() {
    return Rtc.GetDateTime().Second(); // <-- GetDateTime()으로 수정
}