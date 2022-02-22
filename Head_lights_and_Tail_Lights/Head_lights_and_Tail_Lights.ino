/*  Alex Lamey 
 *Created on 04/02/22
 *Edited on by AL 07/02/22 
 *Edited JDH 2022.2.21
 */

#define potPin1 A1 //x axis
#define potPin2 A0 //y axis

/*Define Signal Pins for the transistors on the headlights*/ 
#define lTailLight 4
#define rTailLight 7
#define rHeadlight 8
#define lHeadlight 12

//DEADZONE
#define DEADZONE 2

//Blink Interval, The time the lights are off for milliseconds
#define BLINK_INTERVAL 330

/*define coordinate system*/
volatile int xAxis = 0;
volatile int yAxis = 0;

//Timer vars
volatile unsigned long currentTime;
volatile unsigned long prevTime = 0;

//declare the status of LEDS
char LTailStat = 0;
char RTailStat = 0;
char LHeadStat = 0;
char RHeadStat = 0;

/*begin headlight code*/
void setup() { 
  
  //declare pins and baudrate
  pinMode(potPin1, INPUT);
  pinMode(potPin2, INPUT);
  pinMode(lTailLight, OUTPUT);
  pinMode(rTailLight, OUTPUT);
  pinMode(rHeadlight, OUTPUT);
  pinMode(lHeadlight, OUTPUT);
  
  Serial.begin(115200);
}

void loop() { //begin running mode
  //have to play around with these values to set the angle to the boundaries of the angles
  xAxis = map(analogRead(potPin1), 0, 1023, -10, 10); //define the X coordinate system
  yAxis = map(analogRead(potPin2), 0, 1023, -10, 10); //define the Y coordinate system
  
  /* SETUP SERIAL DEBUGGER */
  
  Serial.print("X: ");
  Serial.print(xAxis);
  //Serial.print(",");
  //Serial.println(valPot1);
  Serial.print("\t");
  Serial.print("Y: ");
  Serial.print(yAxis);
  Serial.println(" ");
  //Serial.print(",");
  //Serial.println(valPot2);
  //Serial.println("X Axis: toString(xAxis) Y Axis: toString(yAxis) \n");
  

  /*############TURN SIGNALS##############*/

  /*DEADZONE                This section is applied whenever the X and Y potentiometer are centered*/
  if (abs(xAxis) < DEADZONE && abs(yAxis) < DEADZONE) { //if the joystick is centered
    digitalWrite(lTailLight, LOW); //no lights
    digitalWrite(rTailLight, LOW); //no lights
    digitalWrite(lHeadlight, LOW); //no lights
    digitalWrite(rHeadlight, LOW); //no lights
  }

  /*      FORWARD           This section is applied whenever the Y potentiometer is tilted forwards */
  if (yAxis >= DEADZONE) { //if joystick is tilted fwds 
    currentTime = millis(); //take current time
    if ((currentTime - prevTime) >= BLINK_INTERVAL){ //check previous time to enter loop and effect current state of light
      prevTime = currentTime; //set the last time lights got turned off (somewhat arbitrary variable to make the lights blink
      
      LTailStat = (LTailStat == 0) ? 1 : 0;
      RTailStat = (RTailStat == 0) ? 1 : 0;
      LHeadStat = (LHeadStat == 0) ? 1 : 0;
      RHeadStat = (RHeadStat == 0) ? 1 : 0;
        
      if (xAxis >= DEADZONE) { //if turning right
        digitalWrite(lTailLight, LOW);  //left off
        digitalWrite(lHeadlight, LOW);  //left off
        digitalWrite(rTailLight, RTailStat); //right on
        digitalWrite(rHeadlight, RHeadStat); //right on
      }
      if (xAxis <= -DEADZONE) { //if turning left
        digitalWrite(lTailLight, LTailStat); //left on
        digitalWrite(lHeadlight, LHeadStat); //left on
        digitalWrite(rTailLight, LOW);  //right off
        digitalWrite(rHeadlight, LOW);  //right off
      }
    }
  }
  /*END OF FORWARD SECTION*/

 /*     REVERSE This section is applied whenever the Y potentiometer is tilted backwards*/
  if (yAxis <= -DEADZONE) { //if joystick is tilted backwards
    currentTime = millis(); //take current time
    if (currentTime - prevTime >= BLINK_INTERVAL){//check previous time to enter loop and effect current state of light
      prevTime = currentTime; //set the last time lights got turned off (somewhat arbitrary variable to make the lights blink)
      
      LTailStat = (LTailStat == 0) ? 1 : 0;
      RTailStat = (RTailStat == 0) ? 1 : 0;
      LHeadStat = (LHeadStat == 0) ? 1 : 0;
      RHeadStat = (RHeadStat == 0) ? 1 : 0; 

      if (xAxis >= DEADZONE) { //if saddle is backing up right 
        digitalWrite(lTailLight, HIGH); //left on
        digitalWrite(lHeadlight, HIGH); //left on
        digitalWrite(rTailLight, RTailStat);  //right off
        digitalWrite(rHeadlight, RTailStat);  //right off
      } else if (xAxis <= -DEADZONE) { //if saddle is backing up left
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
    }/*END OF REVERSE SECTION*/
  }
}
