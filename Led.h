#include "RealTime.h"
#include "Enviroment.h" // Enviroment 클래스 정의를 위해 추가

class Led {

public:
    Led(Enviroment* enviroment, int LED_pin, int CLK, int DAT, int RST)
        : _enviroment(enviroment), _LED_pin(LED_pin), _rtc(CLK, DAT, RST) {
        
        pinMode(_LED_pin, OUTPUT);
        _rtc.begin();
    }

    void control() {
        // boolean 변수를 선언하고 초기값을 false로 설정
        bool shouldBeOn = false;
        Serial.print("시 :");
        Serial.print(_rtc.getHour());
        Serial.print("  분 :");
        Serial.print(_rtc.getMinute());
        Serial.print("  초 :");
        Serial.print(_rtc.getSecond());
        Serial.println(" ");
        // 멤버 변수 이름(_rtc, _enviroment)을 정확하게 사용
        int currentHour = _rtc.getHour();
        int startHour = _enviroment->getOnHour();
        int endHour = _enviroment->getOffHour();

        // 조건문의 문법을 올바르게 수정
        if (startHour <= endHour) {
            // ON/OFF 시간이 같은 날에 있을 경우
            if (currentHour >= startHour && currentHour < endHour) {
                shouldBeOn = true;
            }
        } else {
            // ON/OFF 시간이 날짜를 넘어갈 경우 (예: 22시 ON ~ 다음날 6시 OFF)
            if (currentHour >= startHour || currentHour < endHour) {
                shouldBeOn = true;
            }
        }

        if (shouldBeOn) {
            Serial.println("LED ON");
            LED_turnOn();
        } else {
            Serial.println("LED OFF");
            LED_turnOff();
        }
    }

    void LED_turnOn() {
        digitalWrite(_LED_pin, HIGH);
    }

    void LED_turnOff() {
        digitalWrite(_LED_pin, LOW);
    }

private:
    Enviroment* _enviroment;
    int _LED_pin;
    
    RealTime _rtc;
};