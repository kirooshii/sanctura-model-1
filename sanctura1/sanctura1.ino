// Define the GPIO pins for motor control
const int motorPin1 = 23;
const int motorPin2 = 22;

void setup() {
  // Initialize the motor control pins as outputs
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
}

void loop() {
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, HIGH);
  delay(1000); // Run for 1 second

  // Stop the motor
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  delay(500); // Pause for 0.5 second
}
