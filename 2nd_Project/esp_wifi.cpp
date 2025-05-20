#include <ESP8266WiFi.h>

const char* ssid = "turtle";
const char* password = "turtlebot3";
const char* m_serverIP = "192.168.0.54";  // TCP 서버 주소
const int serverPort = 5511;  // 서버 포트

WiFiClient client;  // TCP 클라이언트 객체 생성

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    
    Serial.println("\nWi-Fi 연결 성공!");
    Serial.print("할당된 IP 주소: ");
    Serial.println(WiFi.localIP());

    if (client.connect(m_serverIP, serverPort)) {  // 서버에 연결
        Serial.println("TCP 서버 연결 성공!");
    } else {
        Serial.println("TCP 서버 연결 실패...");
    }
}

void loop() {
    if (client.connected()) {
        // 데이터를 서버로 전송
        String message = "Hello from ESP8266!";
        client.print(message);
        Serial.println("서버로 데이터 전송 완료: " + message);

        // 서버에서 응답 받기
        while (client.available()) {
            String response = client.readStringUntil('\n');
            response.trim();  // 문자열 앞뒤 공백 제거
            Serial.println("서버 응답: " + response);
            response = "";  // 응답 데이터를 초기화하여 다음 루프에서 깨끗한 상태 유지

        }

        delay(1000);
    } else {
        Serial.println("서버 연결이 끊어졌습니다. 재연결 시도...");
        if (client.connect(m_serverIP, serverPort)) {
            Serial.println("TCP 서버 재연결 성공!");
        }
    }
}
