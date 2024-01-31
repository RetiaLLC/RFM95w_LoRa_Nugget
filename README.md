# RFM95w_LoRa_Nugget
LoRa Radio Programs for a USB Nugget paired with a RFM95W module
Radio module: https://www.amazon.com/Lubeby-Smart-Original-915Mhz-Transceiver/dp/B0BHLK9FC9
USB Nugget: https://retia.io/products/wi-fi-nugget-s2-nugget-esp32s2

Using modified examples from this guide: https://randomnerdtutorials.com/esp32-lora-rfm95-transceiver-arduino-ide/

To make this work on a USB Nugget, I defined custom SPI pins.

#define SCK 15
#define MISO 17
#define MOSI 21

These are the pins on the USB Nugget I connected the module to:

#define ss 4
#define rst 14
#define dio0 2

I also used a Nugget Breakout Board for easy wiring: https://retia.io/products/usb-nuget-breadboard-tail-breakout

If you wire yours *exactly* the same way: 
try it out on your own USB Nugget by flashing the compiled binary on Nugget.dev
