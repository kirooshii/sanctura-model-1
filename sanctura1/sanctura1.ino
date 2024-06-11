// Pins definition
const int motor1_enablePin = 10; // Pin to enable the motor1
const int motor1_in1Pin = 9;     // Pin for entrance 1 - L298N
const int motor1_in2Pin = 8;     // Pin for entrance 2 - L298N
const int hw006Pin = 12; // Pin connected to the OUT pin of HW006
const int trigPin = 5;   // Pin for the trigger of the ultrasonic sensor
const int echoPin = 6;   // Pin for the echo of the ultrasonic sensor

void setup()
{
  // Configure the pins for output
  pinMode(motor1_enablePin, OUTPUT);
  pinMode(motor1_in1Pin, OUTPUT);
  pinMode(motor1_in2Pin, OUTPUT);

  // Configure the pins for the HW006 sensor
  pinMode(hw006Pin, INPUT);

  // Configure the pins for the ultrasonic sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Initialize serial communication
  Serial.begin(9600);
}

void loop()
{
  long duration;
  int distance;

  // Clear the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculating the distance
  distance = duration * 0.034 / 2;

  // Print the distance to the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Read the state of HW006 sensor
  int hw006State = digitalRead(hw006Pin);

  // Motor control logic
  // Check if distance is less than 20cm and HW006 sensor detects something (LED is working)
  if (hw006State == HIGH)
  {
    // Motor1 starts working in one direction
    digitalWrite(motor1_in1Pin, HIGH);
    digitalWrite(motor1_in2Pin, LOW);
    analogWrite(motor1_enablePin, 255); // Full speed
  }
  else
  {
    // Stop the motor if conditions are not met
    digitalWrite(motor1_enablePin, LOW);
  }
}
