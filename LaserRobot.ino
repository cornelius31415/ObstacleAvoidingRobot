// Adafruit Motor Shield library Version 1.0.0
#include <AFMotor.h>
#include <Wire.h>
#include <Adafruit_VL53L0X.h>


// Creating motor objects
AF_DCMotor motor1(1);  
AF_DCMotor motor2(2); 
AF_DCMotor motor3(3); 
AF_DCMotor motor4(4); 

// creating a sensor object
Adafruit_VL53L0X distanceSensor = Adafruit_VL53L0X();

uint8_t robotSpeed = 180;
int laserDistance;
uint8_t criticalDistance = 500;

// -------------------------------------------------------------------------------------
//                                        SETUP
// -------------------------------------------------------------------------------------

void setup() {
 Serial.begin(115200);         // high baudrate because lots of info coming from that sensor
  distanceSensor.begin();
  setupMotors();

  
}

// -------------------------------------------------------------------------------------
//                                     SUPER LOOP
// -------------------------------------------------------------------------------------

void loop() {
 
  moveForward();
  laserDistance = measureDistanceLaser();
  
  Serial.print("Measured Distance: ");
  Serial.println(laserDistance);  
  
  uint8_t randomNumber = random(1,254);
  
  if (laserDistance < criticalDistance && laserDistance > 1 && isEven(randomNumber)) {
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
  
  if (laserDistance < criticalDistance && laserDistance > 1 && !isEven(randomNumber)) {
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
  
  delay(400); 

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
    
  delay(400); 

  motor3.run(RELEASE);  
  motor4.run(RELEASE);  
  
}

// -------------------------------------------------------------------------------------
//                              EVEN OR NOT THAT IS THE QUESTION
// -------------------------------------------------------------------------------------



bool isEven(uint8_t number) {
  if (number % 2 == 0) {
    return true;
  }

  else { 
    return false;
  }
}



// -------------------------------------------------------------------------------------
//                               PROCESSING LASER DATA
// -------------------------------------------------------------------------------------


int measureDistanceLaser() {

  VL53L0X_RangingMeasurementData_t measurement; // its own datatype, contains Range Status, Range Millimeter, etc..
  distanceSensor.rangingTest(&measurement,true); // use pointer to measurement because more efficient than calling 
                                                 // the whole variable

  if (measurement.RangeStatus != 4) {

    laserDistance = measurement.RangeMilliMeter;

    Serial.println(" ");
  Serial.print(laserDistance);
  Serial.println(" mm");
  Serial.println(" ");
    
    return laserDistance;
  }

  else {
    Serial.println(" ");
    Serial.println("Out of Range");
    Serial.println(" "); 
    
  }
  
}
