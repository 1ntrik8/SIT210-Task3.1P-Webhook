/*
 * FILE:        DHT_simple.cpp
 * VERSION:     0.4
 * PURPOSE:     Example that uses DHT library with two sensors
 * LICENSE:     GPL v3 (http://www.gnu.org/licenses/gpl.html)
 *
 * Samples one sensor and monitors the results for long term
 * analysis.  It calls DHT.acquireAndWait
 *
 * Scott Piette (Piette Technologies) scott.piette@gmail.com
 *      January 2014        Original Spark Port
 *      October 2014        Added support for DHT21/22 sensors
 *                          Improved timing, moved FP math out of ISR
 *      September 2016      Updated for Particle and removed dependency
 *                          on callback_wrapper.  Use of callback_wrapper
 *                          is still for backward compatibility but not used
 *                          is still for backward compatibility but not used
 * ScruffR
 *      February 2017       Migrated for Libraries 2.0
 *                          Fixed blocking acquireAndWait()
 *                          and previously ignored timeout setting
 *                          Added timeout when waiting for Serial input
 *
 * With this library connect the DHT sensor to the following pins
 * Spark Core: D0, D1, D2, D3, D4, A0, A1, A3, A5, A6, A7
 * Particle  : any Pin but D0 & A5
 * See docs for more background
 *   https://docs.particle.io/reference/firmware/photon/#attachinterrupt-
 */

#include "PietteTech_DHT.h" 

#define DHTTYPE  DHT22       // Sensor type DHT11/21/22/AM2301/AM2302
#define DHTPIN   D2          // Digital pin for communications
#define LEDPIN   D7

 /*
  * NOTE: Use of callback_wrapper has been deprecated
  */
  //declaration
  //void dht_wrapper(); // must be declared before the lib initialization

  // Lib instantiate
PietteTech_DHT DHT(DHTPIN, DHTTYPE);
int n;      // counter
String data;

void setup()
{
  pinMode(DHTPIN, INPUT);
  pinMode(LEDPIN, OUTPUT);
  DHT.begin();
}

/*
 * NOTE:  Use of callback_wrapper has been deprecated but left in this example
 * to confirm backwards compabibility.
 */
 // This wrapper is in charge of calling
 // must be defined like this for the lib work
 //void dht_wrapper() {
 //    DHT.isrCallback();
 //}

void loop()
{

  int result = DHT.acquireAndWait(1000); // wait up to 1 sec (default indefinitely)

  switch (result) {
  case DHTLIB_OK:
    Serial.println("OK");
    break;
  case DHTLIB_ERROR_CHECKSUM:
    Serial.println("Error\n\r\tChecksum error");
    break;
  case DHTLIB_ERROR_ISR_TIMEOUT:
    Serial.println("Error\n\r\tISR time out error");
    break;
  case DHTLIB_ERROR_RESPONSE_TIMEOUT:
    Serial.println("Error\n\r\tResponse time out error");
    break;
  case DHTLIB_ERROR_DATA_TIMEOUT:
    Serial.println("Error\n\r\tData time out error");
    break;
  case DHTLIB_ERROR_ACQUIRING:
    Serial.println("Error\n\r\tAcquiring");
    break;
  case DHTLIB_ERROR_DELTA:
    Serial.println("Error\n\r\tDelta time to small");
    break;
  case DHTLIB_ERROR_NOTSTARTED:
    Serial.println("Error\n\r\tNot started");
    break;
  default:
    Serial.println("Unknown error");
    break;
  }

  digitalWrite(LEDPIN, HIGH);
  data = String(DHT.getHumidity());
  Particle.publish("readings", data, PRIVATE);
  digitalWrite(LEDPIN, LOW);
  
  delay(15000);
}


