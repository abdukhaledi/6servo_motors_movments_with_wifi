# 4th-project
![Screenshot (461)](https://user-images.githubusercontent.com/85647212/124886838-4ac31f00-dfdd-11eb-83af-a0e2db8a1123.png)

This robot :robot: designed and programmed using Arduino to controll robot arm with 6 servo motors, ultrasonic sensor to detect objects, and Wifi module to send and recive  data from the server.

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

