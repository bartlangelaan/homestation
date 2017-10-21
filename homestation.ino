// This is the entry file of the homestation. The code sets
// up various sensors and the OLED display, gets all current
// sensor data from the sensors, displays them and sends them
// to the iot-open-server.

// The number of seconds every sensor is displayed on the
// OLED display
int SCREEN_DISPLAY_TIME = 3;


void setup() {
  // Make serial data available for all other files.
  Serial.begin(9600);

  // Setup the display.
  displaySetup();

  // Setup the DHT sensor.
  setupDHT();
}

void loop() {
  // Get all sensor data
  float temperature = getTemperature();
  float humidity = getHumidity();

  // Determine the sensor data to display
  int screen_number = millis() / 1000 / SCREEN_DISPLAY_TIME;

  // Display the right sensor data
  switch(screen_number % 2) {
    case 0:
      displayShow(temperature, " C", "temperature");
      break;
    case 1:
      displayShow(humidity, "%", "humidity");
  }

  // The sensor data isn't refreshed that much, wait 200ms
  // before getting new data
  delay(200);
}
