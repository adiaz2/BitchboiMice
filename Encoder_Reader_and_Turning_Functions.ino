  int D1=2;     //H Bridge Outputs
  int D2=3;
  int D3=6;
  int D4=7;

  //Encoders
  int LE;       //Left Encoder
  int RE;       //Right Encode
  int LESum=0;  //Left Encoder Sum
  int RESum=0;  //Right Encoder Sum
  int LI;       //Left Instuction
  int RI;       //Right Instructions

  //IR
  int IR1;      //IR 1
  int IR2;      //IR 2
  int IR3;      //IR 3
  int IR4;      //IR 4
  int IR5;      //IR 5
  int THF=765;  //Threshold
  int THS=580;

void setup() {
  
  //Moter
  pinMode(D1, OUTPUT);  //Delcaring Outputs
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);

  //IR
  IR1= analogRead(2);   //Setting IRs to connect to Analog Pin
  IR2= analogRead(3);
  IR3= analogRead(4);
  IR4= analogRead(5);
  IR5= analogRead(6);


  LI=100;
  RI=100;
  
  Serial.begin(9600);
}

void loop() {
  LE= digitalRead(5);
  RE= digitalRead(9);
  LESum+=LE;
  RESum+=RE;
  if(LESum<=LI && RESum<=RI)
  {
    RT();
  }
  else
  {
    STP();
  }
}

//Functions
//====================================================
//Turning Fucntions
void LT() //Left Turn
{
  LCCW();
  RCW();
}
void RT() //Right Turn
{
  RCCW();
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
  digitalWrite(D1, LOW);
  digitalWrite(D2, HIGH);
}
void LCCW()              //Left Counter Clock Wise
{
  digitalWrite(D1, HIGH);
  digitalWrite(D2, LOW);
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

//IR Functions
bool IRC(int x)        //Function to Check if Somthing is Close to IR
{
  if (x==1)
  {
    IR1= analogRead(2);
    if (IR1>THS)
      return true;
    else
      return false;
  }
  if (x==2)
  {
    IR2= analogRead(3);
    if (IR2>TH)
      return true;
    else
      return false;
  }
  if (x==3)
  {
    IR3= analogRead(4);
    if (IR3>THF)
      return true;
    else
      return false;
  }
  if (x==4)
  {
    IR4= analogRead(5);
    if (IR4>TH)
      return true;
     else
      return false;
  }
  if (x==5)
  {
    IR5= analogRead(6);
    if (IR5>THS)
      return true;
    else
      return false;
  }
}

