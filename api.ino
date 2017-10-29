#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>

String API_BASE = "http://iot-open-server.herokuapp.com";
// For the open-source version, I removed the API token. You need to enter it here:
String API_TOKEN = "";

HTTPClient http;

bool sendData(float temperature, float humidity, float light, float windspeed) {

  // Only send data if the wifi is connected.
  if(!wifiConnected()) return false;

  // Create data object
  StaticJsonBuffer<400> jsonBuffer;
  JsonObject& jsonRoot = jsonBuffer.createObject();
  JsonArray& data = jsonRoot.createNestedArray("data");
  jsonRoot["token"] = API_TOKEN;

  // Add sensor data to data object
  if(temperature > 1) {
    JsonObject& temperatureObject = jsonBuffer.createObject();
    temperatureObject["key"] = "temperature";
    temperatureObject["value"] = temperature;
    data.add(temperatureObject);
  }

  if(humidity > 1) {
    JsonObject& humidityObject = jsonBuffer.createObject();
    humidityObject["key"] = "humidity";
    humidityObject["value"] = humidity;
    data.add(humidityObject);
  }

  JsonObject& lightObject = jsonBuffer.createObject();
  lightObject["key"] = "light";
  lightObject["value"] = light;
  data.add(lightObject);

  if(windspeed >= 0) {
    JsonObject& windspeedObject = jsonBuffer.createObject();
    windspeedObject["key"] = "windspeed";
    windspeedObject["value"] = windspeed;
    data.add(windspeedObject);
  }

  // Convert data object to string
  String dataToSend;
  jsonRoot.printTo(dataToSend);
  Serial.println(dataToSend);

  // Send data
  http.begin(API_BASE + "/data");
  http.addHeader("Content-Type", "application/json");
  int httpCode = http.POST(dataToSend);
  String payload = http.getString();
  Serial.println("Received HTTP Code: " + String(httpCode));
  Serial.println("Received data: " + payload);
  http.end();


  return httpCode == 200;
}

