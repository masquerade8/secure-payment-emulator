// Final Code to Check Valid UID + Secure Authentication using Challenge-Response

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9
#define SS_PIN 10

MFRC522 mfrc522(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;

byte block = 4;
byte secretKey[4];     // Will be read from card
byte challenge[4];     // Random
byte response[4];      // Result of XOR

const int numValidCards = 3;
String validCardUIDs[numValidCards] = {
  "F215EC1B",
  "04B072CA473C80",
  "12345678"
};

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Scan your card for secure authentication...");

  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;  // default key
  randomSeed(analogRead(0)); // seed random generator
}

void loop() {
  if (!mfrc522.PICC_IsNewCardPresent()) return;
  if (!mfrc522.PICC_ReadCardSerial()) return;

  // Get UID as string
  String scannedUID = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    scannedUID += String(mfrc522.uid.uidByte[i], HEX);
  }
  scannedUID.toUpperCase();

  // Check if UID is valid
  bool isValidCard = false;
  for (int i = 0; i < numValidCards; i++) {
    if (scannedUID == validCardUIDs[i]) {
      isValidCard = true;
      break;
    }
  }

  if (!isValidCard) {
    Serial.print("Invalid Card UID: "); Serial.println(scannedUID);
    Serial.println("Access Denied ❌\n--------------------------");
    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
    delay(3000);
    return;
  }

  Serial.print("Valid UID: "); Serial.println(scannedUID);

  // Authenticate block 4
  MFRC522::StatusCode status;
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print("Auth failed: "); Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  byte buffer[18];
  byte size = sizeof(buffer);

  status = mfrc522.MIFARE_Read(block, buffer, &size);
  if (status != MFRC522::STATUS_OK) {
    Serial.print("Read failed: "); Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  // Extract secret key from card
  for (int i = 0; i < 4; i++) {
    secretKey[i] = buffer[i];
  }

  // Generate challenge and response
  for (int i = 0; i < 4; i++) {
    challenge[i] = random(0, 256);
    response[i] = challenge[i] ^ secretKey[i];
  }

  // Display results
  Serial.print("Secret Key: ");
  for (int i = 0; i < 4; i++) Serial.print(secretKey[i], HEX); Serial.println();

  Serial.print("Challenge: ");
  for (int i = 0; i < 4; i++) Serial.print(challenge[i], HEX); Serial.println();

  Serial.print("Response: ");
  for (int i = 0; i < 4; i++) Serial.print(response[i], HEX); Serial.println();

  Serial.println("Access Granted ✅");
  Serial.println("--------------------------");

  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
  delay(3000);
}
