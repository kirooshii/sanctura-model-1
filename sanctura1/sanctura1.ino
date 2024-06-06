// pins definition
const int motor1_enablePin = 9; // pin to enable the motor1
const int motor1_in1Pin = 7;    // pin for entrance 1 - L298N
const int motor1_in2Pin = 8;    // pin for entrance 2 - L298N

const int motor2_enablePin = 12; // pin to enable the motor2
const int motor2_in1Pin = 10; // pin for entrance 1 - L298N
const int motor2_in2Pin = 11; // pin for entrance 2 - L298N

void setup() {
  // configure the pins for output
  pinMode(motor1_enablePin, OUTPUT);
  pinMode(motor1_in1Pin, OUTPUT);
  pinMode(motor1_in2Pin, OUTPUT);
  pinMode(motor2_enablePin, OUTPUT);
  pinMode(motor2_in1Pin, OUTPUT);
  pinMode(motor2_in2Pin, OUTPUT);
}

void loop() {
  // motor1 starts working in one direction
  digitalWrite(motor1_in1Pin, HIGH);
  digitalWrite(motor1_in2Pin, LOW);
  analogWrite(motor1_enablePin, 255); // full speed
  delay(2000); // work for 2 seconds

  // stop motor1
  analogWrite(motor1_enablePin, 0);
  delay(1000); // wait 1 second

  // motor2 starts working in one direction
  digitalWrite(motor2_in1Pin, HIGH);
  digitalWrite(motor2_in2Pin, LOW);
  analogWrite(motor2_enablePin, 255); // full speed
  delay(2000); // work for 2 seconds

  // stop motor2
  analogWrite(motor2_enablePin, 0);
  delay(1000); // wait 1 second

  // motor1 starts working in another direction
  digitalWrite(motor1_in1Pin, LOW);
  digitalWrite(motor1_in2Pin, HIGH);
  analogWrite(motor1_enablePin, 255); // full speed
  delay(2000); // work for 2 seconds

  // stop motor1
  analogWrite(motor1_enablePin, 0);
  delay(1000); // wait 1 second

  // motor2 starts working in another direction
  digitalWrite(motor2_in1Pin, LOW);
  digitalWrite(motor2_in2Pin, HIGH);
  analogWrite(motor2_enablePin, 255); // full speed
  delay(2000); // work for 2 seconds

  // stop motor2
  analogWrite(motor2_enablePin, 0);
  delay(1000); // wait 1 second
}


