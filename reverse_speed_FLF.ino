float Kp = 1;
float Ki = 0;
float Kd = 0.11;
int mf = 10;
float P, D, elapsedTime, Time, prevTime, prevError;
int pos;
float value;

int leftmax = 255;
int rightmax = 255; 
int leftbase = 80;
int rightbase = 80; 
int leftmotor, rightmotor, motorspeed;

int IN2 = 10;
int IN3 = 11;
int IN1 = 5;
int IN4 = 6;

//int line = 0;
//int bg = 1;
int bg;
int line;

int S1, S2, S3, S4, S5, S6, S7, S8, S9;

void setup() {
  Serial.begin(9600);
  Time = millis();
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN4,OUTPUT);

  pinMode(S1,INPUT);
  pinMode(S2,INPUT);
  pinMode(S3,INPUT);
  pinMode(S3,INPUT);
  pinMode(S5,INPUT);
  pinMode(S6,INPUT);
  pinMode(S7,INPUT);
  pinMode(S8,INPUT);
  pinMode(S9,INPUT);

  delay(1000);
}

void loop() {
  prevTime = Time;
  Time = millis();
  elapsedTime = (Time - prevTime)/1000;
  
  S1=digitalRead(2);
  S2=digitalRead(3);
  S3=digitalRead(4);
  S4=digitalRead(A3);
  S5=digitalRead(A2);
  S6=digitalRead(A1);
  S7=digitalRead(A0);
  S8=digitalRead(9);
  S9=digitalRead(A4);

  if(S1 == 0 && S8 == 0 && S9 == 0 ){
    bg = 0;
    line = 1;
  }
  else{
    bg = 1;
    line = 0;
  }
  
  if(S1 == line && S8 == line && S4 == line && S5 == line){
    pos = 3;
  }
  else if(S8 == line){
    pos = -3;
  }
  else if(S1 == line){
    pos = 3;
  }
  else  if(S7 == line){
    pos = -2;
  }
  else  if(S2 == line){
    pos = 2;
  }
  else  if(S6 == line){
    pos = -1;
  }
  else  if(S3 == line){
    pos = 1;
  }
  else { 
    pos = 0;
  }

  speed_control();

}

void speed_control(){
  int error = pos*mf;
  P = Kp*error;

  D = Kd * ((error - prevError)/elapsedTime);
  Serial.print(D);
  motorspeed = P + D;
  
  int leftmotor = leftbase + motorspeed;
  int rightmotor = rightbase - motorspeed;

if (leftmotor>250){
  leftmotor = 250;
  }
else if (leftmotor<-250){
  leftmotor = -250;
  }  
if (rightmotor>250){
  rightmotor = 250;
  }
else if (rightmotor<-250){
  rightmotor = -250;
  }

  
    Move(leftmotor, rightmotor);

//   Serial.print("   Left: ");
//   Serial.print(leftmotor);
//   Serial.print("     ");
//   Serial.print("Right: ");
//   Serial.print(rightmotor);
//   Serial.println("     ");
   
}

void Move(int leftmotor,int rightmotor){

  if(rightmotor>0){
//    rightmotor = map(rightmotor,0,255,80,255);
    analogWrite(IN2,rightmotor);
    analogWrite(IN1,0);
  }
  else{
//    rightmotor = map(rightmotor,0,-255,-80,-255);
    analogWrite(IN1,abs(rightmotor));
    analogWrite(IN2,0);
  }
  if(leftmotor>0){
//    leftmotor = map(leftmotor,0,255,80,255);
    analogWrite(IN3,leftmotor);
    analogWrite(IN4,0);
  }
  else{
//    leftmotor = map(leftmotor,0,-255,-80,-255);
    analogWrite(IN4,abs(leftmotor));
    analogWrite(IN3,0);
  }


   Serial.print("   Left: ");
   Serial.print(leftmotor);
   Serial.print("     ");
   Serial.print("Right: ");
   Serial.print(rightmotor);
   Serial.println("     ");
   
   
}
