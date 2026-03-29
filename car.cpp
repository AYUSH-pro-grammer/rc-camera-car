#include <Arduino.h>
#include "esp_camera.h"
#include <WiFi.h>
#include <WebServer.h>
WebServer server(80);

#define IN1 12 
#define IN2 13
#define IN3 14
#define IN4 15 

const char* ssid = "ACT_5505";
const char* password= "123455432";

#define CAMERA_MODEL_AI_THINKER 
#include "camera_pins.h"

String lastCmd = "";


void handleCapture(){
    camera_fb_t * fb = esp_camera_fb_get();

    if (!fb){
        server.send(500, "text/plain", "Camera Capture failed");
        return;
    }

    server.send_P(200, "image/jpeg",
    (const char *)fb -> buf, fb -> len);

    esp_camera_fb_return(fb);
}

void handleRoot(){
    server.send(200, "text/html", 
    "<h1> Eps32 cam car </h1>"
"<p>/control?cmd=forward</p>"
"<p>/capture</p>");
}

void handleControl(){


    String cmd = server.arg("cmd");

    if (cmd == lastCmd){
        return;
    }

    lastCmd = cmd;



    Serial.println(cmd);

    if (cmd == "forward") forward();
    else if (cmd == "back") back();
    else if (cmd == "left") left();
    else if (cmd == "right") right();
    else stopCar();

    server.send(200, "text/plain", "OK");
}

void forward(){
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

void stopCar(){
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}

void left(){
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
}

void right(){
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

void back(){
    
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
}

void setup(){
    Serial.begin(115200);

    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);

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

    config.pin_pwdn = PWDN_GPIO_NUM;
    config.pin_reset = RESET_GPIO_NUM;

    config.pin_sscb_sda = SIOD_GPIO_NUM;
    config.pin_sscb_scl = SIOC_GPIO_NUM;

    config.xclk_freq_hz = 20000000;
    config.pixel_format  = PIXFORMAT_JPEG;

    if (esp_camera_init(&config) != ESP_OK){
        Serial.println("Camera init failed");
        return;
    }

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED){
        delay(500);
        Serial.print(".");
    }

    Serial.println("\nConnected!");
    Serial.println(WiFi.localIP());


    server.on("/", handleRoot);
    server.on("/control", handleControl);
    server.on("/capture", handleCapture);
    server.begin();

    stopCar();
}

void loop(){

    if (WiFi.status() != WL_CONNECTED){
        stopCar();
    }

    


    server.handleClient();

    delay(1000)


}



