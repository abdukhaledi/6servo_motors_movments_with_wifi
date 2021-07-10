# 4th-project
![Screenshot (461)](https://user-images.githubusercontent.com/85647212/125169954-376aac00-e1b5-11eb-99f4-93a77abe4aeb.png)
This robot :robot: designed and programmed using Arduino to controll robot arm with 6 servo motors, ultrasonic sensor to detect objects, and Wifi module to send and recive  data from the server.

# Movment
![Screenshot (463)](https://user-images.githubusercontent.com/85647212/125169896-fbcfe200-e1b4-11eb-965d-c0ad5a41f07c.png)
The goal in this task is to implement design and program the circuit to controll the robot arm based on the object distance and the IoT outcomes.
1. first move "Hello" is when the robot detect an object from 250 cm.
2. robot arm interaction is based to the cutomer's rivew:
   - if the customer was satisfied, "Happy" movment will be implemented.
   - if the customer was disappointed, "Sad" movment will be implemented.
   - if the customer end his rivew, "Goodbye" movment will be implemented.

# Components
* Arduino Uno R3
* Wifi Module (ESP8266)
* Micro Servo **x6**
* Ultrasonic Distance Sensor
* 1 kΩ Resistor **x2**

## Wifi Module (ESP8266)
![image](https://user-images.githubusercontent.com/85647212/124890303-93300c00-dfe0-11eb-8b9d-479d525cd39a.png)

First of all, upload my sample Arduino sketch. Then follow these steps:
* connect VCC Power Pin and Enable Pin to Uno's +3.3V power pin. **IMPORTANT DON'T POWER THE ESP8266 USING 5V PIN.**
* connect ESP's Ground Pin 1K resistor 2x then to Ground Pin.
* connect ESP's TX to Uno's Pin 1
* connect ESP's RX to 1K resistor then to Uno's Pin 0.
* connect ESP's RX to 1K resistor 2x then to Uno's GND Pin.

## servo motor
![image](https://user-images.githubusercontent.com/85647212/124890530-cc687c00-dfe0-11eb-96c6-e920b7d0acb9.png)

Servo motors have three terminals - power, ground, and signal:
* The power wire should be connected to the 5V pin on the Arduino.
* The ground wire should be connected to the ground terminal ofArduino. 
* To protect your Arduino board from damage, you will need some driver IC.
* The signal pin should be connected to Arduino digital pin.

## Ultrasonic Distance Sensor
![image](https://user-images.githubusercontent.com/85647212/124891082-51539580-dfe1-11eb-8f5f-c68ad4f2a97f.png)

Ultrasonic Sensor have four terminals - power, ground, trigger, and echo:
 * The supply voltage of VCC is +5V and should be connected to the 5V pin on the arduino.
 * The ground wire should be connected to the ground terminal ofArduino.
 * you can attach TRIG and ECHO pin to any Digital I/O in your Arduino Board.
 
# Circuit
![Screenshot (462)](https://user-images.githubusercontent.com/85647212/124890848-1e110680-dfe1-11eb-85a8-740098783ca1.png)

The circuit containe: 
* 3 servo motor above for the left robot arm.
* 3 servo motor below for the right robot arm.
* Ultra sonic detector in the right hand side.
* Wifi module on the left hand side.

# Code
Include Servo and Wifi library
```C++
#include <Servo.h>
#include <SoftwareSerial.h>
```
Define the RX and TX pins
```C++
// RX | TX
SoftwareSerial ESPserial(0, 1); 
```
Set variables
```C++
// set initial position
int initial_position;
int cm = 0;

// set threshold distance
int distanceThreshold = 0;

// Read data to position arm
char incomingChar = 0;
char read_input = 0;

// Declare the Servo pin
int servo_pin0 = 3;
int servo_pin1 = 5;
int servo_pin2 = 6;

int servo_pin3 = 9;
int servo_pin4 = 10;
int servo_pin5 = 11;

// Create a servo object
Servo Servo0;
Servo Servo1;
Servo Servo2;

Servo Servo3;
Servo Servo4;
Servo Servo5;
```
Make a function for the ultrasonic
```C++
long ultrasonic_distance(int triggerPin, int echoPin) {
  // Read the trigger pin
  pinMode(triggerPin, OUTPUT);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);

  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);

  // Read the echo pin
  return pulseIn(echoPin, HIGH);
}
```
setup() opject
```C++
void setup() {
  Serial.begin(9600);

  // communication with the host computer
  Serial.begin(115200); 
  
  // Start the software serial for communication with the ESP8266
  ESPserial.begin(115200);
  
  // attach the servo to the used pin number
  Servo0.attach(servo_pin0);
  Servo1.attach(servo_pin1);
  Servo2.attach(servo_pin2);

  Servo3.attach(servo_pin3);
  Servo4.attach(servo_pin4);
  Servo5.attach(servo_pin5);

  // set the initial position on 90 digree
  Servo0.write(0);
  Servo1.write(0);
  Servo2.write(0);

  Servo3.write(0);
  Servo4.write(0);
  Servo5.write(0);
}
```
loop object
```C++
void loop() {
  // listen for communication from the ESP8266 and then write it to the serial monitor
  if (ESPserial.available()) { 
    read_input = Serial.write(ESPserial.read()); 
  }

  // set threshold distance to activate LEDs
  distanceThreshold = 350;
  
  // measure the ping time in cm
  cm = 0.01723 * ultrasonic_distance(12, 13);

  // OFF when object is farther than 250
  if (cm > distanceThreshold) {
    Servo0.write(0);
    Servo1.write(0);
    Servo2.write(0);

    Servo3.write(0);
    Servo4.write(0);
    Servo5.write(0);
  }
  else if (cm < distanceThreshold && cm > distanceThreshold - 100) {
    Servo0.write(0);
    Servo1.write(0);
    Servo2.write(0);

    Servo3.write(0);
    Servo4.write(0);
    Servo5.write(0);
  }
  // ON when objecct is nearer than 250
  else if (cm < distanceThreshold - 100 && cm > distanceThreshold - 250) {
    Servo0.write(180);
    Servo1.write(180);
    Servo2.write(180);

    Servo3.write(180);
    Servo4.write(180);
    Servo5.write(180);
    delay(3000);

    // reply only when you receive data:
    if (Serial.available() > 0) 
    {
      incomingChar = Serial.read();
      if (incomingChar == 'H') { //Happy movment
        Servo0.write(10);
        Servo1.write(100);
        Servo2.write(100);

        Servo3.write(100);
        Servo4.write(100);
        Servo5.write(100);
        delay(5000);
      }
      else if (incomingChar == 'S') { //Sad movment
        Servo0.write(10);
        Servo1.write(10);
        Servo2.write(10);

        Servo3.write(10);
        Servo4.write(10);
        Servo5.write(10);
        delay(5000);
      }
      else if (incomingChar == 'G') { //goodbye movment
        Servo0.write(180);
        Servo1.write(180);
        Servo2.write(180);

        Servo3.write(180);
        Servo4.write(180);
        Servo5.write(180);
        delay(5000);
      }      
    }
  }
}
```

