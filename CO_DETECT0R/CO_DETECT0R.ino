// MQ7 Gas Detection System with Buzzer and LED Alerts
// Description:
// This Arduino sketch reads gas concentration levels using the MQ7 sensor.
// When dangerous gas levels are detected (above threshold), it activates a buzzer
// and blinks a red LED as a warning. A green LED stays on when the environment is safe.

const int sensorPin = A0;      // Analog input pin connected to the MQ7 sensor's analog output
const int buzzerPin = 2;       // Digital output pin connected to the buzzer
const int redLEDPin = 4;       // Digital output pin connected to the red warning LED
const int greenLEDPin = 3;     // Digital output pin connected to the green safe-status LED

void setup() {
  // Configure all output pins
  pinMode(buzzerPin, OUTPUT);       // Buzzer will be triggered by digital HIGH/LOW
  pinMode(redLEDPin, OUTPUT);       // Red LED signals danger (blinking)
  pinMode(greenLEDPin, OUTPUT);     // Green LED signals safety (solid ON)

  // Ensure all outputs are OFF initially
  digitalWrite(buzzerPin, LOW);     
  digitalWrite(redLEDPin, LOW);
  digitalWrite(greenLEDPin, LOW);

  // Initialize serial communication for monitoring sensor readings via Serial Monitor
  Serial.begin(9600);
}

void loop() {
  // Step 1: Read the analog value from the MQ7 gas sensor
  int sensorValue = analogRead(sensorPin);

  // Step 2: Print sensor value to Serial Monitor for diagnostics or live monitoring
 
  Serial.print("Gas Level: ");
  Serial.println(sensorValue);
  delay(3000);

  // Step 3: Check if gas level crosses the predefined safety threshold
  // NOTE: You can adjust this threshold based on testing or calibration
  if (sensorValue > 300) {
    // DANGER CONDITION: High gas detected

    // Turn OFF green LED to indicate unsafe environment
    digitalWrite(greenLEDPin, LOW);

    // Blink red LED to warn user visually (100ms ON, 100ms OFF)
    digitalWrite(redLEDPin, HIGH);
    delay(100);
    digitalWrite(redLEDPin, LOW);
    delay(100);

    // Audible alert using buzzer with short pulse pattern (quick beeps)
    for (int i = 0; i < 40; i++) {
      digitalWrite(buzzerPin, HIGH);  // Turn buzzer ON
      delay(1);                        // Keep ON for 1ms
      digitalWrite(buzzerPin, LOW);   // Turn buzzer OFF
      delay(1);                        // Wait for 1ms
    }

    delay(30); // Short delay before changing sound pattern

    // Second pattern of buzzer beeps with slightly longer duration
    for (int j = 0; j < 50; j++) {
      digitalWrite(buzzerPin, HIGH);  // Longer pulse ON
      delay(2);
      digitalWrite(buzzerPin, LOW);   // Longer pulse OFF
      delay(2);
    }

  } else {
    // SAFE CONDITION: Gas level is normal

    // Turn OFF red LED, just in case it was blinking before
    digitalWrite(redLEDPin, LOW);

    // Turn ON green LED to indicate everything is safe
    digitalWrite(greenLEDPin, HIGH);

    // Make sure buzzer is OFF
    digitalWrite(buzzerPin, LOW);
  }

  // Step 4: Wait a short moment before next loop iteration
  // This prevents excessive serial output and gives smoother performance
  delay(100);
}
