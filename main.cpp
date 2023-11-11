
#include <PubSubClient.h>
#include <WiFiNINA.h>

const char* ssid = "gęsi pipek";
const char* password = "Rakowicka@2021";
const char* mqttServer = "192.168.0.24";
const int mqttPort = 1883;
const char* mqttTopic = "led/control";
const char* mqttButtonTopic = "button/pressed";
const char* mqttButtonCountTopic1 = "/once";
const char* mqttButtonCountTopic2 = "/double";
const char* mqttConnected = "connected/true";
const char* mqttClientID = "arduino-client";
const char* mqttAnalogRead = "analog/read";
const char* mqtt_username = "admin";
const char* mqtt_password = "LVProject11";

const char* mqttButtonnumber1 = "/1";
const char* mqttButtonnumber2 = "/2";

bool doubleClickEnable = true;

// set PushButton pin number
const int buttonPin = 2;
const int buttonPin2 = 4;

int buttonState;

unsigned long timePress = 0;
unsigned long timePressLimit = 0;
int clicks = 0;

int buttonState2;

unsigned long timePress2 = 0;
unsigned long timePressLimit2 = 0;
int clicks2 = 0;

int initialValue = 0;
int lastAnalogVal = 0;


WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

void setup() {
  // put your setup code here, to run once:
  
  // initialize the LED pin as an output:
  pinMode(buttonPin ,INPUT);
  pinMode(buttonPin2 ,INPUT);
  
  Serial.begin(9600);
  setupWiFi();
  mqttClient.setServer(mqttServer, mqttPort);
  mqttClient.setCallback(handleMqttMessage);
  reconnect();
}

void loop() {
  if (!mqttClient.connected()) {
    reconnect();
  }

  mqttClient.loop();

    // Read the potentiometer value
  int potValue = analogRead(A1);

  // Adjust the initial value based on the potentiometer reading
  int adjustedValue = initialValue + map(potValue, 0, 1023, -10, 10);
  // The adjusted value can be used in your MQTT messages or other logic

  if (mqttClient.connected()) {
    String fullTopic = String(mqttAnalogRead);
    mqttClient.publish(fullTopic.c_str(), String(adjustedValue).c_str());

  }

  
  buttonState = digitalRead(buttonPin);
  
  if (buttonState == HIGH){
    delay(200);
    //Serial.println("Button Pressed");
    
    if (clicks == 0) {
    timePress = millis();
      if(doubleClickEnable){
        timePressLimit = timePress + 400;
      }    
      else{
        timePressLimit = timePress ;
      }
    clicks = 1;
    }

    else if (clicks == 1 && millis() < timePressLimit){
      Serial.println("Button Pressed twice");
      if (mqttClient.connected()) {
        String fullTopic2 = String(mqttButtonTopic) + mqttButtonCountTopic2 + mqttButtonnumber1;
        mqttClient.publish(fullTopic2.c_str(), "PRESSED_DOUBLE_1");
      }

     //set variables back to 0
      timePress = 0;
      timePressLimit = 0;
      clicks = 0;      
    }    
  }

  if (clicks == 1 && timePressLimit != 0 && millis() > timePressLimit){
     Serial.println("Button Pressed Once");
      if (mqttClient.connected()) {
        String fullTopic2 = String(mqttButtonTopic) + mqttButtonCountTopic1 + mqttButtonnumber1;
        mqttClient.publish(fullTopic2.c_str(), "PRESSED_ONCE_1");
      }
     timePress = 0;
     timePressLimit = 0;
     clicks = 0;

  }
    buttonState2 = digitalRead(buttonPin2);

  if (buttonState2 == HIGH) {
    delay(200);

    if (clicks2 == 0) {
      timePress2 = millis();
      if(doubleClickEnable){
        timePressLimit = timePress + 400;
      }    
      else{
        timePressLimit = timePress ;
      }
      clicks2 = 1;
    } else if (clicks2 == 1 && millis() < timePressLimit2) {
      Serial.println("Button 2 Pressed twice");
      if (mqttClient.connected()) {
        String fullTopic2 = String(mqttButtonTopic) + mqttButtonCountTopic2 + mqttButtonnumber2;
        mqttClient.publish(fullTopic2.c_str(), "PRESSED_DOUBLE_2");
      }

      timePress2 = 0;
      timePressLimit2 = 0;
      clicks2 = 0;
    }
  }

  if (clicks2 == 1 && timePressLimit2 != 0 && millis() > timePressLimit2) {
    Serial.println("Button 2 Pressed Once");
    if (mqttClient.connected()) {
      String fullTopic2 = String(mqttButtonTopic) + mqttButtonCountTopic1 + mqttButtonnumber2;
      mqttClient.publish(fullTopic2.c_str(), "PRESSED_ONCE_2");
    }
    timePress2 = 0;
    timePressLimit2 = 0;
    clicks2 = 0;
  } 
}
void setupWiFi() {
  delay(10);
  Serial.print("Connecting to WiFi ");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, password);
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}

void reconnect() {
  while (!mqttClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (mqttClient.connect("ArduinoClient", mqtt_username, mqtt_password)) {
      Serial.println("connected");
      mqttClient.subscribe(mqttTopic);

      if (mqttClient.connected()) {
        mqttClient.publish(mqttConnected, "true");
      }
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void handleMqttMessage(char* topic, byte* payload, unsigned int length) {
  String message = "";
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  // Convert the received message to an integer
  int receivedValue = message.toInt();

  // Use the received value as the new initial value
  initialValue = receivedValue;

  Serial.print("Received new initial value: ");
  Serial.println(initialValue);
}
