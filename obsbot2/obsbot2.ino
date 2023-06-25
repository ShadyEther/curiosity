#include <AFMotor.h>
#include <NewPing.h>

#define trigPin A4//pin connection of sensor trig pin
#define echoPin A5//sensor echo pin

int maxDistance = 200;
int maxSpeed = 190; 

  NewPing sonar(trigPin, echoPin, maxDistance);

AF_DCMotor motorL(1);
AF_DCMotor motorR(2);


int distance = 100;//initial value of distance is 100.
int speedSet = 200;

void setup() {//nothing to setup

  motorL.setSpeed(150);
  motorR.setSpeed(180);
  delay(3000);//wait 3s
}

void loop() {
  int distR = 0;//initializes right side distance value
  int distL = 0;//initializes left side distance value
//if obstacle within 15 cm then turn left check distance...turn rigt check distance..compares and moves to path with no obstacles or lesser distance.
  if (distance <= 15) {
    stop();//stops for 200ms
    delay(1000);

    turnLeft();//turnLeft
    distL = readPing();  //read left value
    delay(1000);


    turnRight();//turn right
    delay(1000);
    turnRight();
    distR = readPing();  //read right value
    delay(1000);


    if (distL <= distR) {//compares distance
      moveForward();  //continue right
    } 
    else {
        turnLeft();
        delay(1000);
        turnLeft();
        stop();
        delay(200);

        moveForward();  //continue left
      }
  } 
  else {
    moveForward();  //continue forward
  }
  distance = readPing();//sensoer checks distance for obstacle
  
}



int readPing() {
  delay(100);
  int dist = sonar.ping_cm();

  if (dist == 0) {
    dist = 250;
  }
  return dist;
}

void stop() {
  motorL.run(RELEASE);
  motorR.run(RELEASE);
}

void moveForward() {
  motorL.run(FORWARD);
  motorR.run(FORWARD);
}

void turnLeft(){
  motorL.run(BACKWARD);
  motorR.run(FORWARD);
  delay(400);
  stop();
}

void turnRight(){
  motorL.run(FORWARD);
  motorR.run(BACKWARD);
  delay (400);
  stop();
}
