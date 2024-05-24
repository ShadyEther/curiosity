




#define SENSOR1 2
#define BUZZER1 3
#define GREEN1 4
#define RED1 5

#define SENSOR2 8
#define BUZZER2 9
#define GREEN2 10
#define RED2 11



void setup() {
  pinMode(SENSOR1, INPUT);
  pinMode(SENSOR2, INPUT);
  pinMode(BUZZER1, OUTPUT);
  pinMode(BUZZER2, OUTPUT);
  pinMode(GREEN1, OUTPUT);
  pinMode(GREEN2, OUTPUT);
  pinMode(RED1, OUTPUT);
  pinMode(RED2, OUTPUT);
}

void loop() {
  tone(BUZZER1,700);
  delay(700);
  noTone(BUZZER1);
  delay(1);
  tone(BUZZER1,500);
  delay(700);
  noTone(BUZZER1);
  delay(1);

}
