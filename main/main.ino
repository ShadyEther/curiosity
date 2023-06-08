#include <Servo.h>
#include <string.h>
// typedef struct servos{
//     Servo motor;
//     int pos;
// }SERVO;
int delay_time = 30;  //default delay time for motr speed
int step = 1;         //delay step value for motor speed

Servo servos[5];                       //array of servo joints
int pos[5] = { 10, 60, 40, 90, 100 };  //array for holding joint servos positions

int wheelpin[4] = { 2, 4, 7, 8 };  //wheelpins for controlling two motors

int baudRate = 9600;  //default baudrate

void setup() {
  Serial.begin(9600);
  // Serial.begin(9600);
  while (!Serial);  
    //wait infinitely for Serial port to connected
    Serial.println("Serial port connected at: 9600");
  // Serial.println("Serial port connected at: ");
  while(Serial.available()>0) Serial.read();
  Serial.flush();
  servos[0].attach(3);
  servos[1].attach(5);
  servos[2].attach(6);
  servos[3].attach(9);
  servos[4].attach(10);

  for (int i = 0; i < 5; i++)
    servos[i].write(pos[i]);  //setitng servos to their initial position...needed for speed calculation

  for (int i = 0; i < 4; i++)
    pinMode(wheelpin[i], OUTPUT);  //wheelpins set as output
}

void loop() {
  // Serial.println("Loop running");
  driver();
  delay(1000);
}

void driver() {
  String input_command = "", input_String = "";
  int input_value = 0;
  if (Serial.available()) {
    // input_String=Serial.readString();
    input_command = Serial.readString();                 //reads the whole command from the input
    input_value = (input_command.substring(1)).toInt();  //get the substring starting from index 1 to end and convert it to int
    // Serial.println(input_command);
    // Serial.println(input_command.substring(1));
    // Serial.println(input_value);
    switch (input_command[0]) {
      case 'A':
        moveServo(input_value, 0);
        break;

      case 'B':
        moveServo(input_value, 1);
        break;

      case 'C':
        moveServo(input_value, 2);
        break;

      case 'D':
        moveServo(input_value, 3);
        break;

      case 'E':
        moveServo(input_value, 4);
        break;

      case 'M':
        moveWheel(input_value);
        break;

      case 'T':
        delay_time = input_value;
        Serial.println("Set delay to: " + String(delay_time));
        break;

      case 'S':
        step = input_value;
        Serial.println("Set step value to: " + String(step));
        break;

      default: Serial.println("Wrong Command!");
    }
  }
}

void moveServo(int angle, int tag) {
  if (angle < 10 || angle > 169) {
    Serial.println("Angle out of range!");
  } else {
    Serial.println("Turning joint "+String(tag)+" from " + String(pos[tag]) + " to " + String(angle) + " degree.");
    if (pos[tag] > angle) {
      for (int i = pos[tag]; i >= angle; i -= step) {
        pos[tag] = i;
        // Serial.println("Pos: "+String(pos[tag]));
        servos[tag].write(i);
        delay(delay_time);
      }
    } else if (pos[tag] < angle) {
      for (int i = pos[tag]; i <= angle; i += step) {
        pos[tag] = i;
        // Serial.println("Pos: "+String(pos[tag]));
        servos[tag].write(i);
        delay(delay_time);
      }
    } else
      ;
  }
}

void moveWheel(int dir) {
  switch (dir) {
    case 1:
      Serial.println("Turning Left");

      //LEFT=RWFRT+LWBAC
      digitalWrite(wheelpin[0], LOW);
      digitalWrite(wheelpin[1], HIGH);
      digitalWrite(wheelpin[2], LOW);
      digitalWrite(wheelpin[3], HIGH);
      break;

    case 2:
      Serial.println("Moving Front");

      //FRONT=RWFRT+LWFRT
      digitalWrite(wheelpin[0], LOW);
      digitalWrite(wheelpin[1], HIGH);
      digitalWrite(wheelpin[2], HIGH);
      digitalWrite(wheelpin[3], LOW);

      break;

    case 3:
      Serial.println("Turning Right");

      //RIGHT=LWFRT+RWBAC
      digitalWrite(wheelpin[0], HIGH);
      digitalWrite(wheelpin[1], LOW);
      digitalWrite(wheelpin[2], HIGH);
      digitalWrite(wheelpin[3], LOW);


      break;

    case 4:
      Serial.println("Moving Back");
      //BACK=LWBAC+RWBAC
      digitalWrite(wheelpin[0], HIGH);
      digitalWrite(wheelpin[1], LOW);
      digitalWrite(wheelpin[2], LOW);
      digitalWrite(wheelpin[3], HIGH);
      break;

    case 5:
      Serial.println("Stopping!");
      digitalWrite(wheelpin[0], LOW);
      digitalWrite(wheelpin[1], LOW);
      digitalWrite(wheelpin[2], LOW);
      digitalWrite(wheelpin[3], LOW);
      break;

    default: Serial.println("Wrong Command!");
  }
}
//LW BACK
//         digitalWrite(wheelpin[0],LOW);
//         digitalWrite(wheelpin[1],LOW);
//         digitalWrite(wheelpin[2],LOW);
//         digitalWrite(wheelpin[3],HIGH);

//LEFT WHEEL FRONT
// digitalWrite(wheelpin[0],LOW);
// digitalWrite(wheelpin[1],LOW);
// digitalWrite(wheelpin[2],HIGH);
// digitalWrite(wheelpin[3],LOW);

//RIGHT WHEEL FRONT
// digitalWrite(wheelpin[0],LOW);
// digitalWrite(wheelpin[1],HIGH);
// digitalWrite(wheelpin[2],LOW);
// digitalWrite(wheelpin[3],LOW);

//RIGHT WHEEL BACK
// digitalWrite(wheelpin[0],HIGH);
// digitalWrite(wheelpin[1],LOW);
// digitalWrite(wheelpin[2],LOW);
// digitalWrite(wheelpin[3],LOW);
