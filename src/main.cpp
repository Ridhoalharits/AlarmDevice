#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define buzzer 15

const char* ssid ="Dhior";
const char* password ="itsmedhior";

int data_Btn_1;
int data_Btn_2;
float data_Lat_1;
float data_Lat_2;
float data_Lon_1;
float data_Lon_2;

const unsigned long interval2 = 10000;    // 10 s interval to send message
const unsigned long interval1 = 20000;    // 10 s interval to send message
unsigned long previousMillis = 0;  // will store last time message sent

void setup() {
  Serial.begin(115200);
  pinMode(buzzer, OUTPUT);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();

  WiFi.begin(ssid,password);
  Serial.print("Connecting to WiFi");

  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
    }
    Serial.println("\nConnected to WiFi Network");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
}

void device_1_get(){
  if((WiFi.status() == WL_CONNECTED)){
    HTTPClient client;

//    client.begin("https://platform.antares.id:8443/~/antares-cse/antares-id/PanicButton-1/PanicButtonDevice-1/la");
//    client.addHeader("X-M2M-Origin", "b144ed255ea8dcd4:7cab148e0506e8d6");
//    client.addHeader("Content-Type", "application/json;ty=4");
//    client.addHeader("Accept", "application/json");
    client.begin("https://api.qubitro.com/v2/projects/b9aabf51-edf2-4885-b211-8a424cb55208/devices/f7566774-46ea-4b09-bb19-63fd19699594/data?page=1&limit=1&range=all");
    client.addHeader("Accept", "application/json");
    client.addHeader("Authorization", "Bearer QB_BzKTp5dhQP3--u1T9q1MYcpYJTO4reb4IY81Qax-");
    int httpCode=client.GET();

    if(httpCode > 0){
      String payload=client.getString();
      Serial.println(payload);


      //QUBITRO

      StaticJsonDocument<384> doc;
      
      DeserializationError error = deserializeJson(doc, payload);
      
      if (error) {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.c_str());
        return;
      }
      
      JsonObject response_0 = doc["data"][0]["data"];
      data_Btn_1 = response_0["Btn"]; // 1
      data_Lat_1 = response_0["Lat"];
      data_Lon_1 = response_0["Lon"];
      Serial.print("Button State (dev1): ");
      Serial.println(String(data_Btn_1));
      Serial.println("----------------\n");
      }
      
//-------------------------------------------
            //ANTARES
//      StaticJsonDocument<768> doc;
//
//      DeserializationError error = deserializeJson(doc, payload);
//      
//      if (error) {
//        Serial.print("deserializeJson()_1 failed: ");
//        Serial.println(error.c_str());
//        return;
//      }
//
//      JsonObject m2m_cin = doc["m2m:cin"];
//      const char* m2m_cin_con = m2m_cin["con"];
//      //Serial.println(String(m2m_cin_con) + "\n");
//
//      //http req antares
//      StaticJsonDocument<768> doc2;
//
//      DeserializationError error_2 = deserializeJson(doc2, m2m_cin_con);
//      
//      if (error_2) {
//        Serial.print("deserializeJson()_2 failed: ");
//        Serial.println(error.c_str());
//        return;
//      }
//
//      JsonObject data = doc2["data"];
//      data_Btn_1 = data["Btn"];
//      Serial.print("Button State : ");
//      Serial.println(String(data_Btn_1));
//      Serial.println("----------------\n");

//-------------------------------------------

    else{
      Serial.println("Error on HTTP request");
      }
      client.end();
    }

  else{
    Serial.println("Connection Lost");
    }
}

void device_2_get(){
  if((WiFi.status() == WL_CONNECTED)){
    HTTPClient client;

//    client.begin("https://platform.antares.id:8443/~/antares-cse/antares-id/PanicButton-1/PanicButtonDevice-2/la");
//    client.addHeader("X-M2M-Origin", "b144ed255ea8dcd4:7cab148e0506e8d6");
//    client.addHeader("Content-Type", "application/json;ty=4");
//    client.addHeader("Accept", "application/json");
    client.begin("https://api.qubitro.com/v2/projects/b9aabf51-edf2-4885-b211-8a424cb55208/devices/f7566774-46ea-4b09-bb19-63fd19699594/data?page=1&limit=1&range=all");
    client.addHeader("Accept", "application/json");
    client.addHeader("Authorization", "Bearer QB_BzKTp5dhQP3--u1T9q1MYcpYJTO4reb4IY81Qax-");
    int httpCode=client.GET();

     if(httpCode > 0){
      String payload=client.getString();
      Serial.println(payload);

      //QUBITRO

      StaticJsonDocument<384> doc;
      
      DeserializationError error = deserializeJson(doc, payload);
      
      if (error) {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.c_str());
        return;
      }
      
      JsonObject response_0 = doc["data"][0]["data"];
      data_Btn_2 = response_0["Btn"]; // 1
      data_Lat_2 = response_0["Lat"];
      data_Lon_2 = response_0["Lon"];
      Serial.print("Button State (dev2): ");
      Serial.println(String(data_Btn_2));
      Serial.println("----------------\n");
     }
     
//-------------------------------------------
      //ANTARES
//      StaticJsonDocument<768> doc;
//
//      DeserializationError error = deserializeJson(doc, payload);
//      
//      if (error) {
//        Serial.print("deserializeJson()_1 failed: ");
//        Serial.println(error.c_str());
//        return;
//      }
//
//      JsonObject m2m_cin = doc["m2m:cin"];
//      const char* m2m_cin_con = m2m_cin["con"];
//      //Serial.println(String(m2m_cin_con) + "\n");
//
//      //http req antares
//      StaticJsonDocument<768> doc2;
//
//      DeserializationError error_2 = deserializeJson(doc2, m2m_cin_con);
//      
//      if (error_2) {
//        Serial.print("deserializeJson()_2 failed: ");
//        Serial.println(error.c_str());
//        return;
//      }
//
//      JsonObject data = doc2["data"];
//      data_Btn_2 = data["Btn"];
//      Serial.print("Button State : ");
//      Serial.println(String(data_Btn_2));
//      Serial.println("----------------\n");
//-------------------------------------------
     
    else{
      Serial.println("Error on HTTP request");
      }
      client.end();
    }

  else{
    Serial.println("Connection Lost");
    }
}

void device_1_post(){
  const char* serverName = "https://ap2.loriot.io/1/rest";
  unsigned long lastTime = 0;
  unsigned long timerDelay = 5000;
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      HTTPClient https;
      
      // Your Domain name with URL path or IP address with path
      https.begin(serverName);
      
      // If you need an HTTP request with a content type: application/json, use the following:
      https.addHeader("Authorization", "Bearer vnoG0wAAAA1hcDEubG9yaW90LmlvoO2eQixfYSe3BqfgoW_S4g==");
      https.addHeader("Content-Type", "application/json");
     
      int httpResponseCode = https.POST("{\"cmd\": \"tx\",\"EUI\": \"F10E517FB7CD7A20\",\"port\": 32,\"confirmed\": false,\"data\": \"31\",\"appid\": \"BE7A06D3\",\"priority\": 3}");

      Serial.print("HTTP Response code (Loriot_dev1): ");
      Serial.println(httpResponseCode);
        
      https.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
  Serial.println("----------------\n");
    
}

void device_2_post(){
  const char* serverName = "https://ap2a.loriot.io/1/rest";
  unsigned long lastTime = 0;
  unsigned long timerDelay = 5000;
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      HTTPClient https;
      
      // Your Domain name with URL path or IP address with path
      https.begin(serverName);
      
      // If you need an HTTP request with a content type: application/json, use the following:
      https.addHeader("Authorization", "Bearer vnoG0wAAAA1hcDEubG9yaW90LmlvoO2eQixfYSe3BqfgoW_S4g==");
      https.addHeader("Content-Type", "application/json");
     
      int httpResponseCode = https.POST("{\"cmd\": \"tx\",\"EUI\": \"F10E517FB7CD7A21\",\"port\": 33,\"confirmed\": false,\"data\": \"31\",\"appid\": \"BE7A06D3\",\"priority\": 3}");

      Serial.print("HTTP Response code (Loriot_dev2): ");
      Serial.println(httpResponseCode);
        
      https.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
  Serial.println("----------------\n");
    
}

void loop_read_data(){
  //http get
  device_1_get();
  device_2_get();

  //kondisional oled and buzzer
      if(String(data_Btn_1)=="1" && String(data_Btn_2)=="1"){
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0, 10);
        display.println("Device 1: TIDAK AMAN!");
        display.setCursor(0, 20);
        display.println("Device 2: TIDAK AMAN!");
        display.display();
        display.clearDisplay();
        digitalWrite(buzzer, HIGH);
        delay(2000);
        digitalWrite(buzzer, LOW);
        delay(1000);
      }
      
      else if(String(data_Btn_1)=="1" && String(data_Btn_2)=="0"){
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0, 10);
        display.println("Device 1: TIDAK AMAN!");
        display.setCursor(0, 20);
        display.println("Device 2: AMAN!");
        display.display();
        display.clearDisplay();
        digitalWrite(buzzer, HIGH);
        delay(2000);
        digitalWrite(buzzer, LOW);
        delay(1000);
      } 
      
      else if (String(data_Btn_1)=="0" && String(data_Btn_2)=="1"){
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0, 10);
        display.println("Device 1: AMAN!");
        display.setCursor(0, 20);
        display.println("Device 2: TIDAK AMAN!");
        display.display();
        display.clearDisplay();
        digitalWrite(buzzer, HIGH);
        delay(2000);
        digitalWrite(buzzer, LOW);
        delay(1000);
      }
       
      else if (String(data_Btn_1)=="0" && String(data_Btn_2)=="0"){
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0, 10);
        display.println("Device 1: AMAN!");
        display.setCursor(0, 20);
        display.println("Device 2: AMAN!");
        display.display();
        display.clearDisplay();
      }
}

void loop_read_data_2(){
  //http get
  device_1_get();

  //kondisional oled and buzzer
      if(String(data_Btn_1)=="1"){
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0, 10);
        display.println("Device 1: TIDAK AMAN!");
        display.display();
        display.clearDisplay();
        digitalWrite(buzzer, HIGH);
        delay(2000);
        digitalWrite(buzzer, LOW);
        delay(1000);
      }
       
      else if (String(data_Btn_1)=="0"){
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0, 10);
        display.println("Device 1: AMAN!");
        display.display();
        display.clearDisplay();
      }
}

void loop(){
//  loop_read_data_2();
//  unsigned long currentMillis1 = millis();
//  if (currentMillis1 - previousMillis > interval2) {
//    previousMillis = currentMillis1;
//    device_1_post();
//    device_1_post_db();
//  }
  loop_read_data();  
      
  unsigned long currentMillis1 = millis();
  if (currentMillis1 - previousMillis > interval1) {
    previousMillis = currentMillis1;
    unsigned long currentMillis2 = millis();
    while (currentMillis2 - previousMillis < interval2) {
      // Get the current time for action2
      currentMillis2 = millis();
      loop_read_data();
    }
 
  }
}