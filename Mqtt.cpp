
#include <WiFi.h>
#include <PubSubClient.h>
const char* ssid = "";
const char* password = "";

//MQTT 브로커 설정
// 라즈베리파이의 IP 주소를 입력하세요
const char* mqtt_server = "";
const int mqtt_port = 1883;
const char* mqtt_user = "";  //사용자명이 필요없는 경우 비워둠

const char* mqtt_password = "";  //비밀번호가 필요없는 경우 비워둔다.

//MQTT 토픽 설정
const char* out_topic = "arduino/sensor";


public:
MQTT::MQTT(String MQTT_USER, String MQTT_PASSWORD, String MQTT_PORT, String MQTT_SERVER, String SSID, String PASSWORD, String out_topic)
  : _MQTT_USER(MQTT_USER), _MQTT_PASSWORD(MQTT_PASSWORD), _MQTT_PORT(MQTT_PORT), _MQTT_SERVER(MQTT_SERVER), _SSID(SSID), _PASSWORD(PASSWORD),
    _out_topic(out_topic) {
}

MQTT::setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connection to");
  Serial.println(_SSID);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conncted");
  Serial.println("IP Address : ");
  Serial.println(WiFi.localIP());
}

private:
WiFiClient espClient;
PubSubClient client(espClient);


long lastMsg = 0;
char msg[50];
int value = 0;

void setup_wifi() {

  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conncted");
  Serial.println("IP Address : ");
  Serial.println(WiFi.localIP());
}

//MQTT 브로커에 재접속하는 함수
void reconnect() {
  while (!client.connected()) {
    Serial.print("Attemping MQTT connection...");
    //클라이언트 ID를 무작위로 생성하여 충돌 방지
    String clientId = "ESP32Client-";
    StringId += String(random(0xffff), HEX);

    //MQTT 서버에 연결 시도
    if (client.connect(clientId.c_str(), mqtt_user, mqtt_password)) {
      Serial.println("connected");
    } else {
      Serial.print("failed,rc=");
      Serial.print(client.state());
      Serial.println("try again in 5 esconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  //wifi 연결
  setup_wifi();

  //브로커와 연결
  client.setServer(mqtt_server, mqtt_port);
  // MQTT 메시지 수신 시 처리하는 콜백 함수 설정 ( 이 예제에서는 사용하지 않는다);
  //client.setCallback(callback);
}

void loop() {
  //MQTT 연결 상태 확인 및 재접속
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  //5초마다 메시지 발행
  if (now - lastMsg > 5000) {
    lastMsg = now;

    //예제 데이터 생성 (온도 센서 데이터라고 가정) 실제 센서를 연결하여 값을 읽어오면 됨
    value = random(20, 30);

    //메시지 문자열 생성
    snprintf(msg, 50, "sensor data : %d", value);
    Serial.print("Publish message: ");
    Serial.println(msg);

    //메시지 발행 (토픽 , 메시지 , 유지 여부);
    client.publish(out_topic, msg);
  }
}

