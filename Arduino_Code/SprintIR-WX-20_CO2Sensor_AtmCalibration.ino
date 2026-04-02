String line = "";
int multiplier = 1;

void setup() {
  Serial.begin(115200);  // Serial to PC
  Serial2.begin(9600);   // Hardware Serial2 to SprintIR (Pins 16 & 17)

  Serial.println("=== SprintIR CO2 POLLING MODE (MEGA) ===");
  Serial.println("Type 'G' and press Enter to calibrate to 400 ppm (Fresh Air).");

  delay(2000);  // warm-up

  // Put sensor into polling mode
  Serial2.print("K 2\r\n");
  delay(200);

  // Clear buffer
  while (Serial2.available()) Serial2.read();

  Serial.print("Fetching Multiplier... ");
  Serial2.print(".\r\n");
  delay(100);
  
  String multResponse = "";
  while (Serial2.available()) {
    char c = Serial2.read();
    if (c == '\n') break;
    multResponse += c;
  }
  multResponse.trim();
  
  // Parse the multiplier response (looks like ". 00010")
  if (multResponse.startsWith(".")) {
    multiplier = multResponse.substring(1).toInt();
    Serial.print("x");
    Serial.println(multiplier);
  } else {
    Serial.println("Failed to read multiplier, defaulting to x1.");
  }
  
  // Clear buffer again just in case
  while (Serial2.available()) Serial2.read();
  Serial.println("=================================");
}

void loop() {
  // 1. CHECK FOR USER INPUT (Calibration)
  if (Serial.available()) {
    char inputChar = Serial.read(); // Read exactly one character

    // If that character is a G (uppercase or lowercase)
    if (inputChar == 'G' || inputChar == 'g') {
      Serial.println("\n[Sending Fresh Air Calibration Command (G)...]");
      Serial2.print("G\r\n"); 
      
      delay(100);
      
      String calResponse = "";
      while (Serial2.available()) {
        calResponse += (char)Serial2.read();
      }
      calResponse.trim();
      
      Serial.print("Sensor replied: ");
      Serial.println(calResponse);
      Serial.println("Calibration complete! You should see ~400 ppm. Resuming polling...\n");
      
      // Clear out any trailing "Enter" keys left in the buffer
      while (Serial.available()) Serial.read(); 
      return; 
    }
  }

  // 2. NORMAL POLLING BEHAVIOR
  Serial2.print("Z\r\n");

  unsigned long start = millis();
  line = "";
  bool lineComplete = false; 

  while ((millis() - start < 50) && !lineComplete) {
    while (Serial2.available()) {
      char c = Serial2.read();

      if (c == '\n') {
        line.trim();   
        lineComplete = true; 
        break;         
      } else {
        line += c;
      }
    }
  }

  // Check if we have a valid response
  if (line.startsWith("Z")) {
    long co2raw = line.substring(1).toInt(); 
    long co2ppm = co2raw * multiplier;
    float co2per = (float)co2ppm / 10000.0;
    
    Serial.print("CO2: ");
    Serial.print(co2ppm);
    Serial.print(" ppm   |   ");
    Serial.print(co2per, 2); 
    Serial.println("%");

  } else if (line.length() > 0) {
    Serial.print("Invalid response: ");
    Serial.println(line);
  }

  delay(1000); // 1 Hz polling
}
