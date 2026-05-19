// Code to read from Serial port and OPEN/CLOSE the gripper

#include <Servo.h>
Servo serv;

int BAUDRATE = 9600;
int SERVO_PIN = 3;
int OPEN = 170;
int CLOSE = 100;

void setup() {
  Serial.begin(BAUDRATE);
  serv.attach(SERVO_PIN);
  serv.write(OPEN); // Open the gripper initially
}

void loop() {
  if (Serial.available() > 0) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();
    cmd.toLowerCase();
    
    if (cmd == "close") {
      serv.write(CLOSE);
      Serial.println("GRIPPER CLOSED!");
    } else {
      serv.write(OPEN);
      Serial.println("GRIPPER OPEN!");
    }
  }
}