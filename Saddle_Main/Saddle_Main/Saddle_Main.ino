/*
 * The Saddle Main
 * 2021.08.31
 * The Saloon
 * Alex Lamey
 * Eric Suszerk
 * J.D. Herlehy
 * Octavio Daiz
 * To drive and control the saddle
 * 2021.9.2 + Added Cruise Control JDH
 */

#define ButtonOne 33
#define ButtonTwo 26
#define PWMLeft 3
#define PWMRight 9
#define DIRLeft 2
#define DIRRight 10
#define XAxis 4
#define YAxis 14
#define Power 35 //subject to change to real pinout

//define other vars
int cruise; //setting if it's on or off
int cruiseL; //value of cruise left duty %
int cruiseLD; //value of cruise left direction
int cruiseR; //value of cruise right duty %
int cruiseRD; //value of cruise right direction


void setup() {
  Serial.begin(9600); //will be deleted after debugging is no longer needed

  //set up pwm for the motor controllers
  ledcSetup(6, 20000, 8); //20kHz, 8bit res
  ledcSetup(10, 20000, 8);

  ledcAttachPin(PWMLeft, 6);
  ledcAttachPin(PWMRight, 10);

  //set up for motor controllers direction
  pinMode(OUTPUT, DIRLeft);
  pinMode(OUTPUT, DIRRight);

  //set up for button inputs + power
  pinMode(INPUT_PULLUP, ButtonOne);
  pinMode(INPUT_PULLUP, ButtonTwo);
  pinMode(INPUT_PULLUP, Power);

  //set up for axis
  pinMode(INPUT, XAxis);
  pinMode(INPUT, YAxis);

}

void loop() {
  //check if the power is on (this may be off, if so change to ==)
  if(analogRead(Power) != 0){
    //fetch input from axis and output to the motors
    //hold the output motor values for use in cruise control (secondary feature)
    //use an array to hold motor values or use same method twice but return different things
    //implement the conversion into this main code?
    
    //Cruise Control
    //If a button is pressed hold the current motor outputs
    //Publish the held output to the motors until the other button is pressed
    //otherwise publish the real time outputs
    //set casses, one case for non cruise and one case for cruise, check case number

    if(analogRead(ButtonOne) == 0){ //0 might be unpressed, change to != otherwise
      cruise = 1;
      cruiseL = leftMotor;
      cruiseLD = leftMotorD;
      cruiseR = rightMotor;
      cruiseRD = rightMotorD;
    }

    switch(cruise){
      case 0: //non-cruise case
        ledcWrite(6, leftMotor);
        ledcWrite(10, rightMotor);
        digitalWrite(DIRLeft, leftMotorD);
        digitalWrite(DIRRight, rightMotorD);

        break;
        
      case 1: //cruise case
        if(analogRead(ButtonTwo) == 0){ //0 might be unpressed, change to != otherwise
          cruise = 0;
        }
        ledcWrite(6, cruiseL);
        ledcWrite(10, cruiseR);
        digitalWrite(DIRLeft, cruiseLD);
        digitalWrite(DIRRight, cruiseRD);

        break;
    }
    
  }
  
}
