//NEO 6M GPS wrapper of TinyGPS++ lib
#ifndef NEO6M_H
#define NEO6M_H

#include <SoftwareSerial.h>
#include <TinyGPS++.h>

class NEO6M {
  private:
    TinyGPSPlus gps;
    SoftwareSerial  *SerialGPS;
  public:
    NEO6M();
    ~NEO6M();
    void setup(int rx_pin, int tx_pin);
    void read_data();
    double get_latitude();
    double get_longitude(); 
    int RX_PIN;
    int TX_PIN;
    double latitude;
    double longitude;
};




#endif