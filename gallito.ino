#include <BluetoothSerial.h> // Librería Bluetooth
BluetoothSerial SerialBT;

// Definir pines del controlador MX1508
#define M1_IN1 25
#define M1_IN2 26
#define M2_IN1 27
#define M2_IN2 14
int velocidad=255;

void setup() {
  // Configuración del Bluetooth
  Serial.begin(115200);
  String nombreBluetooth = "Friforce"; // Cambia el nombre a lo que prefieras
  SerialBT.begin(nombreBluetooth);

  Serial.println("El dispositivo está listo para emparejarse");

  // Configuración de los pines como salida
  pinMode(M1_IN1, OUTPUT);
  pinMode(M1_IN2, OUTPUT);
  pinMode(M2_IN1, OUTPUT);
  pinMode(M2_IN2, OUTPUT);

  // Inicializar motores apagados
  detener();
}

void loop() {
  if (SerialBT.available()) {
    char comando = SerialBT.read();
    controlarCarrito(comando);
  }
}

// Función para controlar el carrito
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
    case 'S': // Detener
      detener();
      break;
  }
}

// Funciones para mover el carrito
void avanzar() {
  analogWrite(M1_IN1, 255); // Velocidad máxima
  analogWrite(M1_IN2, 0);   // Dirección
  analogWrite(M2_IN1, 255); // Velocidad máxima
  analogWrite(M2_IN2, 0);   // Dirección
}

void retroceder() {
  analogWrite(M1_IN1, 0);
  analogWrite(M1_IN2, 255); // Dirección opuesta
  analogWrite(M2_IN1, 0);
  analogWrite(M2_IN2, 255); // Dirección opuesta
}

void girarIzquierda() {
  analogWrite(M1_IN1, 0);   // Motor izquierdo se detiene
  analogWrite(M1_IN2, 0);   // Motor izquierdo se detiene
  analogWrite(M2_IN1, 255); // Motor derecho avanza
  analogWrite(M2_IN2, 0);   // Dirección
}

void girarDerecha() {
  analogWrite(M1_IN1, 255); // Motor izquierdo avanza
  analogWrite(M1_IN2, 0);   // Dirección
  analogWrite(M2_IN1, 0);   // Motor derecho se detiene
  analogWrite(M2_IN2, 0);   // Motor derecho se detiene
}

void detener() {
  analogWrite(M1_IN1, 0);
  analogWrite(M1_IN2, 0);
  analogWrite(M2_IN1, 0);
  analogWrite(M2_IN2, 0);
}
