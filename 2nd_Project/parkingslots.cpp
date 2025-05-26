// platformio 

#include <ESP8266WiFi.h>
#include <Arduino.h>

#define TRIG D6
#define ECHO D5
#define RED  D1
#define GREEN D2

bool previousRedState = LOW;
bool previousGreenState = HIGH;

const char* ssid = "turtle";
const char* password = "turtlebot3";
const char* m_serverIP = "192.168.0.54";  // TCP 서버 주소
const int serverPort = 5511;  // 서버 포트

WiFiClient client;

void connectWiFi() {
    Serial.print("WiFi 연결 중...");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWi-Fi 연결 성공!");
    Serial.print("할당된 IP 주소: ");
    Serial.println(WiFi.localIP());
}

void sendData(String message) {
    if (!client.connected()) {
        Serial.println("TCP 서버 연결 시도...");
        if (!client.connect(m_serverIP, serverPort)) {
            Serial.println("TCP 서버 연결 실패...");
            return;
        }
        Serial.println("TCP 서버 연결 성공!");
    }

    Serial.println("데이터 전송 중...");
    client.print(message);
    client.flush();  // 데이터가 완전히 전송되도록 보장
    Serial.println("서버로 데이터 전송 완료: " + message);

    // 서버 응답 확인
    while (client.available()) {
        String response = client.readStringUntil('\n');
        response.trim();
        Serial.println("서버 응답: " + response);
    }
}

void setup() {
    Serial.begin(9600);
    connectWiFi();

    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);
    pinMode(RED, OUTPUT);
    pinMode(GREEN, OUTPUT);

    digitalWrite(RED, LOW);
    digitalWrite(GREEN, HIGH); // 기본 상태 녹색
}

void loop() {
    long duration;
    float distance;

    // 초음파 펄스 발생
    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);

    // // error check
    // duration = pulseIn(ECHO, HIGH, 30000);
    // if (duration == 0) {
    //     Serial.println("초음파 센서 오류: 반응 없음");
    //     return;
    // }

    // ECHO 핀에서 HIGH가 유지된 시간 측정
    duration = pulseIn(ECHO, HIGH);
    distance = duration / 58.0;

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    bool currentRedState, currentGreenState;

    // 거리 판단
    if (distance < 10.0) {
        Serial.println("detect");
        currentRedState = HIGH;
        currentGreenState = LOW;
    } else {
        currentRedState = LOW;
        currentGreenState = HIGH;
    }

    if (currentRedState != previousRedState || currentGreenState != previousGreenState) {
        previousRedState = currentRedState;
        previousGreenState = currentGreenState;

        digitalWrite(RED, currentRedState);
        digitalWrite(GREEN, currentGreenState);

        if (currentRedState == HIGH) {
            sendData("UPDATE parking_slots SET status = 'Occupied', entry_time = NOW(), exit_time = NULL WHERE slot_number = 'A1';");
        } else {
            sendData("UPDATE parking_slots SET status = 'Empty', exit_time = NOW() WHERE slot_number = 'A1';");
        }
    }


    // WiFi 연결 확인 및 재연결
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("WiFi 연결 끊김! 재연결 시도...");
        connectWiFi();
    }

    delay(1000);
}