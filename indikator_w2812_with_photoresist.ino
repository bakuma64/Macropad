#include <Adafruit_NeoPixel.h>

#define PIN       8
#define NUMPIXELS 8
#define PIN_PHOTO_SENSOR A0
int inByte = 0;
int r = 0;
int g = 0;
int b = 0;



Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  int val = analogRead(PIN_PHOTO_SENSOR);
  int new_bright = map(val, 20, 900, 10, 230);
  pixels.setBrightness(200 - new_bright);

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
      r = 0;
      g = 255;
      b = 255;
      pixels.fill(pixels.Color(r, g, b));
      pixels.show();
    }
  }
  {
    Serial.begin(9600);
    Serial.print("Ready");
  }

}


void loop()  {
  int val = analogRead(PIN_PHOTO_SENSOR);
  //Serial.println(val);
  //Serial.println(ledPower);
  // analogWrite(PIN, ledPower);
  pixels.setPixelColor(8, pixels.Color(r, g, b));
  int new_bright = map(val, 20, 900, 0, 255);
  pixels.setBrightness(265 - new_bright);
  pixels.show();   // Send the updated pixel colors to the hardware.

  if (Serial.available() > 0) {
    inByte = Serial.read();
    if (inByte == '2') { // RU
      for (int i = 0; i < NUMPIXELS; i++) { // For each pixel...
        r = 0;
        g = 255;
        b = 35;
        pixels.setPixelColor(i, pixels.Color(r, g, b));
       // int new_bright = map(val, 20, 900, 10, 230);
       // pixels.setBrightness(200 - new_bright);
        pixels.show();   // Send the updated pixel colors to the hardware.
      }
      delay(20); // Pause before next pass through loop
    }
    else if (inByte == '1') { // EN
      for (int i = 0; i < NUMPIXELS; i++) { // For each pixel...
        r = 255;
        g = 0;
        b = 35;
        pixels.setPixelColor(i, pixels.Color(r, g, b));
        pixels.show();   // Send the updated pixel colors to the hardware.
        delay(20); // Pause before next pass through loop
      }
    }
  }
}
