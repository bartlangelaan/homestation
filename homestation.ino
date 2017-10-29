// This is the entry file of the homestation. The code sets
// up various sensors and the OLED display, gets all current
// sensor data from the sensors, displays them and sends them
// to the iot-open-server.

// The number of seconds every sensor is displayed on the
// OLED display
int SCREEN_DISPLAY_TIME = 3;

// The number of seconds between data posts
int DATA_POST_TIME = 5;


void setup() {
  // Make serial data available for all other files.
  Serial.begin(9600);

  // Setup the display.
  displaySetup();

  // Setup the DHT sensor.
  setupDHT();

  // Connect to Wifi neworks
  setupWifi();

  // Set up light sensor
  setupLightSensor();
}

int lastDataSent = 0;

void loop() {
  
  // Get all sensor data
  float temperature = getTemperature();
  float humidity = getHumidity();
  bool light = getLight();
  float windspeed = getWindspeed();

  // Determine the sensor data to display
  int screen_number = millis() / 1000 / SCREEN_DISPLAY_TIME;

  //Display the right sensor data
  switch(screen_number % 4) {
    case 0:
      displayShow(String(temperature), " C", "temperature");
      break;
    case 1:
      displayShow(String(humidity), "%", "humidity");
      break;
    case 2:
      displayShow(light ? "On" : "Off", "", "light");
      break;
    case 3:
      displayShow(String(windspeed), "km/h", "windspeed");
      break;
  }

  if(lastDataSent < (millis() - (DATA_POST_TIME * 1000))) {
    if(sendData(temperature, humidity, light, windspeed)) {
      lastDataSent = millis();
    }
  }

  if(light >= 1 && temperature > 24) {
    turnLightOn();
  }
  else {
    turnLightOff();
  }
}
