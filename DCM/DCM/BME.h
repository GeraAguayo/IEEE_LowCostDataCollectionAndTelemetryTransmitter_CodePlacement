#ifndef BME_H
#define BME_H

//BME 380 Sensor module
//GRI

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"

struct bme_data  {
  float temperature; //°C
  float pressure; //hPa
  float humidity; //%
  float gas; //kOhms
  float altitude; //m
};

class BME{
  private:
    Adafruit_BME680 bme;
  public:
    BME();
    ~BME();
    void begin();
    bme_data get_values();
    bool is_enabled();
};

#endif