#include <SHA256.h>

#define HASH_SIZE 32

struct HashTest
{
  const char *name;
  byte key[32];
  byte ciphertext[96];
  byte data[16];
};

static HashTest const SHA256Test = {
  "SHA256-hash",
  {0x37, 0x4C, 0x33, 0x53, 0x77, 0x53, 0x71, 0x61,
  0x34, 0x4D, 0x6E, 0x4D, 0x69, 0x50, 0x5A, 0x44,
  0x53, 0x55, 0x46, 0x78, 0x52, 0x79, 0x56, 0x65,
  0x74, 0x6B, 0x41, 0x63, 0x53, 0x47, 0x75, 0x4E},
  {0x81, 0xF9, 0x58, 0xA4, 0xD3, 0x65, 0xAC, 0xCC, 
  0xB9, 0xBE, 0x10, 0x3E, 0x71, 0xD4, 0x94, 0x60, 
  0xD1, 0xCA, 0x81, 0x26, 0xF9, 0xF6, 0xD4, 0x50, 
  0x83, 0xDB, 0xA8, 0xFF, 0xE7, 0x8A, 0x24, 0xC6, 
  0x30, 0xE9, 0xCB, 0x93, 0xB0, 0x30, 0xCA, 0x81, 
  0xC2, 0xD0, 0x26, 0xBC, 0x14, 0x27, 0xDD, 0xF3, 
  0xAC, 0x39, 0x54, 0xF0, 0x81, 0xF3, 0xD7, 0xE0, 
  0xD1, 0xCA, 0xCD, 0xE4, 0x92, 0x41, 0xD0, 0x50, 
  0xEA, 0x96, 0x29, 0x24, 0x22, 0xCB, 0x31, 0xBD, 
  0x34, 0x09, 0x46, 0x91, 0x23, 0x78, 0xD1, 0x4C, 
  0xCC, 0x40, 0x91, 0x84, 0x86, 0x01, 0xA2, 0xED, 
  0xD0, 0xB3, 0xB0, 0x73, 0xBA, 0x31, 0x7E, 0x98},
  {0x41, 0x73, 0x73, 0x6F, 0x63, 0x69, 0x61, 0x74,
  0x65, 0x64, 0x20, 0x64, 0x61, 0x74, 0x61, 0x2E}
};

SHA256 hashAlgorithm;

void performHash(const struct HashTest *test, Hash *hashAlgorithm) {
  unsigned long start, elapsed;
  byte input[sizeof(test->ciphertext) + sizeof(test->data)] = {0}, output[HASH_SIZE] = {0};
  
  memcpy(input, test->ciphertext, 96);
  memcpy(input + 96, test->data, 16);
  Serial.print("Cipher text: \n"); printHex(test->ciphertext, 96); Serial.println();
  Serial.print("Associated data: \n"); 
  for (short i=0; i < 16; i++) {
    Serial.print((char)test->data[i]);
  }
  Serial.println();
  start = millis();
  hashAlgorithm->update(input, sizeof(input));
  hashAlgorithm->finalizeHMAC(test->key, sizeof(test->key), output, sizeof(output));
  elapsed = millis() - start;
  printHex(output, sizeof(output));
  Serial.println(); Serial.print(elapsed); Serial.print(" milliseconds \n");
}

void printHex(const uint8_t *input, size_t len) {
 for (short i=0; i < len; i++) {
    if (i % 8 == 0) {
      Serial.println();
    }
    Serial.print("0x");
    if (input[i] < 16) {
      Serial.print('0'); 
    }
    Serial.print(input[i], HEX);
    if (i+1 != len) {
      Serial.print(", ");
    }
 }
}

void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.print(SHA256Test.name);
  Serial.println();
  performHash(&SHA256Test, &hashAlgorithm);
}

void loop() {
}