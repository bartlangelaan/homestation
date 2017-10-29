void setupLightSensor() {
  //pinMode(D7, INPUT);
}

float getLight() {
  bool on = digitalRead(D7);
  return on;
}

