#include <Arduino.h>
#include <Wire.h>
#include <EEPROM_24LC32A_I2C.h>
#include <MuxController.hpp>
#include <Adafruit_NeoPixel.h>

#define PIN 13          // Pin al que están conectados los LEDs WS2812B
#define NUM_LEDS 30     // Número de LEDs en la tira
#define NUM_REGISTERS 2 // Número de registros en cascada (puedes ajustarlo según tu configuración)

int latchPin = 14; // pin D5 on NodeMCU boards
int clockPin = 0;  // pin D3 on NodeMCU boards
int dataPin = 12;  // pin D6 on NodeMCU
uint8_t leds = 0;  // Variable to hold the pattern of which LEDs are currently turned on or off

int numOfRegisters = 2;
uint8_t *registerState;

long effectId = 0;
long prevEffect = 0;
long effectRepeat = 0;
long effectSpeed = 30;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

EEPROM_24LC32A_I2C gamePiece(0x50);

// Función para llenar toda la tira con un color sólido
void colorWipe(uint32_t color, int wait)
{
  for (int i = 0; i < strip.numPixels(); i++)
  {
    strip.setPixelColor(i, color);
    strip.show();
    delay(wait);
  }
}

void regWrite(int pin, bool state)
{
  int reg = pin / 8;               // Determines register
  int actualPin = pin - (8 * reg); // Determines pin for actual register
  digitalWrite(latchPin, LOW);     // Begin session
  for (int i = 0; i < numOfRegisters; i++)
  {
    uint8_t *states = &registerState[i];
    // Update state
    if (i == reg)
    {
      bitWrite(*states, actualPin, state);
    }
    // Write
    shiftOut(dataPin, clockPin, MSBFIRST, *states);
  }
  digitalWrite(latchPin, HIGH); // End session
}

void setup()
{

  // Initialize array
  registerState = new uint8_t[numOfRegisters];
  for (size_t i = 0; i < numOfRegisters; i++)
  {
    registerState[i] = 0;
  }

  // Set all the pins of 74HC595 as OUTPUT
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

  Serial.begin(115200);
  Wire.begin(); // Iniciar la comunicación I2C
  Wire.setClock(10000);

  // regWrite(14, HIGH);
  regWrite(9, HIGH);
  char str_data[] = {"0000"};

  delay(100);
  // gamePiece.readDataFromEEPROM();
  strip.begin();
  strip.show();                          // Inicializa todos los LEDs en apagado
                                         // Ejemplo de cambio de color en todos los LEDs
  colorWipe(strip.Color(0, 255, 0), 10); // Verde

  leds = 0; // Inicialmente apaga todos los LEDs, dando a la variable 'leds' el valor 0

  delay(500);
}

void loop()
{
  static bool colorSet = false;
  // gamePiece.readDataFromEEPROM();
  // delay(500);
  for (int k = 0; k <= 5; k++)
  {
    regWrite(k, HIGH);
    for (uint8_t i = 8; i <= 15; i++)
    {
      regWrite(i, HIGH);
      char *data = gamePiece.readDataFromEEPROM();
      delay(20);
      regWrite(i, LOW);
    }
    //  // Verifica si la cadena es igual a "DOSR"
    // if (data != nullptr && strcmp(data, "DOSR") == 0 && !colorSet) {
    //   strip.setPixelColor(0, strip.Color(255, 255, 0));
    //   // Tu código adicional si la cadena es igual a "DOSR"
    //       strip.show();
    //       colorSet = true;
    // } else if (data == nullptr  && k == 9 && colorSet){
    //       strip.setPixelColor(0, strip.Color(0, 255, 0));
    //   // Tu código adicional si la cadena es igual a "DOSR"
    //       strip.show();
    //       colorSet = false;
    // }
    delay(100);
    regWrite(k, LOW);
  }
}
