const int lm35Pin = A0;   // LM35 sensor connected to Analog pin A0
const int ledPin = 13;    // Onboard LED connected to digital pin 13

unsigned long previousMillis = 0;
unsigned long interval = 250;  // Default interval for temperature below 30 degrees


void setup() {
  pinMode(lm35Pin, INPUT);
  pinMode(ledPin, OUTPUT);

  Serial.begin(9600);
}

void blinkLED(int blinkInterval) {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= blinkInterval) {
    previousMillis = currentMillis;

    // Toggle the LED state
    digitalWrite(ledPin, !digitalRead(ledPin));
  }
}

void loop() {
  // Read temperature from LM35 sensor
  int temperature = analogRead(lm35Pin);
  //Convert digital data into analog by multiplying by 5000 and dividing by 1024
float voltage = temperature * (5000 / 1024.0);
// Convert the voltage into the temperature in degree Celsius:
float celsius = voltage / 10;

   // Show temperature on Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(celsius);
  Serial.println(" degrees Celsius");

  // Determine the blink interval based on temperature
  if (celsius < 30) {
    interval = 250;
  } else {
    interval = 500;
  }

  // Call the blinkLED function with the determined interval
  blinkLED(interval);
}
