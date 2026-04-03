#include <Adafruit_AHTX0.h>

Adafruit_AHTX0 aht;

Adafruit_Sensor *aht_humidity, *aht_temp;

void setup(void) {
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit AHT10/AHT20 test!");

  if (!aht.begin()) {
    Serial.println("Failed to find AHT10/AHT20 chip");
    while (1) {
      delay(10);
    }
  }

  Serial.println("AHT10/AHT20 Found!");
  aht_temp = aht.getTemperatureSensor();
  aht_temp->printSensorDetails();

  aht_humidity = aht.getHumiditySensor();
  aht_humidity->printSensorDetails();
}

void loop() {
  // Get the current time in milliseconds since the program started
  unsigned long currentMillis = millis();
  
  // Get a new normalized sensor event
  sensors_event_t humidity;
  sensors_event_t temp;
  aht_humidity->getEvent(&humidity);
  aht_temp->getEvent(&temp);
  
  // Print the timestamp along with temperature and humidity
  Serial.print("Time: ");
  Serial.print(currentMillis); // Display the time in milliseconds
  Serial.print(" ms\t\tTemperature: ");
  Serial.print(temp.temperature);
  Serial.println(" deg C");
  
  Serial.print("\t\tHumidity: ");
  Serial.print(humidity.relative_humidity);
  Serial.println(" % rH");

  // Serial Plotter
  Serial.print(temp.temperature);
  Serial.print(",");
  Serial.print(humidity.relative_humidity);
  Serial.println();

  delay(500);
}
