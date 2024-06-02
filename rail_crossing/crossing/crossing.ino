

// #define SENSOR1 2
// #define BUZZER1 3
// #define GREEN1 4
// #define RED1 5

// #define SENSOR2 8
// #define BUZZER2 9
// #define GREEN2 10
// #define RED2 11

int sensor[] = {2, 8};
int buzzer[] = {3, 9};
int green[] = {4, 10};
int red[] = {5, 11};

int Duration = 15000;
int freq1 = 1000, freq2 = 1500;

void setup()
{
  for (int i = 0; i < 2; i++)
  {
    pinMode(sensor[i], INPUT);
    pinMode(buzzer[i], OUTPUT);
    pinMode(green[i], OUTPUT);
    pinMode(red[i], OUTPUT);
  }
}

void loop()
{
  senseTrigger(0, Duration);
  senseTrigger(1, Duration);
}

void senseTrigger(int number, int duration)
{
  if (digitalRead(sensor[number])==1)
  {
    digitalWrite(green[number], LOW);
    for (int i = 0; i <int(duration/1200); i++)
    {
      tone(buzzer[number], freq1);
      digitalWrite(red[number], HIGH);
      delay(600);
      noTone(buzzer[number]);
      tone(buzzer[number], freq2);
      digitalWrite(red[number], LOW);
      delay(600);
      noTone(buzzer[number]);
    }
    digitalWrite(green[number], HIGH);
  }
  else {
    digitalWrite(green[number], HIGH);
  }
}