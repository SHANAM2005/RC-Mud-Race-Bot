int ch4 = 1500;
int ch2 = 1500;

int speed = 0, steering = 0;
int left1 = 11; 
int right1 = 9;
int leftEn = 10;
int rightEn = 6;

int thresX = 30;
int thresY = 15;
int turnThres = 30;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
ch4 = pulseIn(5, HIGH);  // Connect CH1 to digital pin 3
ch2 = pulseIn(3, HIGH);  // Connect CH2 to digital pin 5


speed = map(ch2,1000,2000,-255,255);
steering = map(ch4,1000,2000,120,-120);

if (abs(speed) > thresX)
  {
    if (speed < 0)
    {
      speed = abs(speed);
      moveBackward();
    } else {
      moveForward();
    }
  }
  else if (abs(steering) > turnThres)
  {
     if(steering < 0)
     {
      steering = abs(steering);
      turnLeft();
     }
     else
     {
      turnRight();
       
     }
  }
  else
  {
    stop();
  }
  delay(50);
}

void stop()
{
  digitalWrite(left1,LOW);
  digitalWrite(leftEn,LOW);
  digitalWrite(right1,LOW);
  digitalWrite(rightEn,LOW);
  Serial.println("stop");
}

void moveForward()
{ 
  if (abs(steering) > thresY)
  {
    if (speed+steering >= 0){
      digitalWrite(right1,LOW);
      analogWrite(rightEn,min(255,speed+steering));
    } else {
      digitalWrite(rightEn,LOW);
      analogWrite(right1,abs(min(255,steering+speed)));
    }

    if (speed-steering >= 0){
      digitalWrite(left1,LOW);
      analogWrite(leftEn,min(255,speed-steering));
    } else {
      digitalWrite(leftEn,LOW);
      analogWrite(left1,abs(min(255,steering-speed)));
    }
   Serial.print("forward with rSp: ");
   Serial.print(min(255,speed+steering));
   Serial.print(" and lsp: ");
   Serial.println(min(255,speed-steering));
  } else
  {
   digitalWrite(left1,LOW);
   digitalWrite(right1,LOW);
   analogWrite(rightEn,min(255,speed));
   analogWrite(leftEn,min(255,speed));

   Serial.print("forward with rSp: ");
   Serial.print(speed);
   Serial.print(" and lsp: ");
   Serial.println(speed);
  }
}

void moveBackward()
{
  if (abs(steering) > thresY)
  {
   if (speed+steering >= 10){
      digitalWrite(rightEn,LOW);
      analogWrite(right1,min(255,speed+steering));
    } else if (speed+steering < -20){
      digitalWrite(right1,LOW);
      analogWrite(rightEn,abs(min(255,steering+speed)));
    }

    if (speed-steering >= 10){
      digitalWrite(leftEn,LOW);
      analogWrite(left1,min(255,speed-steering));
    } else if(speed - steering < -20) {
      digitalWrite(left1,LOW);
      analogWrite(leftEn,abs(min(255,steering-speed)));
    } 

   Serial.print("backward with rSp: ");
   Serial.print(min(255,speed+steering));
   Serial.print(" and lsp: ");
   Serial.println(min(255,speed-steering));
  } else
  {
    digitalWrite(leftEn,LOW);
   digitalWrite(rightEn,LOW);
   analogWrite(right1,min(255,speed));
   analogWrite(left1,min(255,speed));

   Serial.print("backward with rSp: ");
   Serial.print(speed);
   Serial.print(" and lsp: ");
   Serial.println(speed);
  }
}

void turnLeft()
{
   digitalWrite(right1,LOW);
   digitalWrite(leftEn,LOW);
   analogWrite(left1,abs(steering));
   analogWrite(rightEn,abs(steering));
  
  Serial.print("right with rSp: ");
   Serial.println(steering);
}

void turnRight()
{
   digitalWrite(rightEn,LOW);
   digitalWrite(left1,LOW);
   analogWrite(leftEn,abs(steering));
   analogWrite(right1,abs(steering));

  Serial.print("left with rSp: ");
   Serial.println(steering); 
}