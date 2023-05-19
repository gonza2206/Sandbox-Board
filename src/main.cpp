#include <Adafruit_NeoPixel.h>

#define LED_PIN D6 // define el pin donde está conectado el LED
#define NUM_LEDS 9 // número de LEDs que vamos a usar

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
  strip.begin(); // inicializa la tira de LEDs
  strip.show();  // asegurarse de que los LEDs estén apagados al inicio
  for (int i = 0; i < NUM_LEDS; i++)
  {
    strip.setPixelColor(i, 255, 100, 0); // establece el color del LED en rojo
    strip.show();                        // muestra el color en el LED
    delay(500);                          // espera 500ms
  }
  strip.setPixelColor(0, 0, 100, 0); // establece el color del LED en rojo
  strip.setPixelColor(3, 0, 100, 0); // establece el color del LED en rojo
  strip.setPixelColor(6, 0, 100, 0); // establece el color del LED en rojo

  strip.setPixelColor(1, 0, 0, 255); // establece el color del LED en rojo
  strip.setPixelColor(7, 0, 0, 255); // establece el color del LED en rojo

  strip.setPixelColor(2, 0, 100, 0); // establece el color del LED en rojo
  strip.setPixelColor(5, 0, 100, 0); // establece el color del LED en rojo
  strip.setPixelColor(8, 0, 100, 0); // establece el color del LED en rojo
  strip.show();                      // muestra el color en el LED
}

void loop()
{
  strip.setPixelColor(4, 255, 0, 0); // establece el color del LED en rojo
  strip.show();                      // muestra el color en el LED
  delay(400);
  strip.setPixelColor(4, 0, 0, 0); // establece el color del LED en rojo
  strip.show();                      // muestra el color en el LED
  delay(400);
}
