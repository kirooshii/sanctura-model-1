/*
File: angletest.ino
Project: reverse and attack
Author: kiroshi
*/

// ----------------------------------------------------------------------------------------------------------------------

#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM6DS33.h> // Replace this with the appropriate library for your 4DOF sensor

Adafruit_MPU6050 mpu;

// Pin definitions remain the same
#define motor1_enablePin 11
#define motor1_in1Pin 9
#define motor1_in2Pin 10
#define motor2_enablePin 8
#define motor2_in1Pin 12
#define motor2_in2Pin 13

#define front_trigPin 2
#define front_echoPin 3
#define left_trigPin 4
#define left_echoPin 5
#define right_trigPin 6
#define right_echoPin 7

// Global variables
long duration;
int front_distance;
int left_distance;
int right_distance;

// Threshold values
const int opponent_threshold = 20;
const int edge_threshold = 10;
const float lift_threshold = 10.0; // Threshold angle in degrees

void setup() {
  // Configure the pins for output
  pinMode(motor1_enablePin, OUTPUT);
  pinMode(motor1_in1Pin, OUTPUT);
  pinMode(motor1_in2Pin, OUTPUT);
  pinMode(motor2_enablePin, OUTPUT);
  pinMode(motor2_in1Pin, OUTPUT);
  pinMode(motor2_in2Pin, OUTPUT);

  // Configure the pins for the ultrasonic sensors
  pinMode(front_trigPin, OUTPUT);
  pinMode(front_echoPin, INPUT);
  pinMode(left_trigPin, OUTPUT);
  pinMode(left_echoPin, INPUT);
  pinMode(right_trigPin, OUTPUT);
  pinMode(right_echoPin, INPUT);

  // Initialize the MPU6050
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  // Initialize serial communication
  Serial.begin(9600);
}

void loop() {
  // Continuously measure and output distances
  front_distance = measureDistance(front_trigPin, front_echoPin);
  left_distance = measureDistance(left_trigPin, left_echoPin);
  right_distance = measureDistance(right_trigPin, right_echoPin);

  // Print distances to the Serial Monitor
  Serial.print("Front Sensor Distance: ");
  Serial.print(front_distance);
  Serial.println(" cm");
  Serial.print("Left Sensor Distance: ");
  Serial.print(left_distance);
  Serial.println(" cm");
  Serial.print("Right Sensor Distance: ");
  Serial.print(right_distance);
  Serial.println(" cm");

  // Read angle sensor data
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Check for lifting
  if (abs(a.acceleration.z) < lift_threshold) {
    // Robot is being lifted
    reverse_and_attack();
  } else {
    // Main decision-making logic
    if (front_distance < opponent_threshold && front_distance > 0) {
      motors(255, 255); // Charge forward
    } else if (left_distance < edge_threshold) {
      motors(255, -255); // Pivot right
    } else if (right_distance < edge_threshold) {
      motors(-255, 255); // Pivot left
    } else if (left_distance < opponent_threshold && left_distance > 0) {
      motors(-255, 255); // Turn left
    } else if (right_distance < opponent_threshold && right_distance > 0) {
      motors(255, -255); // Turn right
    } else {
      motors(0, 0); // Stop to reevaluate
      search_for_opponent();
    }
  }

  delay(10); // A slight delay at the end of the code for stability, prevents jittery movement
}

// Function to measure distance using ultrasonic sensor
int measureDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;
  return distance;
}

// Function to control the motors
void motors(int l, int r) {
  // Motor control using PWM values (0-255 for analogWrite)
  analogWrite(motor1_enablePin, abs(l));
  digitalWrite(motor1_in1Pin, l > 0);
  digitalWrite(motor1_in2Pin, l < 0);

  analogWrite(motor2_enablePin, abs(r));
  digitalWrite(motor2_in1Pin, r > 0);
  digitalWrite(motor2_in2Pin, r < 0);
}

// Function to search for the opponent
void search_for_opponent() {
  // Rotate to search for the opponent
  motors(255, -255);
  delay(500); // Rotate for half a second
  motors(0, 0); // Stop
}

// Function to reverse and attack
void reverse_and_attack() {
  // Reverse
  motors(-255, -255);
  delay(500); // Reverse for half a second
  // Stop briefly
  motors(0, 0);
  delay(100);
  // Attack forward
  motors(255, 255);
  delay(500); // Move forward for half a second
  motors(0, 0); // Stop
}
