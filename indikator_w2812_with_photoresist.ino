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
 val = constrain (val, 80, 450);
  int new_bright = map (val , 80 , 450, 0 , 50);
  new_bright = 150 - new_bright*2;

  new_bright = constrain (new_bright, 15 , 150);
  pixels.setBrightness(new_bright);
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
    Serial.print(new_bright);
  }

}


void loop()  {
  int val = analogRead(PIN_PHOTO_SENSOR);
  //Serial.println(val);
  val = constrain (val, 80, 450);
  int new_bright = map (val , 80 , 450, 0 , 150);
  new_bright = 150 - new_bright*4;

  new_bright = constrain (new_bright, 15 , 150);
  pixels.setBrightness(new_bright);

  //Serial.println(new_bright);
  pixels.show();   // Send the updated pixel colors to the hardware.

  if (Serial.available() > 0) {
    inByte = Serial.read();

    if (inByte == '2') { // RU
      for (int i = 0; i < NUMPIXELS; i++) { // For each pixel...
        r = 0;
        g = 255;
        b = 35;
        pixels.setPixelColor(i, pixels.Color(r, g, b));
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
