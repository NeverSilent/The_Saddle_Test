/*  Alex Lamey 
 *Created on 04/02/22 */
/*Edited on by AL 07/02/22 */

 //This is code for an ARDUINO UNO AND NEEDS TO BE MODIFIED TO FIT THE ESP32
int potPin1 = A0; //Potentiometer Wiper
int potPin2 = A1; //Pot wiper 2

/*Define Signal Pins for the transistors on the headlights*/ 
int lTailLight = PD5;
int rTailLight = PD7;
int rHeadlight = PD3;
int lHeadlight = PD4;

/*Define Control Potentiometers*/
int valPot1 = 0;
int valPot2 = 0;

/*define coordinate system*/
int xAxis = 0;
int yAxis = 0;
/*define times*/
unsigned long currentTime;
unsigned long prevTime = 0;
const long blinkInterval = 800;

/*begin headlight code*/
void setup() { //declare pins and baudrate
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(PD7, OUTPUT);
  pinMode(PD5, OUTPUT);
  pinMode(PD4, OUTPUT);
  pinMode(PD3, OUTPUT);
  
  Serial.begin(115200);
}

void loop() { //begin running mode
  valPot1 = analogRead(potPin1); //assign the value to an integer(may be unnecessary, unsure)
  valPot2 = analogRead(potPin2); // assign the value to an integer (may be unnecessary, unsure)
  
  xAxis = map(valPot1, 0, 449 , -10, 10); //define the X coordinate system
  yAxis = map(valPot2, 0, 853, -10, 10); //define the Y coordinate system
  
  /* SETUP SERIAL DEBUGGER */
  
  Serial.print("X: ");
  Serial.print(xAxis);
  //Serial.print(",");
 // Serial.println(valPot1);
  Serial.print("\t");
  Serial.print("Y: ");
  Serial.print(yAxis);
  Serial.println(" ");
  //Serial.print(",");
  //Serial.println(valPot2);
  
 

  //Serial.println("X Axis: toString(xAxis) Y Axis: toString(yAxis) \n");
  

  /*############TURN SIGNALS##############*/

  /*DEADZONE                This section is applied whenever the X and Y potentiometer are centered*/
  if (xAxis > -3 && xAxis < 3 && yAxis > -3 && yAxis < 3) { //if the joystick is centered
    digitalWrite(lTailLight, LOW); //no lights
    digitalWrite(rTailLight, LOW); //no lights
    digitalWrite(lHeadlight, LOW); //no lights
    digitalWrite(rHeadlight, LOW); //no lights
  }

  /*      FORWARD           This section is applied whenever the Y potentiometer is tilted forwards */
  if (yAxis > 1) { //ifjoystick is tilted fwds 
    currentTime = millis(); //take current time
    if (currentTime - prevTime > blinkInterval) //this line makes the lights turn on when the time since the prevous lights turning on exceeds 0.8seconds
    { for (long i = 0; i < (blinkInterval + 36000); i++) { //I set this to run for a set duration, there is probably a better way to do this, but I liked the blinking speed I obtained here through trial and error
        if (xAxis > 1) { //if turning right
          digitalWrite(lTailLight, LOW);  //left off
          digitalWrite(lHeadlight, LOW);  //left off
          digitalWrite(rTailLight, HIGH); //right on
          digitalWrite(rHeadlight, HIGH); //right on
        }
        if (xAxis < -1) { //if turning left
          digitalWrite(lTailLight, HIGH); //left on
          digitalWrite(lHeadlight, HIGH); //left on
          digitalWrite(rTailLight, LOW);  //right off
          digitalWrite(rHeadlight, LOW);  //right off
        }
      }
      prevTime = currentTime; //set the last time lights got turned off (somewhat arbitrary variable to make the lights blink)
    }
    else //if the joystick is tilted forwards, but the lights are in an off interval of the blink
    {
        digitalWrite(rTailLight, LOW); //right off
        digitalWrite(rHeadlight, LOW); //right off
        digitalWrite(lTailLight, LOW); //left off
        digitalWrite(lHeadlight, LOW); //left off
      }
    }
  /*END OF FORWARD SECTION*/

 /*     REVERSE This section is applied whenever the Y potentiometer is tilted backwards*/
  if (yAxis < -2) { //if joystick is tilted backwards
    currentTime = millis(); //take current time
    if (currentTime - prevTime > blinkInterval)//this line makes the lights turn on when the time since the prevous lights turning on exceeds 0.8seconds
    {for (long i = 0; i < (blinkInterval + 36000); i++) { //I set this to run for a set duration, there is probably a better way to do this, but I liked the blinking speed I obtained here through trial and error
        digitalWrite(lTailLight, HIGH); //left on
        digitalWrite(lHeadlight, HIGH); //left low
        digitalWrite(rTailLight, HIGH); //right on
        digitalWrite(rHeadlight, HIGH); //right on 
      }
      prevTime = currentTime; //set the last time lights got turned off (somewhat arbitrary variable to make the lights blink)
    }
    else // if the joystick is tilted backwards, but the lights are in an off interval of the blink
    {
      if (xAxis > 2) { //if saddle is backing up right 
        digitalWrite(lTailLight, HIGH); //left on
        digitalWrite(lHeadlight, HIGH); //left on
        digitalWrite(rTailLight, LOW);  //right off
        digitalWrite(rHeadlight, LOW);  //right off
      }
      if (xAxis < -2) { //if saddle is backing up left
        digitalWrite(lTailLight, LOW);  //left off
        digitalWrite(lHeadlight, LOW);  //left off
        digitalWrite(rTailLight, HIGH); //right on
        digitalWrite(rHeadlight, HIGH); //right off
      }
      if (xAxis > -2 && xAxis < 2) { //if inside deadzone, but moving backwards, all tail lights off, headlights on
        digitalWrite(lTailLight, LOW);
        digitalWrite(rTailLight, LOW);
        digitalWrite(lHeadlight, LOW);
        digitalWrite(rHeadlight, LOW);
      }
    }
  }
  /*END OF REVERSE SECTION*/
}
