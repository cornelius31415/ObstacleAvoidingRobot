// This sketch measures the distance to an ultrasound sensor and
// displays it on the LCD screen and in the serial monitor

#include <LiquidCrystal.h>

// setting up the pins used for the LCD screen
LiquidCrystal lcd(7,8,9,10,11,12);

// declaring the pins for the echo and the trigger
int echopin = 2;
int trigpin = 3;

// variables we will need to calculate physics you know
double duration;
double velocity;
double distance;


void setup() {
  // put your setup code here, to run once:

  // setting up number of columns and rows
  lcd.begin(16,2);
  lcd.print("Distance: ");
  
  // initialize the Serial Connection between Arduino and Port of Computer
  Serial.begin(9600);
  delay(1000);      // after initialization wait a second

  pinMode(trigpin,OUTPUT); // set trigpin to output
  pinMode(echopin,INPUT);  // and echopin to input

}

void loop() {
  // put your main code here, to run repeatedly:

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

  // print the distance in the serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // print the distance on the LCD screen  
  lcd.setCursor(10,0);
  lcd.print(distance);
  lcd.setCursor(14,0);
  lcd.print("cm");

  // wait a sec to do it all over again
  delay(1000);

}
