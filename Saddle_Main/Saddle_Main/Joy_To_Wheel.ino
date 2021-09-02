/* 
 * Method to turn Joystick input into motor output
 * Will proly do the work here and then copy and paste back to the main
 * 2021.08.31
 * The Saloon
 * Alex Lamey
 * Eric Suszerk
 * J.D. Herlehy
 * Octavio Diaz
 * 2021.09.02 + Expansion on the conversion from joystick to tank JDH
 */

//define the axis inputs
#define XAxis 4
#define YAxis 14

//Extra Vars Getting Defined
int joyX;
int joyXInvert;
int joyY;
int V;
int W;
int rightMotor;
int leftMotor;


void setup() {
  //delete this when debuging is done
  Serial.begin(9600);

  //set up for axis
  pinMode(INPUT, XAxis);
  pinMode(INPUT, YAxis);

}

void loop() {
  //The following is the pesudocode for the conversion
  //Have to scale the 16bit input to 0 -> 200 and then subtract 100 then invert it
  /* DELETE THIS WHEN NO REFRENCE OF ALL NEEDED AND/OR OTHER TEAM MEMBERS LOOK AT IT
    Get X and Y from the Joystick, do whatever scaling and calibrating you need to do based on your hardware.
    Invert X
    Calculate R+L (Call it V): V =(100-ABS(X)) * (Y/100) + Y
    Calculate R-L (Call it W): W= (100-ABS(Y)) * (X/100) + X
    Calculate R: R = (V+W) /2
    Calculate L: L= (V-W)/2
    Do any scaling on R and L your hardware may require.
    Send those values to your Robot.
    Go back to 1
  */

  //Get X and Y from the Joystick, do whatever scaling and calibrating you need to do based on your hardware.
  //Invert X

  //The input range and/or output range might need to be adjusted for range of stick movement + deadzone
  joyX = map(analogRead(XAxis), 0, 4095, 0, 200);
  joyX = (joyX - 100);
  joyXInvert = -joyX;
  
  joyY = map(analogRead(YAxis), 0, 4095, 0, 200);
  joyY = (joyY - 100);

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
}
