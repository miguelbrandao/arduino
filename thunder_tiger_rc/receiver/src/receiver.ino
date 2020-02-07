#include <Servo.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

typedef struct data
{
  int acc;
  int dir;
} Data;

#define LED_PIN 13

/************   RADIO VARIABLES   ************/

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

/************   SERVO VARIABLES   ************/
// DIR calibrated
#define ACC_PIN 9
#define ACC_MIN 600
#define ACC_MAX 2400

// DIR calibrated
#define DIR_PIN 10
#define DIR_MIN 870
#define DIR_MAX 2470

// Range where servos can move (in degrees)
#define ACC_MIN_POS 21
#define ACC_MAX_POS 60
#define DIR_MIN_POS 57
#define DIR_MAX_POS 115

Servo acc_servo;
Servo dir_servo;
Data data;

long acc_pos = 0;
long dir_pos = 0;

// Number of degrees of movement per servo
long acc_range;
long dir_range;

unsigned long last_reception_millis;
unsigned long now;

/************   SETUP CODE   ************/

void servo_start_pos()
{
  acc_servo.write(47);
  dir_servo.write(89);
}

void servo_setup()
{
  acc_range = ACC_MAX_POS - ACC_MIN_POS;
  dir_range = DIR_MAX_POS - DIR_MIN_POS;
  acc_servo.attach(ACC_PIN, ACC_MIN, ACC_MAX);
  dir_servo.attach(DIR_PIN, DIR_MIN, DIR_MAX);
  // Servos at starting position
  servo_start_pos();
  delay(1000);
}

void radio_setup()
{
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void setup()
{
  Serial.begin(115200);
  servo_setup();
  radio_setup();
}

/************   ACTUAL CODE   ************/

void failsafe()
{
  now = millis();
  if (now - last_reception_millis > 2000)
  {
    servo_start_pos();
    delay(2000);
  }
}

void radio_receive()
{
  if (radio.available())
  {
    radio.read(&data, sizeof(Data));
    last_reception_millis = millis();
    Serial.print("ACC: ");
    Serial.print(abs(data.acc-1023));
    // Serial.print(data.acc);
    Serial.print("    DIR: ");
    Serial.println(abs(data.dir-1023));
    // Serial.println(data.dir);
  }
  else
  {
    failsafe();
  }
}

void value_conversion()
{
  // prevent division by 0
  long aux_acc = acc_range * abs(data.acc-1023);
  long aux_dir = dir_range * abs(data.dir-1023);
  if (aux_acc != 0)
    aux_acc = aux_acc / 1023;
  if (aux_dir != 0)
    aux_dir = aux_dir / 1023;

  acc_pos = aux_acc + ACC_MIN_POS;
  dir_pos = aux_dir + DIR_MIN_POS;
}

void servo_update()
{
  acc_servo.write(acc_pos);
  Serial.println(acc_pos);
  dir_servo.write(dir_pos);
  //delay(2000);
}

void loop()
{
  radio_receive();
  value_conversion();
  servo_update();
}
