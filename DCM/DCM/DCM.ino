/*
DATA COLLECTION MODULE
Rover AGR
Gerardo Aguayo
*/
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include "BME.h"
BME bme_sensor;
//GPS config
#define GPS_TX_PIN 4
#define GPS_RX_PIN 3
SoftwareSerial gps_serial(GPS_TX_PIN,GPS_RX_PIN);
TinyGPSPlus gps;

/*
Serial Values Standard
Temperature - 0
Pressure - 1
Altitude - 2
Humidity - 3
Gas - 4
Latitude - 5
Longitude - 6
*/
float temperature, pressure, altitude, humidity, gas, latitude, longitude = 0.0;
bool valid_data = true;

void raise_error();

enum error_ids {
  BME_ERROR = 2,
};

void setup() {
  Serial.begin(9600);
  delay(100);
  bme_sensor.begin();
  delay(100);
  gps_serial.begin(9600);
}

void loop() {

  //Read GPS
  while (gps_serial.available()){
    gps.encode(gps_serial.read());
  }
  if (gps.location.isValid()){
    latitude = gps.location.lat();
    longitude = gps.location.lng();
  }
  else{
    latitude = 0.0;
    longitude = 0.0;
  }

  //Read bme680
  if (bme_sensor.is_enabled()){
    bme_data data = bme_sensor.get_values();
    temperature = data.temperature;
    pressure = data.pressure;
    altitude = data.altitude;
    humidity = data.humidity;
    gas = data.gas;
    valid_data = true;
  }
  else{
    //Raise BME error and try again
    raise_error(BME_ERROR);
    bme_sensor.begin();
  }

  if (valid_data){
    //Send data
    Serial.println("DATA");
    Serial.println(temperature);
    Serial.println(pressure);
    Serial.println(altitude);
    Serial.println(humidity);
    Serial.println(gas);
    Serial.println(latitude, 6);
    Serial.println(longitude, 6);
    Serial.println("END");

  }
}

void raise_error(error_ids id){
  valid_data = false;
  Serial.println("SYSLOG");
  Serial.println(id);
  Serial.println("END");

}
