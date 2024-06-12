/*
  File: sanctura1.ino
  Project: sensor test
  Author: kiroshi
*/

// ----------------------------------------------------------------------------------------------------------------------
// Pins definition

// motors
#define motor1_enablePin 5  // Pin to enable the motor1
#define motor1_in1Pin 7     // Pin for entrance 1 - L298N
#define motor1_in2Pin 6     // Pin for entrance 2 - L298N
#define motor2_enablePin 8  // Pin to enable the motor2
#define motor2_in1Pin 9     // Pin for entrance 1 - L298N
#define motor2_in2Pin 10    // Pin for entrance 2 - L298N

// infrared sensor
#define hw006Pin A0         // Pin connected to the OUT pin of HW006

// ultrasonic sensors
#define front_trigPin 3     // Pin for the trigger of the ultrasonic sensor
#define front_echoPin 4     // Pin for the echo of the ultrasonic sensor
#define left_trigPin 2     // Pin for the trigger of the ultrasonic sensor
#define left_echoPin 11      // Pin for the echo of the ultrasonic sensor
#define right_trigPin 12    // Pin for the trigger of the ultrasonic sensor
#define right_echoPin 13    // Pin for the echo of the ultrasonic sensor

// Global variables
long duration;
int distance;

void setup() {
  // Configure the pins for output

  // Configure the motors
  pinMode(motor1_enablePin, OUTPUT);
  pinMode(motor1_in1Pin, OUTPUT);
  pinMode(motor1_in2Pin, OUTPUT);
  pinMode(motor2_enablePin, OUTPUT);
  pinMode(motor2_in1Pin, OUTPUT);
  pinMode(motor2_in2Pin, OUTPUT);

  // Configure the pins for the HW006 sensor
  pinMode(hw006Pin, INPUT);

  // Configure the pins for the ultrasonic sensors
  pinMode(front_trigPin, OUTPUT);
  pinMode(front_echoPin, INPUT);
  pinMode(left_trigPin, OUTPUT);
  pinMode(left_echoPin, INPUT);
  pinMode(right_trigPin, OUTPUT);
  pinMode(right_echoPin, INPUT);

  // Initialize serial communication
  Serial.begin(9600);
}

void loop() {
  // Continuously measure and output distances
  //measureAndPrintDistance(front_trigPin, front_echoPin, "Front");
  //measureAndPrintDistance(left_trigPin, left_echoPin, "Left");
  //measureAndPrintDistance(right_trigPin, right_echoPin, "Right");
  checkHW006();
}

// ----------------------------------------------------------------------------------------------------------------------
// Functions
// ----------------------------------------------------------------------------------------------------------------------

void measureAndPrintDistance(int trigPin, int echoPin, const char* sensorName) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculating the distance
  distance = duration * 0.034 / 2;

  // Print the distance to the Serial Monitor
  Serial.print(sensorName);
  Serial.print(" Sensor Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
}

void checkHW006() {
  // Read the state of HW006 sensor
  int hw006State = digitalRead(hw006Pin);

  // Print the state to the Serial Monitor
  if (hw006State == HIGH) {
    Serial.println("HW006 sensor: LED is working");
    // Motor1 starts working in one direction
    digitalWrite(motor1_in1Pin, HIGH);
    digitalWrite(motor1_in2Pin, LOW);
    analogWrite(motor1_enablePin, 255); // Full speed
    // Motor1 starts working in one direction
    digitalWrite(motor2_in1Pin, HIGH);
    digitalWrite(motor2_in2Pin, LOW);
    analogWrite(motor2_enablePin, 255); // Full speed

  } else {
    Serial.println("HW006 sensor: LED is not working");
    // Stop the motor if conditions are not met
    digitalWrite(motor1_enablePin, LOW);
    digitalWrite(motor2_enablePin, LOW);
  }
}
