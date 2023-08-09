#include <Adafruit_NeoPixel.h>
#include "MuxController.hpp"

#define LED_PIN 0  // define el pin donde está conectado el LED
#define NUM_LEDS 2 // número de LEDs que vamos a usar
#define COL_SIG 32
#define ROW_SIG 21
#define BIT_SIG 34

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
  // column Mux
  pinMode(27, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(COL_SIG, OUTPUT); // Si deseas escribir en un canal, cambia esto a OUTPUT
  // Row Mux
  pinMode(15, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(0, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(ROW_SIG, OUTPUT); // Si deseas escribir en un canal, cambia esto a OUTPUT
  // Bit Mux
  pinMode(17, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(BIT_SIG, INPUT); // Si deseas escribir en un canal, cambia esto a OUTPUT
  Serial.begin(115200);

  strip.begin(); // inicializa la tira de LEDs
  strip.show();  // asegurarse de que los LEDs estén apagados al inicio
  for (int i = 0; i < NUM_LEDS; i++)
  {
    strip.setPixelColor(i, 255, 100, 0); // establece el color del LED en rojo
    strip.show();                        // muestra el color en el LED

    delay(500); // espera 500ms
  }
  strip.setPixelColor(0, 255, 255, 255); // establece el color del LED en rojo
  strip.setPixelColor(3, 255, 255, 255); // establece el color del LED en rojo
  strip.setPixelColor(6, 255, 255, 255); // establece el color del LED en rojo
  strip.setPixelColor(4, 255, 255, 255);
  strip.setPixelColor(1, 255, 255, 255); // establece el color del LED en rojo
  strip.setPixelColor(7, 255, 255, 255); // establece el color del LED en rojo

  strip.setPixelColor(2, 255, 255, 255); // establece el color del LED en rojo
  strip.setPixelColor(5, 255, 255, 255); // establece el color del LED en rojo
  strip.setPixelColor(8, 255, 255, 255); // establece el color del LED en rojo
  strip.setBrightness(255);
  strip.show(); // muestra el color en el LED
}

void loop()
{
  static uint8_t channel = 0;
  row_mux.write(channel);
  for (byte ctrl_pin = 0; ctrl_pin < 3; ctrl_pin++)
  {
    Serial.printf("**********Fila: %i**************\nColumna: %i\n",channel,ctrl_pin);
    ctrl_mux.write(ctrl_pin);
    bit_mux.read();
    Serial.print("\n");
  }
  channel++;
  if (channel>3)
  {
    channel = 0;
  } 
  delay(1000);
}
