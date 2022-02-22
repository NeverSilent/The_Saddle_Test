/*
 * The Saddle Main V2
 * 2022.2.21
 * The Saloon
 * Alex Lamey
 * Eric Suszerk
 * J.D. Herlehy
 * Octavio Daiz
 * Main Body of Code For the Saddle
 * +Lights 2022.2.21
 */

#define PWMLeft 3
#define PWMRight 9
#define DIRLeft 5
#define DIRRight 10
#define XAxis A1
#define YAxis A0

/*Define Signal Pins for the transistors on the headlights*/ 
#define lTailLight 4
#define rTailLight 7
#define rHeadlight 8
#define lHeadlight 12

//DEADZONE
#define DEADZONE 15

//Blink Interval, The time the lights are off for milliseconds
#define BLINK_INTERVAL 300

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

/*define times*/
volatile unsigned long currentTime;
volatile unsigned long prevTime = 0;

//declare the status of LEDS
char LTailStat = 0;
char RTailStat = 0;
char LHeadStat = 0;
char RHeadStat = 0;

void setup() {
  Serial.begin(115200); //will be deleted after debugging is no longer needed

  //set up for motor controllers direction
  pinMode(OUTPUT, DIRLeft);
  pinMode(OUTPUT, DIRRight);

  //set up for axis
  pinMode(INPUT, XAxis);
  pinMode(INPUT, YAxis);

  pinMode(lTailLight, OUTPUT);
  pinMode(rTailLight, OUTPUT);
  pinMode(rHeadlight, OUTPUT);
  pinMode(lHeadlight, OUTPUT);

}

void loop() {
  //**DEBUG**//
    
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

  if((abs(leftMotor) >= DEADZONE) && (abs(rightMotor) >= DEADZONE)){
    analogWrite(DIRLeft, leftMotorD);
    analogWrite(DIRRight, rightMotorD);
    analogWrite(PWMLeft, abs(leftMotor));
    analogWrite(PWMRight, abs(rightMotor));
  } else {
    analogWrite(PWMLeft, 0);
    analogWrite(PWMRight, 0);
  }

  //******************* LIGHTS **************//

  //have to play around with these values to set the angle to the boundaries of the angles
  
  /*############TURN SIGNALS##############*/

  /*DEADZONE                This section is applied whenever the X and Y potentiometer are centered*/
  if (abs(joyX) < DEADZONE && abs(joyY) < DEADZONE) { //if the joystick is centered
    digitalWrite(lTailLight, LOW); //no lights
    digitalWrite(rTailLight, LOW); //no lights
    digitalWrite(lHeadlight, LOW); //no lights
    digitalWrite(rHeadlight, LOW); //no lights
  }

  /*      FORWARD           This section is applied whenever the Y potentiometer is tilted forwards */
  if (joyY >= DEADZONE) { //if joystick is tilted fwds 
    currentTime = millis(); //take current time
    if ((currentTime - prevTime) >= BLINK_INTERVAL){ //check previous time to enter loop and effect current state of light
      prevTime = currentTime; //set the last time lights got turned off (somewhat arbitrary variable to make the lights blink
      
      LTailStat = (LTailStat == 0) ? 1 : 0;
      RTailStat = (RTailStat == 0) ? 1 : 0;
      LHeadStat = (LHeadStat == 0) ? 1 : 0;
      RHeadStat = (RHeadStat == 0) ? 1 : 0;
        
      if (joyX >= DEADZONE) { //if turning right
        digitalWrite(lTailLight, LOW);  //left off
        digitalWrite(lHeadlight, LOW);  //left off
        digitalWrite(rTailLight, RTailStat); //right on
        digitalWrite(rHeadlight, RHeadStat); //right on
      }
      if (joyX <= -DEADZONE) { //if turning left
        digitalWrite(lTailLight, LTailStat); //left on
        digitalWrite(lHeadlight, LHeadStat); //left on
        digitalWrite(rTailLight, LOW);  //right off
        digitalWrite(rHeadlight, LOW);  //right off
      }
    }
  }//END OF FORWARD SECTION

 /*     REVERSE This section is applied whenever the Y potentiometer is tilted backwards*/
  if (joyY <= -DEADZONE) { //if joystick is tilted backwards
    currentTime = millis(); //take current time
    if (currentTime - prevTime >= BLINK_INTERVAL){//check previous time to enter loop and effect current state of light
      prevTime = currentTime; //set the last time lights got turned off (somewhat arbitrary variable to make the lights blink)
      
      LTailStat = (LTailStat == 0) ? 1 : 0;
      RTailStat = (RTailStat == 0) ? 1 : 0;
      LHeadStat = (LHeadStat == 0) ? 1 : 0;
      RHeadStat = (RHeadStat == 0) ? 1 : 0; 

      if (joyX >= DEADZONE) { //if saddle is backing up right 
        digitalWrite(lTailLight, HIGH); //left on
        digitalWrite(lHeadlight, HIGH); //left on
        digitalWrite(rTailLight, RTailStat);  //right off
        digitalWrite(rHeadlight, RTailStat);  //right off
      } else if (joyX <= -DEADZONE) { //if saddle is backing up left
        digitalWrite(lTailLight, LTailStat);  //left off
        digitalWrite(lHeadlight, LHeadStat);  //left off
        digitalWrite(rTailLight, HIGH); //right on
        digitalWrite(rHeadlight, HIGH); //right off
      } else {
        digitalWrite(lTailLight, LTailStat); //left on
        digitalWrite(lHeadlight, LHeadStat); //left low
        digitalWrite(rTailLight, RTailStat); //right on
        digitalWrite(rHeadlight, RHeadStat); //right on
      }
    }
  }//END OF REVERSE SECTION
  //END OF LIGHTS
}//END OF LOOP
