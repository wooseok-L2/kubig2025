#include "esp_camera.h"
#include <WebServer.h>
#include <WiFi.h>

// CAMERA PIN 설정 (AI-Thinker ESP32-CAM 보드 기준)
#define PWDN_GPIO_NUM 32
#define RESET_GPIO_NUM -1
#define XCLK_GPIO_NUM 0
#define SIOD_GPIO_NUM 26
#define SIOC_GPIO_NUM 27

#define Y9_GPIO_NUM 35
#define Y8_GPIO_NUM 34
#define Y7_GPIO_NUM 39
#define Y6_GPIO_NUM 36
#define Y5_GPIO_NUM 21
#define Y4_GPIO_NUM 19
#define Y3_GPIO_NUM 18
#define Y2_GPIO_NUM 5
#define VSYNC_GPIO_NUM 25
#define HREF_GPIO_NUM 23
#define PCLK_GPIO_NUM 22

// WiFi 설정
const char *ssid = "turtle";
const char *password = "turtlebot3";

// 웹서버 포트
WebServer server(80);

// HTML 페이지
const char *INDEX_HTML = R"rawliteral(
<html>
  <head>
    <title>ESP32-CAM Stream</title>
  </head>
  <body>
    <h2>ESP32-CAM Live Stream</h2>
    <img src="/stream" />
  </body>
</html>
)rawliteral";

// HTML 페이지 응답
void handleRoot()
{
    server.send(200, "text/html", INDEX_HTML);
}

// MJPEG 스트리밍 응답
void handleStream()
{
    WiFiClient client = server.client();

    String response = "HTTP/1.1 200 OK\r\n";
    response += "Content-Type: multipart/x-mixed-replace; boundary=frame\r\n\r\n";
    server.sendContent(response);

    while (1)
    {
        camera_fb_t *fb = esp_camera_fb_get();
        if (!fb)
        {
            Serial.println("Camera capture failed");
            return;
        }

        response = "--frame\r\n";
        response += "Content-Type: image/jpeg\r\n\r\n";
        server.sendContent(response);
        server.sendContent((const char *)fb->buf, fb->len);
        server.sendContent("\r\n");

        esp_camera_fb_return(fb);

        if (!client.connected())
        {
            break;
        }

        delay(50); // 프레임 속도 조절
    }
}

void startCameraServer()
{
    server.on("/", handleRoot);
    server.on("/stream", HTTP_GET, handleStream);
    server.begin();
}

void setup()
{
    Serial.begin(115200);

    // 카메라 설정
    camera_config_t config;
    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;
    config.pin_d0 = Y2_GPIO_NUM;
    config.pin_d1 = Y3_GPIO_NUM;
    config.pin_d2 = Y4_GPIO_NUM;
    config.pin_d3 = Y5_GPIO_NUM;
    config.pin_d4 = Y6_GPIO_NUM;
    config.pin_d5 = Y7_GPIO_NUM;
    config.pin_d6 = Y8_GPIO_NUM;
    config.pin_d7 = Y9_GPIO_NUM;
    config.pin_xclk = XCLK_GPIO_NUM;
    config.pin_pclk = PCLK_GPIO_NUM;
    config.pin_vsync = VSYNC_GPIO_NUM;
    config.pin_href = HREF_GPIO_NUM;
    config.pin_sccb_sda = SIOD_GPIO_NUM;
    config.pin_sccb_scl = SIOC_GPIO_NUM;
    config.pin_pwdn = PWDN_GPIO_NUM;
    config.pin_reset = RESET_GPIO_NUM;
    config.xclk_freq_hz = 20000000;
    config.pixel_format = PIXFORMAT_JPEG;

    if (psramFound())
    {
        config.frame_size = FRAMESIZE_VGA;
        config.jpeg_quality = 10;
        config.fb_count = 2;
    }
    else
    {
        config.frame_size = FRAMESIZE_QVGA;
        config.jpeg_quality = 12;
        config.fb_count = 1;
    }
    config.frame_size = FRAMESIZE_QVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;

    // 카메라 초기화
    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK)
    {
        Serial.printf("Camera init failed with error 0x%x", err);
        return;
    }

    // WiFi 연결
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");

    Serial.print("Camera Stream Ready! Go to: http://");
    Serial.print("width, height, quality, and frame count");
    Serial.print(" : ");
    Serial.print(config.frame_size);
    Serial.print(", ");
    Serial.print(config.jpeg_quality);
    Serial.print(", ");
    Serial.print(config.fb_count);
    Serial.println(WiFi.localIP());

    startCameraServer();
}

void loop()
{
    server.handleClient();
}