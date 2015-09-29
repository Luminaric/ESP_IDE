#include <DHT.h>
#include "Timer.h"
#include "ESP8266.h"
#include<SPI.h>
#include "ethernetSettings.h"

#define TEN_MINUTE          600000

//Setup Sensor Interface
float temp, humidity;
//long previousMillis = 0, previousMillisHour = 0, currentMillis = 0;
String getString, getIOTString, sensorID;

void setup() {
  Serial.begin(9600);
  wifiConnect();

}

void loop() {
  uint8_t buffer[128] ={0};
  if(wifi.createTCP(HOST_NAME, HOST_PORT))  {
    Serial.println("Created TCP connection");
  } else  {
    Serial.println("TCP connection failed");
  }
  char *hello = "GET /a/add2.php?sensorID=ESP8266WiFi&t=98.2&h=99.9&p=1030.0\r\n\r\n";
  wifi.send((const uint8_t*)hello, strlen(hello));
  
  uint32_t len = wifi.recv(buffer, sizeof(buffer), 10000);
  if (len > 0) {
      Serial.print("Received:[");
      for(uint32_t i = 0; i < len; i++) {
          Serial.print((char)buffer[i]);
      }
      Serial.print("]\r\n");
  }
  delay(12000);
}
void wifiConnect(void){
  Serial.println("Setup begin");

  Serial.print("FW Version: ");
  Serial.println(wifi.getVersion().c_str());
  
  
  if (wifi.setOprToStation()) {
      Serial.println("to station ok");
  } else {
      Serial.println("to station err");
  }

  if (wifi.joinAP(SSID, PASSWORD)) {
      Serial.println("Join AP success");
      Serial.print("IP: ");       
      Serial.println(wifi.getLocalIP().c_str());
  } else {
      Serial.println("Join AP failure");
  }
  
  Serial.println("Setup complete");
}

void sendString(){}

