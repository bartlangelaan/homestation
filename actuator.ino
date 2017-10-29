
#include <ESP8266HTTPClient.h>
HTTPClient http2;

bool isOnNow = false;

String getBody(int on) {
  // For the open-source version, I removed the device id. You need to change <DEVICEID> with the device id.
  return "{\"method\": \"passthrough\",\"params\": {\"deviceId\": \"<DEVICEID>\",\"requestData\": \"{\\\"system\\\":{\\\"set_relay_state\\\":{\\\"state\\\":" + String(on) + "}}}\"}}";
}

void turnLightOn() {
  if(isOnNow) return;
  // For the open-source version, I removed the token. You need to change <TOKEN> with the device token.
  http2.begin("http://secret-caverns-23903.herokuapp.com/https://eu-wap.tplinkcloud.com/?token=<TOKEN>");
  http2.addHeader("origin", "http://localhost");
  Serial.println(getBody(1));
  int httpCode = http2.POST(getBody(1));
  String payload = http2.getString();
  Serial.println("Received HTTP Code: " + String(httpCode));
  Serial.println("Received data: " + payload);
  http2.end();
  isOnNow = true;
}

void turnLightOff() {
  if(!isOnNow) return;
  // For the open-source version, I removed the token. You need to change <TOKEN> with the device token.
  http2.begin("http://secret-caverns-23903.herokuapp.com/https://eu-wap.tplinkcloud.com/?token=<TOKEN>");
  http2.addHeader("origin", "http://localhost");
  Serial.println(getBody(0));
  int httpCode = http2.POST(getBody(0));
  String payload = http2.getString();
  Serial.println("Received HTTP Code: " + String(httpCode));
  Serial.println("Received data: " + payload);
  http2.end();
  isOnNow = false;
}

