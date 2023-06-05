// Define the LED pin
const int ledPin = 13;

void setup() {
  // Set the LED pin as an output
  pinMode(ledPin, OUTPUT);

  // Start the Serial communication
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    // Read the incoming data from the Serial Monitor
    String command = Serial.readString();

    // Remove any leading or trailing whitespace
    command.trim();

    // Check the received command
    if (command.equalsIgnoreCase("ON")) {
      // Turn the LED on
      digitalWrite(ledPin, HIGH);
      Serial.println("LED is ON");
    } else if (command.equalsIgnoreCase("OFF")) {
      // Turn the LED off
      digitalWrite(ledPin, LOW);
      Serial.println("LED is OFF");
    } else {
      // Invalid command
      Serial.println("Invalid command");
    }
  }
}
