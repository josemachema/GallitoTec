#include <BluetoothSerial.h>
BluetoothSerial SerialBT;

// Pines del TB6612
#define AIN1 25
#define AIN2 26
#define PWMA 32  // PWM para motor A

#define BIN1 27
#define BIN2 14
#define PWMB 33  // PWM para motor B

#define STBY 15  // Standby, debe estar en HIGH

int velocidad = 255;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("Friforce"); // Cambia el nombre si quieres
  Serial.println("El dispositivo está listo para emparejarse");

  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);

  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);

  pinMode(STBY, OUTPUT);
  digitalWrite(STBY, HIGH);  // Activar el puente

  detener();
}

void loop() {
  if (SerialBT.available()) {
    char comando = SerialBT.read();
    controlarCarrito(comando);
  }
}

void controlarCarrito(char comando) {
  switch (comando) {
    case 'F':
      avanzar();
      break;
    case 'B':
      retroceder();
      break;
    case 'L':
      girarIzquierda();
      break;
    case 'R':
      girarDerecha();
      break;
    case 'S':
      detener();
      break;
  }
}

void avanzar() {
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  analogWrite(PWMA, velocidad);

  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMB, velocidad);
}

void retroceder() {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  analogWrite(PWMA, velocidad);

  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
  analogWrite(PWMB, velocidad);
}

void girarIzquierda() {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
  analogWrite(PWMA, 0);  // Motor A detenido

  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMB, velocidad);
}

void girarDerecha() {
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  analogWrite(PWMA, velocidad);

  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMB, 0);  // Motor B detenido
}

void detener() {
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);
}
