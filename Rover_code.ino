#include<SoftwareSerial.h>
#include<AFMotor.h>
#include<OneWire.h>
#include<DallasTemperature.h>
#include<Servo.h>
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
#define sensorPower 7
#define sensorPin A0
AF_DCMotor motor1(1); // front left 
AF_DCMotor motor2(2); // back left
AF_DCMotor motor3(3); // back right
AF_DCMotor motor4(4); // front right 

/* Create object named bt of the class SoftwareSerial */ 
SoftwareSerial bt(13,9); /* (Rx,Tx) */	
char curr = '0', prev = '0';
char dummy = 'a';
int state = 0;
Servo myservo;
void setup() {
  bt.begin(9600);	/* Define baud rate for software serial communication */
  Serial.begin(9600);	/* Define baud rate for serial communication */
  pinMode(sensorPower,OUTPUT);
  digitalWrite(sensorPower,LOW);
  sensors.begin();
  myservo.attach(10);
}

void loop() {

    motor1.setSpeed(75);
    motor2.setSpeed(75);
    motor3.setSpeed(75);
    motor4.setSpeed(75);
    Serial.print("Moisture is: ");
    Serial.println(readSensor());
    delay(1000);
    sensors.requestTemperatures();
    Serial.print("Temperature is(C): ");
    Serial.println(sensors.getTempCByIndex(0));
    bt.print("Moisture is: ");
    bt.println(readSensor());
    delay(1000);
    sensors.requestTemperatures();
    bt.print("Temperature is(C): ");
    bt.println(sensors.getTempCByIndex(0));
    if (bt.available())	/* If data is available on serial port */
    {
      curr = bt.read();
      dummy = curr;
      motor1.run(RELEASE);
      motor2.run(RELEASE);
      motor3.run(RELEASE);
      motor4.run(RELEASE);
     // wheel mechanism, pattern searching conditional hierarchy
     if(curr == '1' && prev == '1') {
      motor1.run(FORWARD);
      motor2.run(FORWARD);
      motor3.run(FORWARD);
      motor4.run(FORWARD);
      Serial.write("forward \n");

      delay(10);

     }
     else if(curr == '1' && prev == '3') {
      motor1.setSpeed(50);
      motor2.setSpeed(50);
      motor3.setSpeed(25);
      motor4.setSpeed(25);
      motor1.run(FORWARD);
      motor2.run(FORWARD);
      motor3.run(FORWARD);
      motor4.run(FORWARD);
      state = 2; // forward right
      Serial.write("forward right \n");
     }
     else if(curr == '3' && prev == '1') {
      motor1.setSpeed(50);
      motor2.setSpeed(50);
      motor3.setSpeed(25);
      motor4.setSpeed(25);
      motor1.run(FORWARD);
      motor2.run(FORWARD);
      motor3.run(FORWARD);
      motor4.run(FORWARD);
      state = 2; // forward right
      Serial.write("forward right \n");
      delay(10);
      motor1.run(RELEASE);
      motor2.run(RELEASE);
      motor3.run(RELEASE);
      motor4.run(RELEASE);

     }

     else if(curr == '1' && prev == '4') {
      motor1.setSpeed(25);
      motor2.setSpeed(25);
      motor3.setSpeed(50);
      motor4.setSpeed(50);
      motor1.run(FORWARD);
      motor2.run(FORWARD);
      motor3.run(FORWARD);
      motor4.run(FORWARD);
      state = 3; // forward left
      Serial.write("forward left \n");
     }
     else if(curr == '4' && prev == '1') {
      motor1.setSpeed(25);
      motor2.setSpeed(25);
      motor3.setSpeed(50);
      motor4.setSpeed(50);
      motor1.run(FORWARD);
      motor2.run(FORWARD);
      motor3.run(FORWARD);
      motor4.run(FORWARD);
      state = 3; // forward left
      Serial.write("forward left \n");
     }
     else if(dummy == '7'){
      myservo.write(0);
      delay(1000);
      myservo.write(119);
      delay(1000);
    }
    else if(dummy == '8'){
      myservo.write(0);
      delay(1000);
    }
     else if(curr == '2' && prev == '2') {
      motor1.setSpeed(50);
      motor2.setSpeed(50);
      motor3.setSpeed(50);
      motor4.setSpeed(50);
      motor1.run(BACKWARD);
      motor2.run(BACKWARD);
      motor3.run(BACKWARD);
      motor4.run(BACKWARD);
      state = 4; // backwards
      Serial.write("backwards \n");
      delay(10);
     }
     else {
      state = 0;
      motor1.run(RELEASE);
      motor2.run(RELEASE);
      motor3.run(RELEASE);
      motor4.run(RELEASE);
      Serial.write(curr);
      Serial.write(" ");
      Serial.write(prev);
      Serial.write("\n");

     }

    }

     prev = curr;     
}
int readSensor() {
	digitalWrite(sensorPower, HIGH);	// Turn the sensor ON
	delay(10);							// Allow power to settle
	int val = analogRead(sensorPin);	// Read the analog value form sensor
	digitalWrite(sensorPower, LOW);		// Turn the sensor OFF
	return val;							// Return analog moisture value
}