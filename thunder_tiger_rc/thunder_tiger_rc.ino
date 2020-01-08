#include <Servo.h>

#define ACC_PIN 9
#define ACC_MIN 800
#define ACC_MAX 2400


// DIR calibrado
#define DIR_PIN 9
#define DIR_MIN 870
#define DIR_MAX 2470

Servo dir_servo;

int pos = 0;

void setup() {
  dir_servo.attach(DIR_PIN,DIR_MIN,DIR_MAX);
}

void blink(){

  int blinks = 5;

  for(int i = 0; i<5; i++){
    delay(100);
    digitalWrite(13,HIGH);
    delay(100);
    digitalWrite(13,LOW);
  }
  
  delay(100);

}

void loop() {

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
