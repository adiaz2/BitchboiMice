  int D1=6;     //H Bridge Outputs
  int D2=7;
  int D3=8;
  int D4=12;

  //Motor
  int LEnable=9;  //Digital pin 9
  int REnable=10; //Digital pin 10

  //Encoders
  int LEA=2;     //Left Encoder A
  int LEB=4;     //Left Encoder B
  int REA=3;     //Right Encode A
  int REB=5;     //Right Encode B
  int VPL= 0;    //Virtual Position Left
  int VPR= 0;    //Virtual Postion Right    

  //IR
  int IR1;      //IR 1
  int IR2;      //IR 2
  int IR3;      //IR 3
  int IR4;      //IR 4
  int IR5;      //IR 5
  int THF=765;  //Threshold
  int THS=580;

  //Error Correcting setup
  int masterPower=100;
  int slavePower=100;
  int error=0;
  int kp= 2;

  int i=0;


void setup() {
  
  attachInterrupt(digitalPinToInterrupt(REA), isr, FALLING);
  attachInterrupt(digitalPinToInterrupt(LEA), isl, FALLING);
  
  //Moter
  pinMode(D1, OUTPUT);  //Delcaring Outputs
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(LEnable, OUTPUT);
  pinMode(REnable, OUTPUT);

  //IR
  IR1= analogRead(2);   //Setting IRs to connect to Analog Pin
  IR2= analogRead(3);
  IR3= analogRead(4);
  IR4= analogRead(5);
  IR5= analogRead(6);
  
  Serial.begin(9600);
}

void loop() 
{

    analogWrite(LEnable, slavePower);   //Speed
    analogWrite(REnable, masterPower);

//Straight Line Correction
//    error= VPR-VPL;
//    slavePower += error / kp;
//    VPL=0;
//    VPR=0;    
//    delay(1000); 
}

//Functions
//====================================================

//Encoder Inturupt Functions
void isl()                                        //Left Encoder
{
  static unsigned long lastInterruptTimeL = 0;
  unsigned long interruptTimeL= millis();
  if (interruptTimeL - lastInterruptTimeL > 1)
  {
    if(digitalRead(LEB)== LOW)
    {
      VPL++;
    }
    else 
    {
      VPL--;
    }
  }
  lastInterruptTimeL = interruptTimeL;
  Serial.print("Left");
  Serial.print(VPL);
  Serial.print("\n");
 }

void isr()                                        //Right Encoder
{
  static unsigned long lastInterruptTimeR = 0;
  unsigned long interruptTimeR= millis();
  if (interruptTimeR - lastInterruptTimeR > 1)
  {
    if(digitalRead(REB)== LOW)
    {
      VPR--;
    }
    else 
    {
      VPR++;
    }
  }
  lastInterruptTimeR = interruptTimeR;
  Serial.print("Right");
  Serial.print(VPR);
  Serial.print("\n");
 }
 

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
  digitalWrite(D1, LOW);
  digitalWrite(D2, HIGH);

  digitalWrite(D3, HIGH);
  digitalWrite(D4, LOW);
  
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
    if (IR2>THF)
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
    if (IR4>THF)
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
