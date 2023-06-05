#include <Servo.h>
Servo servo1;
int pos = 10;
int delay_time = 15;
int step = 1;

void setup()
{

    Serial.begin(9600);
    while (!Serial);
    servo1.attach(9);
    servo1.write(10);
}

void loop()
{
    moveServo();
}

void moveServo()
{
    if (Serial.available())

    {
        int state = Serial.parseInt();

        if (state < 10)

        {
            Serial.print(">");
            Serial.println(state);
            Serial.println("cannost   execute command, too low number");
        }

        if (state >= 10 && state < 170)
        {
            Serial.print(">");
            Serial.println(state);
            Serial.print("turning servo   to ");
            Serial.print(state);
            Serial.println(" degrees");
            turnToAngle(state);
        }
    }
}

void turnToAngle(int angle)
{
    if (angle > pos)
    {
        for (int i = pos; i <= angle; i = i + step)
        {
            pos = i;
            servo1.write(i);
            delay(delay_time);
        }
    }
    else if (angle < pos)
    {
        for (int i = pos; i >= angle; i = i - step)
        {
            pos = i;
            servo1.write(i);
            delay(delay_time);
        }
    }
    else
    {
      servo1.write(pos);
    }
}
