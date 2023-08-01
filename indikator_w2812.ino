#include <Adafruit_NeoPixel.h>

#define PIN       8
#define NUMPIXELS 8
int inByte = 0;
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {

  // safe guard to prevent not beeing able to reprogram arduino
  // on some arduino types that can happen if serial, keyboard and/or mouse input gets sent to pc constantly directly after boot
  pinMode(LED_BUILTIN, OUTPUT);
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  for (int i = 0; i < 8; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000 - (50 * i));
    digitalWrite(LED_BUILTIN, LOW);
    pixels.setPixelColor(i, pixels.Color(0, i * 30, i * 30));
    pixels.show();
    delay(50 * i);
    if (i == 7) {
      pixels.fill(pixels.Color(0, 255, 255));
      pixels.show();
    }
  }
  {
    Serial.begin(9600);
    Serial.print("Ready");
  }

}


void loop()  {
  if (Serial.available() > 0) {
    inByte = Serial.read();
    if (inByte == '2') { // RU
      for (int i = 0; i < NUMPIXELS; i++) { // For each pixel...
        pixels.setPixelColor(i, pixels.Color(0, 255, 35));
        pixels.show();   // Send the updated pixel colors to the hardware.
      }
      delay(20); // Pause before next pass through loop
    }
    else if (inByte == '1') { // EN
      for (int i = 0; i < NUMPIXELS; i++) { // For each pixel...
        pixels.setPixelColor(i, pixels.Color(255, 0, 30));
        pixels.show();   // Send the updated pixel colors to the hardware.
        delay(20); // Pause before next pass through loop
      }
    }
  }
}
