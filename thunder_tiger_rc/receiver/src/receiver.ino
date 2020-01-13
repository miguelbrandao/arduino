#include <Servo.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define LED_PIN 13

/************   RADIO VARIABLES   ************/

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";


/************   SERVO VARIABLES   ************/

#define ACC_PIN 9
#define ACC_MIN 800 //not calibrated
#define ACC_MAX 2400 //not calibrated

// DIR calibrado
#define DIR_PIN 10
#define DIR_MIN 870
#define DIR_MAX 2470

Servo acc_servo;
Servo dir_servo;

int pos = 0;


/************   SETUP CODE   ************/

void servo_setup(){
  acc_servo.attach(ACC_PIN,ACC_MIN,ACC_MAX);
  dir_servo.attach(DIR_PIN,DIR_MIN,DIR_MAX);
  // Servos at starting position
  acc_servo.write(0);
  dir_servo.write(90);
  delay(1000);
}

void radio_setup(){
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}


void setup() {
  //servo_setup();
  radio_setup();
}


/************   ACTUAL CODE   ************/

void blink(){

  int blinks = 5;

  for(int i = 0; i<blinks; i++){
    delay(100);
    digitalWrite(LED_PIN,HIGH);
    delay(100);
    digitalWrite(LED_PIN,LOW);
  }
  
  delay(100);

}

void servo_loop(){
  dir_servo.write(0);
  delay(2000);
  dir_servo.write(90);
  delay(1000);
  dir_servo.write(180);
  delay(1000);
  blink();

//  for(pos=0; pos<=180; pos++){
//    acc_servo.write(pos);
//    delay(15);
//  }
//
//  for(pos=180; pos>=0; pos--){
//    acc_servo.write(pos);
//    delay(15);
//  }
}

void radio_loop(){
  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    Serial.println(text);
  }
}

void loop() {
  //servo_loop();
  radio_loop();
}
