// Include the necessary libraries
#include <AFMotor.h>
#include <NewPing.h>
#include <Servo.h>

// Define the sensor pins
#define TRIG_PIN A0
#define ECHO_PIN A1
#define MAX_DISTANCE 200

// Set the speed of the motors
#define MAX_SPEED 160 // sets speed of DC motors

// Create objects for the motors
AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);

// Create the servo motor object
Servo myservo;

// Create the ultrasonic sensor object
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

boolean goesForward = false;
int distance = 100;
int speedSet = 0;

void setup() {
  Serial.begin(9600);
  myservo.attach(10);  
  myservo.write(115); 
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop() {
  // Read distance from the ultrasonic sensor
  distance = readPing();

  // Check if obstacle is detected
  if (distance <= 40) { // Adjust the threshold as needed
    // Obstacle detected, perform obstacle avoidance
    Serial.println("Obstacle detected!");
    moveStop();
    delay(100);
    moveBackward();
    delay(500); // Move backward for 0.5 second
    moveStop();
    delay(200);
    int distanceR = lookRight();
    delay(200);
    int distanceL = lookLeft();
    delay(200);

    if (distanceR >= distanceL) {
      turnRight();
      delay(1000); // Turn right for 1 second
      moveStop();
      forward(); // Move forward again for 0.5 second
      delay(500);
      moveStop();
      turnRight();
      delay(1000); // Turn right for 1 second
      moveStop();
    } else {
      turnLeft();
      delay(1000); // Turn left for 1 second
      moveStop();
      forward(); // Move forward again for 0.5 second
      delay(500);
      moveStop();
      turnLeft();
      delay(1000); // Turn left for 1 second
      moveStop();
    }
  } else {
    // No obstacle detected, keep moving forward
    if (!goesForward) {
      Serial.println("No obstacle, moving forward");
      forward();
    }
  }
}

int lookRight() {
  myservo.write(50); 
  delay(500);
  int distance = readPing();
  delay(100);
  myservo.write(115); 
  return distance;
}

int lookLeft() {
  myservo.write(170); 
  delay(500);
  int distance = readPing();
  delay(100);
  myservo.write(115); 
  return distance;
}

int readPing() { 
  delay(70);
  int cm = sonar.ping_cm();
  if (cm == 0) {
    cm = 250;
  }
  return cm;
}

void moveStop() {
  motor1.run(RELEASE); 
  motor3.run(RELEASE);
  goesForward = false; // Ensure goesForward is set to false when stopping
} 

void forward() {
  if (!goesForward) {
    goesForward = true;
    motor1.run(FORWARD);      
    motor3.run(FORWARD);     
    for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 2) { // slowly bring the speed up to avoid loading down the batteries too quickly
      motor1.setSpeed(speedSet);
      motor3.setSpeed(speedSet);
      delay(5);
    }
  }
}

void moveBackward() {
  goesForward = false;
  motor1.run(BACKWARD);      
  motor3.run(BACKWARD);  
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 2) { // slowly bring the speed up to avoid loading down the batteries too quickly
    motor1.setSpeed(speedSet);
    motor3.setSpeed(speedSet);
    delay(5);
  }
}  

void turnRight() {
  motor1.run(FORWARD);
  motor3.run(BACKWARD);     
} 
 
void turnLeft() {
  motor1.run(BACKWARD);     
  motor3.run(FORWARD);   
} 
