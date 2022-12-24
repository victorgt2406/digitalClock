// Data Python - Arduino
#include "data_types.h"
#include "communicator.h"
#include "display.h"

data_t data;
// Display
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#define PIN 6
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(32, 8, PIN,
                                               NEO_MATRIX_TOP + NEO_MATRIX_LEFT +
                                                   NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
                                               NEO_GRB + NEO_KHZ800);

//Sincronator
#include "sincronator.h"
Sincronator sincronator;

Display display = Display(&matrix);
bool serial_update = false;

void setup()
{
  // Data
  Serial.begin(115200);
  // Serial.begin(9600);
  Serial.setTimeout(0.1);

  // Display
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(20);
  display.update_all_data(data);
  matrix.show();

  // Sincronator
  sincronator = Sincronator();
}

void loop()
{
  if(look_serial(&data)){
    display.update_all_data(data);
  }
  if(sincronator.is_half_second()){
    display.update_half_second();
  }

  //display.update_half_second();

  delay(100);
}
