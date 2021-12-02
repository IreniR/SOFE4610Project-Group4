/*
 * SOFE 4610U - Final Project
 * Dr. Ramiro Liscano
 * Group 4
 * Shanjay Kailayanathan - 100624670
 * Jana Kanagalingam -100603975
 * Ireni Ruthirakuhan - 100657302
 * Jerusha Macwan - 100723319
 */

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

#define DHTPIN 5     // Digital pin connected to the DHT sensor
#define DHTTYPE    DHT11     // DHT 11

DHT dht(DHTPIN, DHTTYPE);
float t = 0.0;
float tempLimit = 0.0;
float tempThresh = 0.0;
float upperLim = tempLimit + tempThresh;
float lowerLim = tempLimit - tempThresh;
int thresh = 0;
unsigned long previousMillis = 0;    // will store last time DHT was updated



// Updates DHT readings every 10s
const long interval = 10000;  

int buzzer = 4;//the pin of the active buzzer

// Update these with values suitable for your network.

const char* ssid = "XXXXXXXXX";
const char* password = "XXXXXXXX";
const char* mqtt_server = "www.iotgrp4.com";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;
int sampleRate = 2000; //2 samples per second default

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  if (strcmp(topic,"tempLimit")){
    int thresh = 0;
    Serial.println(topic);
    payload[length] = '\0'; // Make payload a string by NULL terminating it.
    tempLimit = float(atoi((char *)payload));
    thresh+=1;
  }
  if (strcmp(topic,"tempThresh")){
    int thresh = 0;
    Serial.println(topic);
    payload[length] = '\0'; // Make payload a string by NULL terminating it.
    tempThresh = float(atoi((char *)payload));
    thresh+=1;
  }
}

void setSampleRate(int sr){
  sampleRate = sr * 1000;
}

int getSampleRate(){
  return sampleRate;
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(), "group4", "IOT123class")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("temperatureOutput", "Temperature Sensor Connection Successful");
      // ... and resubscribe
      client.subscribe("tempLimit");
      client.subscribe("tempThresh");
      //return client.connected();
    } else {
      Serial.print("MQTT connection failed.");
      Serial.print(client.state());
      Serial.println(" Try again in 2 seconds.");
      // Wait 5 seconds before retrying
      delay(2000);
    }
  }
}

void alarm(){
  Serial.println(t);
  Serial.println(upperLim);
  Serial.println(lowerLim);
  if ((t > upperLim) || (t < lowerLim)){
    for(int i =0; i<3; i++){
      digitalWrite(buzzer,HIGH); 
      delay(1000);//wait for 1s 
      digitalWrite(buzzer,LOW); 
      delay(1000);//wait for 1s
    }
  }
  thresh = 0;
}

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  pinMode(buzzer,OUTPUT);//initialize the buzzer pin as an output 
  setup_wifi();
  client.setServer(mqtt_server, 8883);
  client.setCallback(callback);
  Serial.begin(115200);
  dht.begin();
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // save the last time you updated the DHT values
    previousMillis = currentMillis;
    // Read temperature as Celsius (the default)
    float newT = dht.readTemperature();
    // Read temperature as Fahrenheit (isFahrenheit = true)
    //float newT = dht.readTemperature(true);
    // if temperature read failed, don't change t value
    if (!isnan(newT)) {
      t = newT;
      String temp = String(t, 1);
      snprintf (msg, 75, temp.c_str(), value);
      Serial.print("Temperature: ");
      Serial.println(msg);
      client.publish("tempData", msg);
      if (thresh >= 2){
        alarm();
      }
    }
  }
}
