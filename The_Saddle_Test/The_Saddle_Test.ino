#define ButtonOne 33
#define ButtonTwo 26
#define PWMLeft 18
#define PWMRight 19
#define DIRLeft 23
#define DIRRight 25
#define XAxis 4
#define YAxis 14

boolean val = true;

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

  //Serial.print(analogRead(ButtonOne));
  //Serial.print("one");
  //Serial.println();
  //Serial.print(analogRead(ButtonTwo));
  //Serial.print("two");
  //Serial.println();
  Serial.println(analogRead(XAxis));
  Serial.println(analogRead(YAxis));

  ledcWrite(6, (map(analogRead(YAxis), 1780, 4095, 0, 255)));
  ledcWrite(10,255);

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
