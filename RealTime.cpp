#include "RealTime.h"

RealTime::RealTime(int CLK, int DAT, int RST)
    : myWire(DAT, CLK, RST), Rtc(myWire) {
    // 생성자 본문은 비워두거나 필요한 초기화 코드를 추가합니다.
}

void RealTime::begin() {
    // Serial.begin()은 메인 스케치(setup())에서 호출하는 것을 권장합니다.
    Rtc.Begin(); 
    
    // 컴파일 시간을 기반으로 RtcDateTime 객체를 생성합니다.
    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);

    // RTC 모듈의 시간이 유효하지 않거나
    // 현재 RTC 시간이 컴파일 시간보다 이전이면 시간을 새로 설정합니다.
    // 이는 배터리 교체 등으로 RTC 시간이 초기화되었을 때 유용합니다.
    if (!Rtc.IsDateTimeValid() || Rtc.GetDateTime() < compiled) {
        // RTC 모듈에 컴파일 시간을 기준으로 시간 정보를 설정합니다.
        Rtc.SetDateTime(compiled);
    }
}
    
int RealTime::getHour() {
    return Rtc.GetDateTime().Hour();
}

int RealTime::getMinute() {
    return Rtc.GetDateTime().Minute();
}

int RealTime::getSecond() {
    return Rtc.GetDateTime().Second();
}