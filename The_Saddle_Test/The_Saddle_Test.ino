#define ButtonOne 33
#define ButtonTwo 26
#define PWMLeft 18
#define PWMRight 19
#define DIRLeft 23
#define DIRRight 25
#define XAxis 2
#define YAxis 13

boolean val = true;

int xVal;
int yVal;

void setup() {
  Serial.begin(9600);

  ledcSetup(6, 20000, 8);
  ledcSetup(10, 20000, 8);
  
  ledcAttachPin(PWMLeft, 6);
  ledcAttachPin(PWMRight, 10);

  pinMode(OUTPUT, DIRLeft);
  pinMode(OUTPUT, DIRRight);

  pinMode(INPUT_PULLUP, ButtonOne);
  pinMode(INPUT_PULLUP, ButtonTwo);

  pinMode(INPUT, XAxis);
  pinMode(INPUT, YAxis);
}

void loop() { 

   /*Currently this loop will display the value of axies
   * Also it will only output the yaxis but there are comments
   * That will make the motors run full on or off depending on button press
   */

  //Serial.print(analogRead(ButtonOne));
  //Serial.print("one");
  //Serial.println();
  //Serial.print(analogRead(ButtonTwo));
  //Serial.print("two");
  //Serial.println();
  Serial.println(analogRead(XAxis));
  //Serial.println(analogRead(YAxis));

  xVal = analogRead(XAxis);
  yVal = analogRead(YAxis);

  //constrain(xVal, 600, 4095);
  ledcWrite(6, (map(xVal, 0, 4095, 0, 255)));
  //ledcWrite(10,255);

  digitalWrite(DIRLeft, HIGH);
  digitalWrite(DIRRight, HIGH);
 /*
  if((analogRead(ButtonOne)) == 0){
    val = true;
    ledcWrite(6, 255);
    ledcWrite(10, 255);
  } /*else {
    ledcWrite(6, 0);
    ledcWrite(10, 0);
  } */
 /* 
  if((analogRead(ButtonTwo)) == 0) {
    //val = false;
    ledcWrite(6, 255);
    ledcWrite(10, 0);
    digitalWrite(DIRLeft, 0);
    digitalWrite(DIRRight, 0);
  }
/*
  if(val == true){
    ledcWrite(6, 255);
    ledcWrite(7, 255);
  } else {
    ledcWrite(6, 0);
    ledcWrite(7, 0);
  }
  */
}
