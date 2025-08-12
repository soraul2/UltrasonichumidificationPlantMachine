#include <WiFi.h>
#include <PubSubClient.h>
const char* ssid = "";
const char* password = "";

//MQTT 브로커 설정
// 라즈베리파이의 IP 주소를 입력하세요
const char* mqtt_server = "";
const int mqtt_port = 1883;
const char* mqtt_user = ""; //사용자명이 필요없는 경우 비워둠

const char* mqtt_password = ""; //비밀번호가 필요없는 경우 비워둔다.

//MQTT 토픽 설정
const char* out_topic = "arduino/sensor";

WiFiClient espClient;
PubSubClient client(espClient);


class MQTT{

  public :

    void setup_wifi();
    void reconnect();
    void setup();


  private :
    String _MQTT_USER;
    String _MQTT_PASSWORD;
    String _MQTT_PORT;
    String _MQTT_SERVER;
    String _SSID;
    String _PASSWORD;
    String _out_topic;
    WiFiClient _espClient;
    PubSubClient _client;

}


