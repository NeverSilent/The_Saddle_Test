/*
 * The Saddle Main
 * 2021.08.31
 * The Saloon
 * Alex Lamey
 * Eric Suszerk
 * J.D. Herlehy
 * Octavio Daiz
 * To drive and control the saddle
 */

#define PWMLeft 3
#define PWMRight 9
#define DIRLeft 5
#define DIRRight 10
#define XAxis A1
#define YAxis A0

//Extra Vars Getting Defined
volatile int joyX;
volatile int joyXInvert;
volatile int joyY;
volatile int V;
volatile int W;
volatile int rightMotor;
volatile int leftMotor;
volatile int rightMotorD;
volatile int leftMotorD;

void setup() {
  Serial.begin(115200); //will be deleted after debugging is no longer needed

  //set up for motor controllers direction
  pinMode(OUTPUT, DIRLeft);
  pinMode(OUTPUT, DIRRight);

  //set up for axis
  pinMode(INPUT, XAxis);
  pinMode(INPUT, YAxis);

}

void loop() {
  //Get X and Y from the Joystick, do whatever scaling and calibrating you need to do based on your hardware.
  //Invert X

  //The input range and/or output range might need to be adjusted for range of stick movement + deadzone
  joyX = map(analogRead(XAxis), 0, 1023, -255, 255);
  joyXInvert = -joyX;
  
  joyY = map(analogRead(YAxis), 0, 1023, -255, 255);

  //Calculate R+L (Call it V): V =(100-ABS(X)) * (Y/100) + Y
  V = ((100 - abs(joyXInvert)) * (joyY / 100)) + joyY;

  //Calculate R-L (Call it W): W= (100-ABS(Y)) * (X/100) + X
  W = ((100 - abs(joyY)) * (joyXInvert / 100)) + joyXInvert;

  //Calculate R: R = (V+W) /2
  rightMotor = (V + W) / 2;

  //Calculate L: L= (V-W)/2
  leftMotor = (V - W) / 2;

  //The left and right motor may need to be scaled to get the proper power lvls out
  //eg. 5 doesn't make the motor move but 15 does. ^^ all percents ^
  //need a number to scale for pwm duty cycle and a direction for the motors
  //duty cycle comes from the abs value then scale the 0-100 to 0-255 (8 bit res)
  //direction comes from the sign of the value out (+ forward; - reverse)

  if(leftMotor > 0){
    leftMotorD = 255;
  } else {
    leftMotorD = 0;
  }

  if(rightMotor > 0){
    rightMotorD = 255;
  } else {
    rightMotorD = 0;
  }

  
  Serial.print(leftMotor);
  Serial.print(" ");
  Serial.print(rightMotor);
  Serial.print("**  **");
  Serial.print(joyX);
  Serial.print(" ");
  Serial.print(joyY);
  Serial.print("** **");
  Serial.print(leftMotorD);
  Serial.print(" ");
  Serial.println(rightMotorD);

  /*
  leftMotorD = 1;
  rightMotorD = 1;
  leftMotor = map(analogRead(XAxis), 0, 1023, 5, 255);
  rightMotor = map(analogRead(YAxis), 0, 1023,5, 255);
  */
  
  analogWrite(DIRLeft, leftMotorD);
  analogWrite(DIRRight, rightMotorD);
  analogWrite(PWMLeft, abs(leftMotor));
  analogWrite(PWMRight, abs(rightMotor));
  
}
