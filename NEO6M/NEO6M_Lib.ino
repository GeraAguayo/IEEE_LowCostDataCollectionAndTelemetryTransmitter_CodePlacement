#include "NEO6M.h"
NEO6M gps;

double last_lat = 0.0;
double last_lon = 0.0;
int rx_pin = 3;
int tx_pin = 4;

void setup(){
  Serial.begin(115200);
  gps.setup(rx_pin,tx_pin);
} 

void loop(){
  gps.read_data();
  last_lat = gps.get_latitude();
  last_lon = gps.get_longitude();

  Serial.print("Lat: ");
  Serial.print(gps.latitude, 6);
  Serial.print(" | Lon: ");
  Serial.println(gps.longitude, 6);
  delay(500);
}