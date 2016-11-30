/*

Calibration of AFRO12A ESC (SimonK firware)
Guessed procedure for calibration : 
1. apply MAX_THROTTLE
2. power on ESC
3. wait some beep(s) from the ESC
4. apply MIN_THROTTLE
5. wait some beep(s) from the ESC
6. this should be done, ready to apply any value from MIN_THROTTLE to MAX_THROTTLE

*/

#include <Servo.h>
#define BAUDS 9600
#define MIN_THROTTLE 1000               // real MIN pulse width supposed to be 1000 as standard, sometimes less according to ESC firmware
#define MAX_THROTTLE 2000               // real MAX pulse width supposed to be 2000 as standard, sometimes more according to ESC firmware
#define MOTOR1_PIN 9

Servo MOTOR1;  // create servo object to control a servo
int motor_setpoint = 0; // value to store actual user setpoint for motor
bool continueCalib = false;  // bool to ask user if he wants to make another calibration
char userinput;         // to store user answer

void setup() {
  Serial.begin(BAUDS);
  Serial.println("*** ESC calibration intialize ***");
  Serial.print("Attaching ESC MOTOR1 to pin "); Serial.println(MOTOR1_PIN);
  MOTOR1.attach(MOTOR1_PIN);  // attaches the servo on pin 9 to the servo object
  

  
}

void loop() {
//  val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
//  val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
  do{
    Serial.println("*** ESC calibration procedure ***");
    while(Serial.available()>0){Serial.read();}                        // flush serial receive buffer
    Serial.println("ESC must be powered off. Press any key to continue");
    while(!Serial.available());          // wait for keystroke
    Serial.read();
    Serial.print(MAX_THROTTLE); Serial.println(" pulse width (MAX) is sent to ESC MOTOR1");
    MOTOR1.writeMicroseconds(MAX_THROTTLE);                  // send MAX value to ESC
    while(Serial.available()>0){Serial.read();}                        // flush serial receive buffer in case of accidental keystroke
    Serial.println("Power on the ESC, wait for beeps and quickly press any key");
    while(!Serial.available());          // wait for keystroke
    Serial.read();
    Serial.print(MIN_THROTTLE); Serial.println(" pulse width (MIN) is sent to ESC MOTOR1");
    MOTOR1.writeMicroseconds(MIN_THROTTLE);                 // send MIN value to ESC
  
    Serial.println("You should have heard some beeps and ESC MOTOR1 should be calibrated...");
    Serial.println();
    while(Serial.available()>0){Serial.read();}                        // flush serial receive buffer
    Serial.print("Do you want to calibrate another ESC ?\nY to start again, any key to go to next step : ");
    while(!Serial.available());          // wait for keystroke
    userinput = Serial.read();
    if(userinput == 'y' || userinput == 'Y'){continueCalib = true;}else{continueCalib = false;}
  }while(continueCalib);

  Serial.println("*** Testing procedure ***");
  do{
    Serial.read();
    Serial.println("Enter a value between 0 and 1000 to send to the motor (negative value to stop procedure) : ");
    while(!Serial.available());
    motor_setpoint = Serial.parseInt();
    Serial.print("Received setpoint : "); Serial.println(motor_setpoint);
    if (motor_setpoint > 1000) {motor_setpoint = 1000;}else if(motor_setpoint < 0) {break;}
    Serial.print(motor_setpoint + 1000); Serial.println(" pulse width sent to ESC MOTOR1");
    MOTOR1.writeMicroseconds(motor_setpoint + 1000);
    }while(true);
    
    Serial.println("*** OUT FROM TESTING LOOP ***");
    MOTOR1.writeMicroseconds(MIN_THROTTLE);
  
  
//  delay(1500);                           // waits for the servo to get there
//  MOTOR1.writeMicroseconds(1900);
//  delay(3000);
//  MOTOR1.writeMicroseconds(1000);
//  delay(1500);
}

