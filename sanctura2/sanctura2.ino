/*
File: sanctura2.ino
Project: fight test 2
Author: kiroshi
*/

// ----------------------------------------------------------------------------------------------------------------------
// Pin definitions
#define motor1_enablePin 11 // Pin to enable motor1
#define motor1_in1Pin 9 // Pin for entrance 1 - L298N
#define motor1_in2Pin 10 // Pin for entrance 2 - L298N
#define motor2_enablePin 8 // Pin to enable motor2
#define motor2_in1Pin 12 // Pin for entrance 1 - L298N
#define motor2_in2Pin 13 // Pin for entrance 2 - L298N

#define front_trigPin 2 // Pin for the trigger of the ultrasonic sensor
#define front_echoPin 3 // Pin for the echo of the ultrasonic sensor
#define left_trigPin 4 // Pin for the trigger of the ultrasonic sensor
#define left_echoPin 5 // Pin for the echo of the ultrasonic sensor
#define right_trigPin 6 // Pin for the trigger of the ultrasonic sensor
#define right_echoPin 7 // Pin for the echo of the ultrasonic sensor

// Global variables
long duration;
int front_distance;
int left_distance;
int right_distance;

// Threshold values
const int opponent_threshold = 20; // Threshold distance for detecting opponent
const int edge_threshold = 10; // Threshold distance for detecting edge

void setup() {
// Configure the pins for output

// Configure the motors
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

// Main decision-making logic
if (front_distance < opponent_threshold && front_distance > 0) {
// Opponent detected in front
motors(255, 255); // Charge forward
} else if (left_distance < edge_threshold) {
// Edge detected on the left
motors(255, -255); // Pivot right
} else if (right_distance < edge_threshold) {
// Edge detected on the right
motors(-255, 255); // Pivot left
} else if (left_distance < opponent_threshold && left_distance > 0) {
// Opponent detected on the left
motors(-255, 255); // Turn left
} else if (right_distance < opponent_threshold && right_distance > 0) {
// Opponent detected on the right
motors(255, -255); // Turn right
} else {
// No opponent detected, search for the opponent
motors(0, 0); // Stop to reevaluate
search_for_opponent();
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