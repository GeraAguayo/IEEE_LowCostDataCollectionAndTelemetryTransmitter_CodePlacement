# NEO6M_Lib: Arduino Library for NEO-6M GPS Module

This project provides a simple, object-oriented wrapper library for interfacing with the popular **NEO-6M GPS module** on an Arduino, leveraging the powerful **TinyGPS++** library for parsing NMEA data and **SoftwareSerial** for communication.

## Features

* **Simple Interface:** Easy-to-use `setup`, `get_latitude`, and `get_longitude` methods.
* **Software Serial:** Uses `SoftwareSerial` to communicate with the GPS module, freeing up the hardware serial port for debugging.
* **Automatic Data Reading:** GPS data is read and updated automatically when requesting latitude or longitude.

---

## 🛠️ Hardware Setup

The NEO-6M module communicates via **TX** (Transmit) and **RX** (Receive) pins.

| NEO-6M Pin | Arduino Pin (Example) | Description |
| :---: | :---: | :--- |
| **VCC** | 3V | Power Supply |
| **GND** | GND | Ground |
| **TX** | **D3** (RX\_PIN) | GPS TX to Arduino RX |
| **RX** | **D4** (TX\_PIN) | GPS RX to Arduino TX |

***Note:*** *The example code uses **Digital Pin 3** as the **Software Serial RX** (connected to GPS TX) and **Digital Pin 4** as the **Software Serial TX** (connected to GPS RX).*

---

## Dependencies

This library relies on two external libraries, which must be installed in your Arduino IDE:

1.  **TinyGPS++**: For parsing the NMEA sentences from the GPS module.
2.  **SoftwareSerial**: For creating a secondary serial port to communicate with the GPS.

You can typically install these via the Arduino IDE's **Library Manager** (Sketch -> Include Library -> Manage Libraries...).

## Quick Start Tutorial

The example sketch demonstrates the basic flow for initializing and reading data from the GPS module.

### 1. Initialization and Setup

In the global scope, an instance of the `NEO6M` object is created:
```cpp
#include "NEO6M.h"
NEO6M gps;

int rx_pin = 3;// Software Serial RX pin on Arduino (to GPS TX) 
int tx_pin = 4;// Software Serial TX pin on Arduino (to GPS RX) 

```
In the setup() function, the connection is initialized:
```cpp

void setup(){
  Serial.begin(115200); // Initialize hardware serial for debugging 
  gps.setup(rx_pin,tx_pin);// Initialize SoftwareSerial (9600 baud) for GPS 
} 
```


### 2. Reading and Printing Data

The loop() function continuously reads data and prints the coordinates.

```cpp

void loop(){
  // 1. Read and decode any available NMEA data from the GPS module 
  gps.read_data(); 


  Serial.print("Lat: ");
  Serial.print(gps.latitude, 6);   // gps.latitude is updated in read_data() 
  
  Serial.print(" | Lon: ");       // Prints separator 
  Serial.println(gps.longitude, 6); // gps.longitude is updated in read_data() 
  
  delay(500); // Wait 500ms before the next loop iteration 
}

```
