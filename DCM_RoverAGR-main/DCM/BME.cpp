//BME 380 Sensor module
//GRI
#include "BME.h"
#include <Wire.h>
//#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"

#define SEALEVELPRESSURE_HPA (1013.25)
bool bme_found = false;

BME::BME(){
  bme_found = false;
}

void BME::begin(){
  //initialize bme 680
  if(!this->bme.begin()){
    bme_found = false;
  }
  else{
    bme_found = true;
    // Set up oversampling and filter initialization
    this->bme.setTemperatureOversampling(BME680_OS_8X);
    this->bme.setHumidityOversampling(BME680_OS_2X);
    this->bme.setPressureOversampling(BME680_OS_4X);
    this->bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
    this->bme.setGasHeater(320, 150); // 320*C for 150 ms
  }
}

BME::~BME(){
  //destructor
}

bme_data BME::get_values(){
  bme_data data_set = bme_data{};
  //read from sensor
  this->bme.beginReading();
  delay(50);
  //save values
  data_set.temperature = this->bme.temperature;
  data_set.pressure = this->bme.pressure;
  data_set.humidity = this->bme.humidity;
  data_set.gas = this->bme.gas_resistance / 1000.0;
  data_set.altitude = this->bme.readAltitude(SEALEVELPRESSURE_HPA);
  return data_set;

}

bool BME::is_enabled(){
  if(!this->bme.begin()){
    return false;
  }
  else{
    return true;
  }

}