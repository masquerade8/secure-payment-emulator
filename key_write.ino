// To write the key in the block number 4

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9
#define SS_PIN 10

MFRC522 mfrc522(SS_PIN, RST_PIN);

MFRC522::MIFARE_Key key;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("   Place card");

  // Default Key (factory key)
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;
}

void loop() {
  if (!mfrc522.PICC_IsNewCardPresent()) return;
  if (!mfrc522.PICC_ReadCardSerial()) return;

  byte block = 4;  // block 4 (first data block in sector 1)
  byte dataBlock[] = {0xAB, 0xCD, 0x12, 0x32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  // Authenticate
  MFRC522::StatusCode status;
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print("Auth failed: "); Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  // Write
  status = mfrc522.MIFARE_Write(block, dataBlock, 16);
  if (status != MFRC522::STATUS_OK) {
    Serial.print("Write failed: "); Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  Serial.println("Secret key written to card!");

  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
  delay(3000);
}
