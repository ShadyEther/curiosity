#include <Servo.h>  //in-built Servo library
#include <string.h> //in-built String library

int delay_time = 30; // default delay time for motor speed
int step = 1;        // delay step value for motor speed

Servo servos[5];                    // array of servo joints
int pos[5] = {10, 60, 40, 90, 100}; // array for holding joint servo's positions

int resetPin = 12; // resetPin connected at pin 12 of arduino

int baudRate = 9600; // default baudrate for HC-05

void setup()
{
    Serial.begin(baudRate);

    while (!Serial)
        ; // wait infinitely for Serial port to connected

    Serial.println("Arduino connected at: "+String(baudRate)+" baudRate");

    while (Serial.available() > 0)
        Serial.read(); // clear the Serial input stream

    Serial.flush(); // clear the Serial output stream

    servos[0].attach(3);
    servos[1].attach(5);
    servos[2].attach(6);
    servos[3].attach(9);
    servos[4].attach(10);

    for (int i = 0; i < 5; i++)
        servos[i].write(pos[i]); // setitng servos to their initial position...needed for speed calculation

    digitalWrite(resetPin, HIGH); // RESET pin configuration
    pinMode(resetPin, OUTPUT);
}

void loop()
{
    driver();    // driver function called
    delay(100); // delay of 100ms is provided after every command is performed.
}

void driver()
{
    String input_command = "", input_String = "";
    int input_value = 0;

    if (Serial.available()) // checking if there is something in the Serial input stream
    {
        input_command = Serial.readString();                // reads the whole command from the input
        input_value = (input_command.substring(1)).toInt(); // get the substring starting from index 1 to end and convert it to int

        switch (input_command[0]) // the first letter of the input command is used for checking the cases.
        {
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

        case 'T':
            delay_time = input_value;
            Serial.println("Set delay to: " + String(delay_time));
            break;

        case 'S':
            step = input_value;
            Serial.println("Set step value to: " + String(step));
            break;

        case 'R':
            Serial.println("Resetting Arduino...");
            delay(1000);
            digitalWrite(resetPin, LOW);
            break;

        case 'P':
            Serial.println("Running Preprogrammed Movement...");
            while (!Serial.available())
            {
                moveServo(10, 4); // ROTATING

                moveServo(90, 0); // OPENING CLAWS

                moveServo(23, 3); // GOING DOWN
                moveServo(155, 1);
                moveServo(66, 2);

                moveServo(30, 0); // GRIPPING

                moveServo(60, 1); // GOING UP
                moveServo(75, 3);

                moveServo(169, 4); // ROTATE

                moveServo(23, 3); // GOING DOWN
                moveServo(155, 1);

                moveServo(90, 0); // RELEASING

                moveServo(60, 1); // GOING UP
                moveServo(75, 3);

                moveServo(10, 0); // CLOSING CLAWS
            }
            break;

        case 'M':
            Serial.println("Entering Manual Mode...");
            break;

        default:
            Serial.println("Wrong Command!");
        }
    }
}

void moveServo(int angle, int tag)
{
    if (angle < 10 || angle > 169)
    {
        Serial.println("Angle out of range!");
    }
    else
    {
        Serial.println("Turning joint " + String(tag) + " from " + String(pos[tag]) + " to " + String(angle) + " degree.");

        if (pos[tag] > angle)
        {
            for (int i = pos[tag]; i >= angle; i -= step)
            {
                pos[tag] = i;

                servos[tag].write(i);
                delay(delay_time);
            }
        }

        else if (pos[tag] < angle)
        {
            for (int i = pos[tag]; i <= angle; i += step)
            {
                pos[tag] = i;

                servos[tag].write(i);
                delay(delay_time);
            }
        }

        else
            ;
    }
}
