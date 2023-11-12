#include <BfButton.h>
#include <PubSubClient.h>
#include <WiFiNINA.h>

const char* ssid = "#";
const char* password = "#";
const char* mqtt_server = "#";
const char* mqtt_topic = "analog/read";
const char* mqtt_button_topic = "button/click";
const char* mqtt_username = "#";
const char* mqtt_password = "#";

int btnPin = 3;
int DT = 4;
int CLK = 5;
BfButton btn(BfButton::STANDALONE_DIGITAL, btnPin, true, LOW);

int counter = 0;
int angle = 0;
int lastAngle = 0;
int aState;
int aLastState;

WiFiClient wifiClient; 
PubSubClient mqttClient(wifiClient); 

void pressHandler(BfButton *btn, BfButton::press_pattern_t pattern) {
  switch (pattern) {
    case BfButton::SINGLE_PRESS:
      Serial.println("Single push");
      mqttClient.publish(mqtt_button_topic, "single_press");
      break;

    case BfButton::DOUBLE_PRESS:
      Serial.println("Double push");
      break;

    case BfButton::LONG_PRESS:
      Serial.println("Long push");
      break;
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println(angle);
  pinMode(CLK, INPUT_PULLUP);
  pinMode(DT, INPUT_PULLUP);
  aLastState = digitalRead(CLK);

  // Connect to WiFi
  connectWiFi();

  mqttClient.setServer(mqtt_server, 1883);
  //mqttClient.setCallback(handleMqttMessage);
  btn.onPress(pressHandler)
      .onDoublePress(pressHandler)
      .onPressFor(pressHandler, 1000);
}

void loop() {
  btn.read();
  aState = digitalRead(CLK);

  if (aState != aLastState) {
    if (digitalRead(DT) != aState) {
      angle = 1; 
    } else {
      angle = -1; 
    }
    if (!mqttClient.connected()) {
    // Reconnect to MQTT broker
    reconnect();
  }

  mqttClient.loop();
    char angleStr[10];
    itoa(angle, angleStr, 10);
    mqttClient.publish(mqtt_topic, angleStr);
    lastAngle = angle;
    Serial.println(angle);
  }


  aLastState = aState;
}
