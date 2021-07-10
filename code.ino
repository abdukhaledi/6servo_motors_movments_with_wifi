// Include the Servo and Wifi library
#include <Servo.h>
#include <SoftwareSerial.h>

// RX | TX
SoftwareSerial ESPserial(0, 1); 

// set initial position
int initial_position;
int cm = 0;
int hold_time = 0;

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
Servo Servo0; // shoulder
Servo Servo1; // shoulder
Servo Servo2; // arm

Servo Servo3; // shoulder
Servo Servo4; // shoulder
Servo Servo5; // arm

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

void loop() {

  // set threshold distance to activate LEDs
  distanceThreshold = 350;
  
  // measure the ping time in cm
  cm = 0.01723 * ultrasonic_distance(12, 13);

  // this loop is for controlling the time before enter the programm
  if (cm < distanceThreshold - 100 && cm > distanceThreshold - 250 && hold_time < 3) 
  {
    hold_time++;
    delay(1000); // not exactly 3 seconds but around 3 seconds
  }
  
  // OFF when object is farther than 250
  if (cm > distanceThreshold) {
    Servo0.write(0);
    Servo1.write(0);
    Servo2.write(0);

    Servo3.write(0);
    Servo4.write(0);
    Servo5.write(0);
    
    hold_time = 0;
  }
  else if (cm < distanceThreshold && cm > distanceThreshold - 100) {
    Servo0.write(0);
    Servo1.write(0);
    Servo2.write(0);

    Servo3.write(0);
    Servo4.write(0);
    Servo5.write(0);
    
    hold_time = 0;
  }
  // ON when objecct is nearer than 250
  else if (cm < distanceThreshold - 100 && cm > distanceThreshold - 250 && hold_time == 3) {
    Servo0.write(100);
    Servo1.write(30);
    Servo2.write(60);

    Servo3.write(100);
    Servo4.write(30);
    Servo5.write(60);
    delay(3000);

    // reply only when you receive data:
    if ( Serial.available() || ESPserial.available() ){
      incomingChar = Serial.read();
      read_input = Serial.write(ESPserial.read());
      if (incomingChar == 'H' || read_input == 'H') { //Happy movment
        Servo0.write(130);
        Servo1.write(30);
        Servo2.write(20);
        Servo3.write(130);
        Servo4.write(30);
        Servo5.write(20);
        delay(500);
        
        for (int i = 0; i < 5; i++) {
  		  Servo2.write(50);
          Servo5.write(50);
          delay(500);
        
          Servo2.write(20);
          Servo5.write(20);
          delay(500);
		}
      }
      else if (incomingChar == 'S' || read_input == 'S') { //Sad movment
        Servo0.write(10);
        Servo1.write(90);
        Servo2.write(90);

        Servo3.write(10);
        Servo4.write(90);
        Servo5.write(90);
        delay(7500);
      }
      else if (incomingChar == 'G' || read_input == 'G') { //Goodbye movment
        Servo0.write(150);
        Servo1.write(130);
        Servo2.write(20);

        Servo3.write(10);
        Servo4.write(10);
        Servo5.write(10);
        delay(500);
        
        for (int i = 0; i < 5; i++) {
  		  Servo2.write(90);
          delay(500);
          Servo2.write(20);
          delay(500);
		}
      }      
    }
  }
}