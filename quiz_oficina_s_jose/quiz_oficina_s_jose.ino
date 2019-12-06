
const int button1Pin = 2;
const int button2Pin = 3;
const int button3Pin = 4;
const int button4Pin = 5;
const int tomada1 = 12;
const int tomada2 = 10;
const int tomada3 = 11;
const int tomada4 = 13;

int button1State;
int button2State;
int button3State;
int button4State;

void setup() {
  Serial.begin(9600);
  pinMode(tomada1, OUTPUT);
  pinMode(tomada2, OUTPUT);
  pinMode(tomada3, OUTPUT);
  pinMode(tomada4, OUTPUT);
  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);
  pinMode(button3Pin, INPUT_PULLUP);
  pinMode(button4Pin, INPUT_PULLUP);
}

bool isAnyButtonPressed(){
  return (button1State || button2State || button3State || button4State);
}


void loop() {
  
  button1State = digitalRead(button1Pin);
  button2State = digitalRead(button2Pin);
  button3State = digitalRead(button3Pin);
  button4State = digitalRead(button4Pin);
  
  Serial.print((button1State == HIGH) ? "HIGH" : "LOW");
  Serial.print("\t");
  Serial.print((button2State == HIGH) ? "HIGH" : "LOW");
  Serial.print("\t");
  Serial.print((button3State == HIGH) ? "HIGH" : "LOW");
  Serial.print("\t");
  Serial.print((button4State == HIGH) ? "HIGH" : "LOW");
  Serial.print("\n");

  // check if the pushbutton is pressed (LOW in our case).
  while (button1State == LOW){
    digitalWrite(tomada1, LOW);
    button1State = digitalRead(button1Pin);
  }
  while (button2State == LOW){
    digitalWrite(tomada2, LOW);
    button2State = digitalRead(button2Pin);
  }
  while (button3State == LOW){
    digitalWrite(tomada3, LOW);
    button3State = digitalRead(button3Pin);

  }
  while (button4State == LOW){
    digitalWrite(tomada4, LOW);
    button4State = digitalRead(button4Pin);
  }
  
  digitalWrite(tomada1, HIGH);
  digitalWrite(tomada2, HIGH);
  digitalWrite(tomada3, HIGH);
  digitalWrite(tomada4, HIGH);

}
