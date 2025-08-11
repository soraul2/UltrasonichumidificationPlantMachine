#ifndef RTCController_h
#define RTCController_h

#include "Arduino.h"
#include <ThreeWire.h>
#include <RtcDS1302.h>

class RTCController {
public: // <-- 이 부분이 꼭 필요합니다.
    // 생성자
    RTCController(int CLK, int DAT, int RST);

    // 공용 메서드들
    void begin();
    int getHour();
    int getMinute();
    int getSecond();

private:
    // 멤버 변수 선언 방식 수정
    ThreeWire myWire;
    RtcDS1302<ThreeWire> Rtc;
}; // <-- 클래스 정의 끝에 세미콜론이 필요합니다.

#endif // <-- #ifndef와 짝을 이루는 #endif도 잊지 마세요.