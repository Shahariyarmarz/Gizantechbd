#include "AtmegaHexUploader.h"

#define MSPIM_SCK 18
#define RESET 15
#define BB_MISO 19
#define BB_MOSI 23

AtmegaHexUploader hexUploader(BB_MISO, BB_MOSI);  // Software: MISO, MOSI

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600);

  if (hexUploader.begin(RESET, MSPIM_SCK)) {  // Software: RESET, SCK
    Serial.println("Uploader Started.");
  }
}

void loop() {
  if (Serial2.available()) {
    Serial.print(char(Serial2.read()));
  }

  if (Serial.available()) {
    char data = Serial.read();

    if (data == 'W') {
      if (hexUploader.upload("/test.hex")) {
        Serial.println("Successfully Uploaded Flash.");
      }
    }
    if (data == 'b') {
      if (hexUploader.upload("/test_64.hex")) {
        Serial.println("Successfully Uploaded Flash.");
      }
    }

    if (data == 'f') {
      if (hexUploader.start()) {
        hexUploader.getFuseBytes();
        hexUploader.stop();
      }
    }

    if (data == 's') {
      if (hexUploader.start()) {
        hexUploader.getSignature();
        hexUploader.stop();
      }
    }
  }

  delay(1);
}
