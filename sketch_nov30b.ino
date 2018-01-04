int FIR;      //Front IR
int LIR;      //Left IR
int RIR;      //Right IR
int D1=1;
int D2=2;
int D3=3;
int D4=4;
int D5 = 5;
int Th=1000;  //Threshhold

void setup()
{
  pinMode(D1, OUTPUT);//Delcaring Outputs
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  Serial.begin(9600); //initialize baud rate to 9600
}

void loop()
{
  FIR= analogRead(0);  //read value from analog pin 1 
  LIR= analogRead(1);
  RIR= analogRead(2);
  Serial.println(FIR); //print the value on the screen
  Serial.println(LIR);
  Serial.println(RIR);
  if (FIR<Th)
  {
    BW();
  }    
  delay(1);
}


//Turning Fucntions
void LT() //Left Turn
{
  LSTP();
  RCW();
}
void RT() //Right Turn
{
  RSTP();
  LCW();
}
void FW() //Foward
{
  LCW();
  RCW();
}
void BW() //Backwards
{
  LCCW();
  RCCW();
}
void STP() //Stop
{
  LSTP();
  RSTP();
}


//Wheel Functions

//Left Functions 
void LCW()               //Left Clock Wise
{
  digitalWrite(D1, HIGH);
  digitalWrite(D2, LOW);
}
void LCCW()              //Left Counter Clock Wise
{
  digitalWrite(D1, LOW);
  digitalWrite(D2, HIGH);
}
void LSTP()              //Left Stop
{
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
}


//Right Functions
void RCW()              //Right Clock Wise
{
  digitalWrite(D3, HIGH);
  digitalWrite(D4, LOW);
}
void RCCW()             //Right Counter Clock Wise
{
  digitalWrite(D3, LOW);
  digitalWrite(D4, HIGH);
}
void RSTP()             //Right Stop
{
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);
}


