#include <AFMotor.h>
#include <NewPing.h>

#define TRIG_PIN A4
#define ECHO_PIN A5

#define BUZZER 9
#define LED 10

#define MAX_DISTANCE 200
#define MAX_SPEED 50 // Sets speed of DC motors
#define MAX_SPEED_OFFSET 5

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

AF_DCMotor motor1(1); // First motor to connection 1

boolean goesForward = false;

int distance = 100; // Define an int for distance and speed
int speedSet = 0;

int duration=500

void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
}

void loop()
{
  delay(40);

  if (distance <= 10)
  {
    soundHorn(duration);
    flashLED(duration);
    moveStop();
    delay(100);
  }
  else if (distance <= 30)
  {
    soundHorn();
    flashLED();
    moveForward();
    delay(100);
  }
  else if (distance <= 90)
  {
    soundHorn(duration);
    flashLED(duration);
    moveForward()
    delay(100);
  }
  else{
    moveForward();
  }
  distance = readPing();
}


int readPing()
{
  delay(70);
  int cm = sonar.ping_cm();

  if (cm == 0)
  {
    cm = 250;
  }

  return cm;
}

void moveStop()
{
  for (speedSet = MAX_SPEED; speedSet > 0; speedSet -= MAX_SPEED_OFFSET)
    {
      motor.setSpeed(speedSet);
      delay(5);
    }
  motor.run(RELEASE);
  goesForward = false;
}

void moveForward()
{
  if (goesForward==false)
  {
    goesForward = true;
    motor.setSpeed(0);
    motor.run(FORWARD);
    // Slowly bring up speed to avoid loading down
    // batteries too quickly
    for (speedSet = 0; speedSet < MAX_SPEED; speedSet += MAX_SPEED_OFFSET)
    {
      motor.setSpeed(speedSet);
      delay(5);
    }
  }
}


void soundHorn(int duration){
  digitalWrite(BUZZER, HIGH);
  delay(duration);
  digitalWrite(BUZZER,LOW);
  delay(duration);
}

void flashLED(int duration){
  digitalWrite(LED, HIGH);
  delay(duration);
  digitalWrite(LED, LOW);
  delay(duration);
}
  

