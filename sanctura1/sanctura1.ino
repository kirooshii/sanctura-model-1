// Definir pines del Arduino
const int enablePin = 9; // Pin de habilitación del motor
const int in1Pin = 7;    // Pin de entrada 1 del L298N
const int in2Pin = 8;    // Pin de entrada 2 del L298N

void setup() {
  // Configurar los pines como salidas
  pinMode(enablePin, OUTPUT);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
}

void loop() {
  // Hacer girar el motor en una dirección
  digitalWrite(in1Pin, HIGH);
  digitalWrite(in2Pin, LOW);
  analogWrite(enablePin, 255); // Velocidad máxima
  delay(2000); // Girar durante 2 segundos

  // Detener el motor
  analogWrite(enablePin, 0);
  delay(1000); // Esperar 1 segundo

  // Hacer girar el motor en la otra dirección
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, HIGH);
  analogWrite(enablePin, 255); // Velocidad máxima
  delay(2000); // Girar durante 2 segundos

  // Detener el motor
  analogWrite(enablePin, 0);
  delay(1000); // Esperar 1 segundo
}


