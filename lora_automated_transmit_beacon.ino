#include <SPI.h>
#include <LoRa.h>
#include <Adafruit_NeoPixel.h>

// Define custom SPI pins
#define SCK 15
#define MISO 17
#define MOSI 21

// Define the pins used by the LoRa module
#define ss 4
#define rst 14
#define dio0 2

// Define NeoPixel settings
#define NEOPIXEL_PIN 12
#define NUMPIXELS    1
Adafruit_NeoPixel pixels(NUMPIXELS, NEOPIXEL_PIN);

int counter = 0;

void setup() {
    Serial.begin(115200);
    while (!Serial);
    Serial.println("LoRa Sender");

    SPI.begin(SCK, MISO, MOSI, ss);

    pixels.begin();
    pixels.clear();
    pixels.show();

    LoRa.setPins(ss, rst, dio0);
    while (!LoRa.begin(915E6)) {
        Serial.println(".");
        delay(500);
    }

    LoRa.setSyncWord(0xF3);
    Serial.println("LoRa Initializing OK!");
}

void loop() {
    // Turn NeoPixel red when transmitting
    pixels.setPixelColor(0, pixels.Color(255, 0, 0));
    pixels.show();

    Serial.print("Sending packet: ");
    Serial.println(counter);

    LoRa.beginPacket();
    LoRa.print("hello ");
    LoRa.print(counter);
    LoRa.endPacket();

    delay(1000);

    // Turn off the NeoPixel
    pixels.setPixelColor(0, pixels.Color(0, 0, 0));
    pixels.show();

    counter++;
    delay(9000);
}
