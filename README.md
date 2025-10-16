# GallitoTec
Codigo de Gallitos

---

## 🚗 Proyecto GallitoTec

Este proyecto controla un carrito robótico mediante **Bluetooth**, utilizando un ESP32 y un controlador de motores **MX1508**.

---

### 🔧 Componentes usados

* ESP32
* Driver MX1508
* 2 Motores DC
* Conexión Bluetooth (nombre del dispositivo: `Friforce`)
* Aplicación de control Bluetooth

---

### 📱 Aplicación recomendada

Para controlar el carrito puedes usar **“Bluetooth Terminal HC-05”** (Android), que permite enviar caracteres al ESP32 desde tu celular. También puedes usar cualquier app similar que permita enviar caracteres simples por Bluetooth, como:

* [Serial Bluetooth Terminal (Android)](https://play.google.com/store/apps/details?id=de.kai_morich.serial_bluetooth_terminal)
* [Bluetooth Electronics (Android/iOS)](https://www.keuwl.com/apps/bluetooth-electronics/)
* Aplicación personalizada en MIT App Inventor (opcional)

Solo necesitas emparejar tu celular con el ESP32 (`Friforce`) y enviar los comandos siguientes:

| Comando | Acción               |
| ------- | -------------------- |
| `F`     | Avanzar              |
| `B`     | Retroceder           |
| `L`     | Girar a la izquierda |
| `R`     | Girar a la derecha   |
| `S`     | Detener el carrito   |

---

### ⚙️ Pines utilizados

```cpp
#define M1_IN1 25
#define M1_IN2 26
#define M2_IN1 27
#define M2_IN2 14
```

---

### 🧠 ¿Cómo funciona?

El ESP32 recibe comandos vía Bluetooth y ejecuta una acción correspondiente en los motores del carrito. Todo el procesamiento se hace dentro de la función `controlarCarrito()`:

```cpp
if (SerialBT.available()) {
  char comando = SerialBT.read();
  controlarCarrito(comando);
}
```

---

## 🔌 Conexiones entre ESP32, TB6612FNG y batería

### 📦 Módulo TB6612FNG ↔ ESP32

| TB6612FNG | ESP32     | Descripción                         |
|-----------|-----------|-------------------------------------|
| AIN1      | GPIO 25   | Dirección Motor A                   |
| AIN2      | GPIO 26   | Dirección Motor A                   |
| PWMA      | GPIO 32   | PWM para Motor A                    |
| BIN1      | GPIO 27   | Dirección Motor B                   |
| BIN2      | GPIO 14   | Dirección Motor B                   |
| PWMB      | GPIO 33   | PWM para Motor B                    |
| STBY      | GPIO 15   | Activa el puente (poner en HIGH)    |
| VM        | + batería | Alimentación de motores (6V–12V)    |
| VCC       | 5V ESP32  | Alimentación lógica del puente      |
| GND       | GND común | Tierra común con ESP32 y batería    |

---

### 🔋 Conexión de la batería (para los motores)

- **Positivo (+)** → Conectar al pin **VM** del TB6612FNG  
- **Negativo (–)** → Conectar al **GND** del TB6612FNG **y también al GND del ESP32**

> ⚠️ **No conectes directamente el + de la batería al pin 5V del ESP32**.  
> Si deseas alimentar también el ESP32 desde la misma batería, utiliza un **regulador de voltaje** (como un **LM2596**) y conecta la salida regulada de 5V al pin **Vin** o **5V** del ESP32.

---

### 📱 Comunicación Bluetooth

- El ESP32 se empareja vía Bluetooth con el nombre: **`Friforce`**
- Puedes usar una app como:
  - `Serial Bluetooth Terminal` (Android)
  - `Bluetooth RC Controller` u otras similares
- Comandos disponibles:
  - `'F'` → Adelante
  - `'B'` → Atrás
  - `'L'` → Izquierda
  - `'R'` → Derecha
  - `'S'` → Detener
