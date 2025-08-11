#ifndef Enviroment_h
#define Enviroment_h

#include "Arduino.h"
#include <TimeLib.h>  // 시간 관련 라이브러리

class Enviroment {
public:
    // 생성자: 온도, 습도, ON/OFF 시간, 그리고 min/max 범위를 모두 받도록 수정
    Enviroment(float tempMin, float tempMax, float humidMin, float humidMax, int onHour, int offHour)
      : _tempMin(tempMin), _tempMax(tempMax),
        _humidMin(humidMin), _humidMax(humidMax),
        _onHour(onHour), _offHour(offHour)
    {
    }


    float getTempMin() const {
      return _tempMin;
    }
    float getTempMax() const {
      return _tempMax;
    }
    float getHumidMin() const {
      return _humidMin;
    }
    float getHumidMax() const {
      return _humidMax;
    }


    int getOnHour() const {
      return _onHour;
    }
    int getOffHour() const {
      return _offHour;
    }

private:

    float _tempMin;
    float _tempMax;
    float _humidMin;
    float _humidMax;

    // 기존 멤버 변수들
    int _onHour;
    int _offHour;
};

#endif