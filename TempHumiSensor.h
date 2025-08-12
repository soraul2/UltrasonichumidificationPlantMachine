#include <DHT.h>

class TempHumiSensor {
public:
    TempHumiSensor(int dht_pin);
    
    void init();
    void readSensor(); // readSensor() 메서드 추가
    float getTemperature();
    float getHumidity();

private:
    int _dht_pin;       // dht_pin 멤버 변수 추가
    float _temperature; // int에서 float으로 변경
    float _humidity;    // int에서 float으로 변경
    DHT _dht;
};