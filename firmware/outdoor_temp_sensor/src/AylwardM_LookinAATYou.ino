/*
 * Project AylwardM_LookinAATYou
 * Description: Give the students experience using the OLED and DHT22 sensors
 * Author: Matt Aylward
 * Date: October 25th, 2018
 */



/*
 * Most of this information was canabalized from the PietteTech_DHT
 * and SparkFunMicroOLED libraries as needed
 */
#include "PietteTech_DHT.h"
#include "SparkFunMicroOLED.h"
#include "math.h"

// Creating Macro
#define DHTTYPE  DHT22       // Sensor type DHT11/21/22/AM2301/AM2302
#define DHTPIN   D1

// dht_wrapper must be called before we initialize the library
void dht_wrapper();

// Library initialization
PietteTech_DHT dht(DHTPIN, DHTTYPE);
MicroOLED oled;

// Variable declaration
float humidity, temperature, tempF, dewPoint;


// Setup runs once
void setup() {
  Serial.begin(300);

  // Displays the first item in the buffer and clears everything
  oled.begin();
  oled.clear(ALL);
  oled.display();
  delay(1000);
}



void loop() {
  // These methods are called every time we loop
  getTempAndHum();
  displayTempAndHum();

  // Delaying one second so the memory doesnt fill up too quickly
  delay(1000);
}



// This method was pulled almost in its entirity from the PietteTech_DHT library
void getTempAndHum(){

  // Makes request from DHT22 sensor and waits for information to be transmitted
  int result = dht.acquireAndWait(1000);

      // These results are required and cannot be deleted or else you will receive an error code
      // Best to just keep it and not need it...
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

  // Several get methods retrieve the information we require
  humidity = dht.getHumidity();
  temperature = dht.getCelsius();
  tempF = ((temperature * 1.8) + 32.0);
  // Dont actually use dew point
  dewPoint = dht.getDewPoint();
}



// // This method does the AAT calculation and displays it on the OLED
// void displayAAT() {
//
//   // The calculation for AAT
//   float aat = temperature + (0.33*((humidity/100) * 6.105 * (pow(M_E, 17.27*temperature/(237.7+temperature))))) - 4.0;
//
//   // Format the value into a string
//   String aatStg = String::format("AAT: %.1f", aat);
//
//   // Clears what the LED had previously on screen
//   oled.clear(PAGE);
//   // Sets the font to the smallest size
//   oled.setFontType(0);
//   // Sets the 'cursor' to the upper left-hand corner where
//   // It will begin drawing the image
//   oled.setCursor(0, 0);
//
//   // Pass AAT value to the println method
//   oled.println(aatStg);
//   // Call display
//   oled.display();
// }



// This method simply displays the temperature and humidity values to the screen
void displayTempAndHum() {

  // Format the values into strings
  String humStg = String::format("Hum: %.1f", humidity);
  String tempStgC = String::format("TC: %.1f", temperature);
  String tempStgF = String::format("TF: %.1f", tempF);

  // Clears what the LED had previously on screen
  oled.clear(PAGE);
  // Sets the font to the smallest size
  oled.setFontType(0);
  // Sets the 'cursor' to the upper left-hand corner where
  // It will begin drawing the image
  oled.setCursor(0, 0);

  // Print the values to the screen and display them
  oled.println(humStg);
  oled.display();
  oled.println(tempStgC);
  oled.display();
  oled.println(tempStgF);
  oled.display();
}
