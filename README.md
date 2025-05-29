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

