#include <Adafruit_NeoPixel.h>
#include <Mux.h>

#define LED_PIN 0  // define el pin donde está conectado el LED
#define NUM_LEDS 2 // número de LEDs que vamos a usar

#define S0 27  // Conectar al pin S0 del HP4067
#define S1 26  // Conectar al pin S1 del HP4067
#define S2 25  // Conectar al pin S2 del HP4067
#define S3 23  // Conectar al pin S3 del HP4067
#define SIG 32 // Conectar al pin SIG del HP4067

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void selectChannel(uint8_t channel)
{
  if (channel < 0 || channel > 15)
    return; // Canal inválido
  digitalWrite(S0, (channel & 0b0001) ? HIGH : LOW);
  digitalWrite(S1, (channel & 0b0010) ? HIGH : LOW);
  digitalWrite(S2, (channel & 0b0100) ? HIGH : LOW);
  digitalWrite(S3, (channel & 0b1000) ? HIGH : LOW);
}

void setup()
{
  
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(SIG, INPUT); // Si deseas escribir en un canal, cambia esto a OUTPUT
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
  for (uint8_t i = 0; i < 16; i++)
  {
    selectChannel(i);
    int value = analogRead(SIG); // Lee el valor analógico del canal seleccionado
    Serial.print("Leyendo canal ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(value);
    delay(300);
  }
}
