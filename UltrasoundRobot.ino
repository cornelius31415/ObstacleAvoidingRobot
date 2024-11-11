// Adafruit Motor Shield library Version 1.0.0
#include <AFMotor.h>

// declaring the pins for the echo and the trigger
const int echopin = 13;
const int trigpin = 2;


// Creating motor objects
AF_DCMotor motor1(1);  
AF_DCMotor motor2(2); 
AF_DCMotor motor3(3); 
AF_DCMotor motor4(4); 

uint8_t robotSpeed = 200;

float distance;
uint8_t criticalDistance = 40;

// -------------------------------------------------------------------------------------
//                                        SETUP
// -------------------------------------------------------------------------------------

void setup() {
Serial.begin(9600);
  setupMotors();
  setupUltraSound();
  
}

// -------------------------------------------------------------------------------------
//                                     SUPER LOOP
// -------------------------------------------------------------------------------------

void loop() {
 
  moveForward();
  distance = measureDistance();
  
  Serial.print("Measured Distance: ");
  Serial.println(distance);  
  
  uint8_t randomNumber = random(1,254);
  
  if (distance < criticalDistance && distance > 1 && isEven(randomNumber)) {
    // the idea of the following procedure is to help the robot not getting
    // stuck in narrow areas due to repeated low distance measurement
    // and non-stop turning when there is no space to turn
    
    // move a bit backwards
    releaseMotors();
    moveBackward();
    delay(500); 
    
    // then turn  
    turnRight();
    
    // then move a little bit forward
    moveForward();
    delay(500);
    releaseMotors();
    
  }
  
  if (distance < criticalDistance && distance > 1 && !isEven(randomNumber)) {
    // same as before, just turning left this time
    
    releaseMotors();
    moveBackward();
    delay(500);   
  
    turnLeft();
    
    moveForward();
    delay(500);
    releaseMotors();
    
  }
  
  delay(100);       
        
}



// -------------------------------------------------------------------------------------
//                              SETTING UP THE MOTORS
// -------------------------------------------------------------------------------------

void setupMotors() {

  motor1.run(RELEASE);  
  motor2.run(RELEASE);  
  motor3.run(RELEASE);  
  motor4.run(RELEASE);  

  motor1.setSpeed(robotSpeed);
  motor2.setSpeed(robotSpeed);
  motor3.setSpeed(robotSpeed);
  motor4.setSpeed(robotSpeed);
  
}

// -------------------------------------------------------------------------------------
//                           SETTING UP THE ULTRA SOUND
// -------------------------------------------------------------------------------------

void setupUltraSound() {
  pinMode(trigpin,OUTPUT); // set trigpin to output
  pinMode(echopin,INPUT);  // and echopin to input
}

// -------------------------------------------------------------------------------------
//                               ROBOT MOVEMENTS
// -------------------------------------------------------------------------------------
void releaseMotors() {
  motor1.run(RELEASE);  
  motor2.run(RELEASE);  
  motor3.run(RELEASE);  
  motor4.run(RELEASE);  
  
}


void moveForward() {
  motor1.run(FORWARD);   
  motor2.run(FORWARD);     
  motor3.run(FORWARD);  
  motor4.run(FORWARD);   
}

void moveBackward() {
  motor1.run(BACKWARD);   
  motor2.run(BACKWARD);     
  motor3.run(BACKWARD);  
  motor4.run(BACKWARD);   
  
}

void turnRight() {
  
  motor1.run(RELEASE);  
  motor2.run(RELEASE);  
  motor3.run(RELEASE);  
  motor4.run(RELEASE);  
  
  delay(500);

  motor1.run(BACKWARD);   
  motor2.run(BACKWARD);    
  
  delay(800); 

  motor1.run(RELEASE);  
  motor2.run(RELEASE);  
}

void turnLeft() {
  
  motor1.run(RELEASE);  
  motor2.run(RELEASE);  
  motor3.run(RELEASE);  
  motor4.run(RELEASE);  
  
  delay(500);

  motor3.run(BACKWARD);   
  motor4.run(BACKWARD);  
    
  delay(800); 

  motor3.run(RELEASE);  
  motor4.run(RELEASE);  
  
}

// -------------------------------------------------------------------------------------
//                         PROCESSING ULTRA SOUND DATA
// -------------------------------------------------------------------------------------

float measureDistance() {

  double duration;
  double velocity;
  double distance;
  
  // make sure that trigpin is set to LOW in the beginning
  digitalWrite(trigpin,LOW);
  delayMicroseconds(2);

  // trigger a signal in the ultrasound sensor
  digitalWrite(trigpin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin,LOW);

  // measure the time it took the signal to travel back
  duration = pulseIn(echopin,HIGH);   // gives back time in microseconds

  velocity = 0.0343;  // speed of sound in cm/microsec
  distance = 0.5 * duration * velocity;  // distance travelled is half of duration times speed

  return distance;
  
}

bool isEven(uint8_t number) {
  if (number % 2 == 0) {
    return true;
  }

  else { 
    return false;
  }
}
