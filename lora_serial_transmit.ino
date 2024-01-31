#include <SPI.h>
#include <LoRa.h>
#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

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

// Define SH1106 display dimensions and address
#define OLED_RESET    -1
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64
#define OLED_ADDR     0x3C  // Adjust if needed

Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
    // Initialize Serial Monitor
    Serial.begin(115200);
    while (!Serial); // Wait for Serial port to connect
    Serial.println("LoRa Sender");

    // Initialize SPI with custom pins
    SPI.begin(SCK, MISO, MOSI, ss);

    // Setup LoRa transceiver module
    LoRa.setPins(ss, rst, dio0);
    while (!LoRa.begin(915E6)) {
        Serial.println(".");
        delay(500);
    }

    // Set the LoRa radio's sync word
    LoRa.setSyncWord(0xF3);
    Serial.println("LoRa Initializing OK!");

    // Initialize NeoPixel
    pixels.begin();
    pixels.setPixelColor(0, pixels.Color(0, 0, 255)); // Blue color on boot
    pixels.show();
    delay(1000);

    // Initialize the SH1106 display
    if(!display.begin(OLED_ADDR, OLED_RESET)) {  
        Serial.println(F("SH1106 allocation failed"));
        for(;;); // Don't proceed, loop forever
    }
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(0,0);
    display.display();
    delay(2000);

    Serial.println("Type a message and press enter to send via LoRa:");
}

void loop() {
    if (Serial.available()) {
        // Turn NeoPixel red when transmitting
        pixels.setPixelColor(0, pixels.Color(255, 0, 0));
        pixels.show();

        String message = Serial.readStringUntil('\n');

        // Display message on SH1106
        display.clearDisplay();
        display.setCursor(0, 0);
        display.println("Transmitting: ");
        display.println(message);
        display.display();

        Serial.print("Sending packet: ");
        Serial.println(message);

        // Send packet via LoRa
        LoRa.beginPacket();
        LoRa.print(message);
        LoRa.endPacket();

        // Turn off the NeoPixel
        pixels.setPixelColor(0, pixels.Color(0, 0, 0));
        pixels.show();

        delay(1000); // Delay after sending message
    }
}
