#include <BluetoothSerial.h> // Librería Bluetooth
BluetoothSerial SerialBT;

// =======================
// Pines BTS7960 - Motor izquierdo
// =======================
#define L_R_EN   32
#define L_L_EN   33
#define L_RPWM   25
#define L_LPWM   26

// =======================
// Pines BTS7960 - Motor derecho
// =======================
#define R_R_EN   27
#define R_L_EN   14
#define R_RPWM   12
#define R_LPWM   13

int velocidad = 255; // 0-255

// Canales PWM ESP32
const int ch_L_RPWM = 0;
const int ch_L_LPWM = 1;
const int ch_R_RPWM = 2;
const int ch_R_LPWM = 3;

const int freq = 20000;      // 20kHz para que no se escuche
const int resolution = 8;    // 8 bits (0-255)

void setup() {
  Serial.begin(115200);
  String nombreBluetooth = "Friforce"; // Nombre del BT
  SerialBT.begin(nombreBluetooth);

  Serial.println("El dispositivo está listo para emparejarse");

  // Configuración de pines ENABLE
  pinMode(L_R_EN, OUTPUT);
  pinMode(L_L_EN, OUTPUT);
  pinMode(R_R_EN, OUTPUT);
  pinMode(R_L_EN, OUTPUT);

  digitalWrite(L_R_EN, HIGH);
  digitalWrite(L_L_EN, HIGH);
  digitalWrite(R_R_EN, HIGH);
  digitalWrite(R_L_EN, HIGH);

  // Configuración PWM para cada pin
  ledcSetup(ch_L_RPWM, freq, resolution);
  ledcSetup(ch_L_LPWM, freq, resolution);
  ledcSetup(ch_R_RPWM, freq, resolution);
  ledcSetup(ch_R_LPWM, freq, resolution);

  ledcAttachPin(L_RPWM, ch_L_RPWM);
  ledcAttachPin(L_LPWM, ch_L_LPWM);
  ledcAttachPin(R_RPWM, ch_R_RPWM);
  ledcAttachPin(R_LPWM, ch_R_LPWM);

  detener();
}

void loop() {
  if (SerialBT.available()) {
    char comando = SerialBT.read();
    controlarCarrito(comando);
  }
}

// =======================
// Control por comando BT
// =======================
void controlarCarrito(char comando) {
  switch (comando) {
    case 'F': // Adelante
      avanzar();
      break;
    case 'B': // Atrás
      retroceder();
      break;
    case 'L': // Izquierda
      girarIzquierda();
      break;
    case 'R': // Derecha
      girarDerecha();
      break;
    case 'S': // Stop
      detener();
      break;
  }
}

// =======================
// Helpers para motores BTS7960
// vel: -255 a 255
// =======================
void setMotorIzquierdo(int vel) {
  vel = constrain(vel, -255, 255);

  if (vel > 0) {
    // Adelante
    ledcWrite(ch_L_RPWM, vel);
    ledcWrite(ch_L_LPWM, 0);
  } else if (vel < 0) {
    // Reversa
    ledcWrite(ch_L_RPWM, 0);
    ledcWrite(ch_L_LPWM, -vel);
  } else {
    // Stop
    ledcWrite(ch_L_RPWM, 0);
    ledcWrite(ch_L_LPWM, 0);
  }
}

void setMotorDerecho(int vel) {
  vel = constrain(vel, -255, 255);

  if (vel > 0) {
    // Adelante
    ledcWrite(ch_R_RPWM, vel);
    ledcWrite(ch_R_LPWM, 0);
  } else if (vel < 0) {
    // Reversa
    ledcWrite(ch_R_RPWM, 0);
    ledcWrite(ch_R_LPWM, -vel);
  } else {
    // Stop
    ledcWrite(ch_R_RPWM, 0);
    ledcWrite(ch_R_LPWM, 0);
  }
}

// =======================
// Movimientos del carrito
// =======================
void avanzar() {
  setMotorIzquierdo(velocidad);
  setMotorDerecho(velocidad);
}

void retroceder() {
  setMotorIzquierdo(-velocidad);
  setMotorDerecho(-velocidad);
}

void girarIzquierda() {
  // Izquierdo se detiene, derecho avanza
  setMotorIzquierdo(0);
  setMotorDerecho(velocidad);
}

void girarDerecha() {
  // Izquierdo avanza, derecho se detiene
  setMotorIzquierdo(velocidad);
  setMotorDerecho(0);
}

void detener() {
  setMotorIzquierdo(0);
  setMotorDerecho(0);
}
