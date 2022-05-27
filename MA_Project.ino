#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN     9
#define SS_PIN      10

MFRC522 mfrc522(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;

void setup() {
  //pinMode(8, OUTPUT);
  Serial.begin(9600);
  while(!Serial);
  SPI.begin();
  mfrc522.PCD_Init();

  for(byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;
  Serial.print('>');
}

void loop() {
  if(!mfrc522.PICC_IsNewCardPresent()) return;
  if(!mfrc522.PICC_ReadCardSerial()) return;

  //digitalWrite(8, HIGH);
  //delay(1000);
  //digitalWrite(8, LOW);
  //delay(1000);

  send_tag_val(mfrc522.uid.uidByte, mfrc522.uid.size);
  delay(1000);
}

void send_tag_val(byte *buffer, byte bufferSize) {
  Serial.print("ID:");
  for(byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i], DEC);
    Serial.print(" ");
  }
  Serial.println(0, DEC);
  Serial.print('>');
}
