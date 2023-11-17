#include <Arduino.h>
#include <Wire.h>
#include <EEPROM_24LC32A_I2C.h>
#include <MuxController.hpp>
#include <Adafruit_NeoPixel.h>

#define PIN            4  // Pin al que están conectados los LEDs WS2812B
#define NUM_LEDS       30  // Número de LEDs en la tira

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);


#define s0_gnd 14
#define sig_gnd 25
#define sig_vcc 26
#define s0_vcc 27
EEPROM_24LC32A_I2C gamePiece(0x50);

// Función para llenar toda la tira con un color sólido
void colorWipe(uint32_t color, int wait) {
  for(int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
    strip.show();
    delay(wait);
  }
}
void setup()
{

  // pinMode(s0_gnd, OUTPUT);
  // pinMode(sig_gnd, OUTPUT);
  // pinMode(sig_vcc, OUTPUT);
  // pinMode(s0_vcc, OUTPUT);

  // Serial.begin(115200);
  // Wire.begin(); // Iniciar la comunicación I2C
  // char str_data[] = {"DOS"};
  // // eprom.write(0,str_data);
  //  //gamePiece.writeEEPROM(0,str_data);
  // // vcc_mux.write(0, HIGH);
  // delay(100);
  // digitalWrite(sig_gnd, HIGH); // Configura el pin 23 en HIGH
  // digitalWrite(s0_gnd, HIGH); // Configura el pin 26 en HIGH
  // gamePiece.readDataFromEEPROM();
    strip.begin();
  strip.show();  // Inicializa todos los LEDs en apagado
}

void loop()
{
    // Ejemplo de cambio de color en todos los LEDs
  colorWipe(strip.Color(255, 0, 0), 50);  // Rojo
  delay(500);
  colorWipe(strip.Color(0, 255, 0), 50);  // Verde
  delay(500);
  colorWipe(strip.Color(0, 0, 255), 50);  // Azul
  delay(500);
  // //Activamos la columna 0 del mux gnd
  // digitalWrite(s0_vcc, LOW);
  // //Energizamos la columna 0 
  // digitalWrite(sig_vcc, HIGH);
  // delay(2000);
  // gamePiece.readDataFromEEPROM();
  // digitalWrite(sig_vcc, LOW);
  // //Activamos la columna 1 del mux gnd
  // digitalWrite(s0_vcc, HIGH);
  // digitalWrite(sig_vcc, HIGH);
  // delay(2000);
  // gamePiece.readDataFromEEPROM(); //LEEMOS otra EEPROM
  // delay(2000);
}