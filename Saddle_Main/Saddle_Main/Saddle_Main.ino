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

#define ButtonOne 33
#define ButtonTwo 26
#define PWMLeft 18
#define PWMRight 19
#define DIRLeft 23
#define DIRRight 25
#define XAxis 4
#define YAxis 14
#define Power 35 //subject to change to real pinout


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
    
    
  }
  
}
