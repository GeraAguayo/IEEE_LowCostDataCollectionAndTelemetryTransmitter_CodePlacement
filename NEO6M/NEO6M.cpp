#include "NEO6M.h"
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

NEO6M::NEO6M(){
};

NEO6M::~NEO6M() {
  delete this->SerialGPS;
  this->SerialGPS = nullptr;
}

void NEO6M::setup(int rx_pin, int tx_pin){
  /*
  rx_pin : to which pin in the board the tx of the NEO6M is connected to
  tx_pin : to which pin in the board the rx of the NEO6M is connected to
  */
  this->RX_PIN = rx_pin;
  this->TX_PIN = tx_pin;
  delay(100);
  this->SerialGPS = new SoftwareSerial(this->RX_PIN, this->TX_PIN);
  delay(100);
  this->SerialGPS->begin(9600);
  this->latitude = 0.0;
  this->longitude = 0.0;
}
void NEO6M::read_data(){
  while (this->SerialGPS->available()){
    this->gps.encode(this->SerialGPS->read());
  }

  if (this->gps.location.isValid()){
    this->latitude = this->gps.location.lat();
    this->longitude = this->gps.location.lng();
  }
}


double NEO6M::get_latitude(){
  this->read_data();
  return this->latitude;
}

double NEO6M::get_longitude(){
  this->read_data();
  return this->longitude;
}

