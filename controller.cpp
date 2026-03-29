#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "ACT_5505";
const char* password = "123455432";

String carIP = "192.188.0.1"; // i'll update this latter

#define VRX 34
#define VRY 35 

int xVal = 0;
int yVal = 0;


// functions

String getCommand(int x, int y){
    if (x > 1500 && x < 2500 && y > 1500 && y < 2500){
        return "stop";
    }

    if (y > 3000){
        return "forward";
    };

    if (y < 1000){return "back";};
    if (x > 3000){return "right";};
    if (x < 1000){return "left";};

    return "stop";

}

// i'll send cmd from here
void sendCommand(String cmd){
    HTTPClient http;
    String url = "http://" + carIP + "/control?cmd=" + cmd;

    http.begin(url);
    int httpCode = http.GET();

    Serial.print("cmd...");
    Serial.print(cmd);

    Serial.print(" | Response: ");
    Serial.println(httpCode);
    http.end();
}


void setup(){
    Serial.begin(115200);
    Serial.println("ESP32 working");

    pinMode(VRX, INPUT);
    pinMode(VRY, INPUT);

    Serial.println("connection to wifi");
    WiFi.begin(ssid, password);

    while (WiFi.status () != WL_CONNECTED){
        delay(500);
        Serial.print(".");

    };

    Serial.println("\nn Connected!");
    Serial.println(WiFi.localIP());

}

void loop(){


    xVal = analogRead(VRX);
    yVal = analogRead(VRY);

    Serial.print(xVal + ",");
    Serial.println(yVal);
    String command = getCommand(xVal, yVal);
    sendCommand(command);
    delay(1000);



}
