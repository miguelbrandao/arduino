#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

typedef struct data
{
  int acc;
  int dir;
} Data;

int ledPin = 13;
int joyPinAcc = A0;
int joyPinDir = A1;
Data data;
RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";
Data dataBuf;

/*************  SETUP  *************/

void radio_setup(){
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(joyPinAcc, INPUT);
  pinMode(joyPinDir, INPUT);
  digitalWrite(ledPin, LOW);
  // Serial.begin(115200);
  radio_setup();
}


/*************  CODE  *************/

void radio_send() {
  dataBuf = data;
  radio.write(&dataBuf, sizeof(Data));
}

void serial_print(){
  Serial.print("ACC: ");
  Serial.print(data.acc);
  Serial.print("\t\tDIR: ");
  Serial.println(data.dir);
  Serial.print("\n");
}

 void loop() {
  data.acc = analogRead(joyPinAcc);  
  // this small pause is needed between reading
  // analog pins, otherwise we get the same value twice
  delay(1);            
  data.dir = analogRead(joyPinDir);  
  //serial_print();
  radio_send();
 }