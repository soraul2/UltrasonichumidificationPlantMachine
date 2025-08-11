#ifndef WaterSensor_h
#define WaterSensor_h

class WaterSensor {

public:
    // 생성자: 핀 번호를 받아 멤버 변수를 초기화합니다.
    WaterSensor(int waterSensor_pin);
    

    // 아날로그 값을 읽어 정수형으로 반환하는 함수 (const 키워드 추가)
    int getValue() const;

private:
    int _waterSensor_pin;
};

#endif