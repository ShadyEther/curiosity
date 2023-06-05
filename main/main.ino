#include<Servo.h>
#include<string.h>
// typedef struct servos{
//     Servo motor;
//     int pos;
// }SERVO;
int delay_time=15;//default delay time for motr speed
int step=1;//delay step value for motor speed

Servo servos[5];//array of servo joints
int pos[5]={10,50,90,100,80};//array for holding joint servos positions

int baudRate=9600;//default baudrate

void setup(){
    // Serial.begin(baudRate);
    Serial.begin(9600);
    while(!Serial);//wait infinitely for Serial port to connect
    Serial.print("Serial port connected at: " + String(baudRate));
    // Serial.print("Serial port connected at: ");
    servos[0].attach(3);
    servos[1].attach(5);
    servos[2].attach(6);
    servos[3].attach(9);
    servos[4].attach(10);
    for(int i=0;i<5;i++)
        servos[i].write(pos[i]);
}

void loop(){
  // Serial.print("Loop running");
  driver();
  delay(1000);
}

void driver(){
    String input_command="",input_String="";
    int input_value=0;
    if(Serial.available()){
      // input_String=Serial.readString(); 
        input_command=Serial.readString();//reads the whole command from the input
        input_value=(input_command.substring(1)).toInt();//get the substring starting from index 1 to end and convert it to int
        Serial.println(input_command);
        Serial.println(input_command.substring(1));
        Serial.println(input_value);
        switch(input_command[0]){
            case 'A':moveServo(input_value,0);
                      break;

            case 'B':moveServo(input_value,1);
                      break;

            case 'C':moveServo(input_value,2);
                      break;

            case 'D':moveServo(input_value,3);
                      break;

            case 'E':moveServo(input_value,4);
                      break;

            case 'M':moveWheel(input_value);
                      break;
            
            case 'T':delay_time=input_value;
                      Serial.print("Set delay to: "+String(delay_time));
                      break;

            case 'S':step=input_value;
                      Serial.print("Set step value to: "+String(step));
                      break;

            default:Serial.print("Wrong Command!");
        }
    }
}

void moveServo(int angle,int tag){
    if(angle<10 || angle>169){
        Serial.print("Angle out of range!");
    }
    else{
        Serial.print("Turning joint "+ String(pos[tag]) +" to "+ String(angle) +" degree.");
        if(pos[tag]>angle){
          for(int i=pos[tag];i>=angle;i-=step){
            pos[tag]=i;
            // Serial.print("Pos: "+String(pos[tag]));
            servos[tag].write(i);
            delay(delay_time);
          }
        }
        else if(pos[tag]<angle){
          for(int i=pos[tag];i<=angle;i+=step){
            pos[tag]=i;
            // Serial.print("Pos: "+String(pos[tag]));
            servos[tag].write(i);
            delay(delay_time);
          }
        }
        else ;
        }
        
}

void moveWheel(int dir){
  switch(dir){
    case 1:Serial.print("Turning Left");break;

    case 2:Serial.print("Moving Front");break;

    case 3:Serial.print("Turning Right");break;

    case 4:Serial.print("Moving Back");break;
    
    case 5:Serial.print("Stopping!");break;

    default: Serial.print("Wrong Command!");
  }
}
