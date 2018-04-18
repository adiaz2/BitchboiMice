#include <Wire.h>
#include <SPI.h>
#include <math.h>
#include <Adafruit_LSM9DS1.h>
#include <Adafruit_Sensor.h>  // not used in this demo but required!
#include <digitalWriteFast.h>



  
  int D1=6;     //H Bridge Outputs
  int D2=7;
  int D3=8;#include <Wire.h>
#include <SPI.h>
#include <math.h>
#include <Adafruit_LSM9DS1.h>
#include <Adafruit_Sensor.h>  // not used in this demo but required!
#include <digitalWriteFast.h>



  
  int D1=6;     //H Bridge Outputs
  int D2=7;
  int D3=8;
  int D4=12;

  //Motor
  int LEnable=9;  //Digital pin 9
  int REnable=10; //Digital pin 10

  //IR
  int IR1;      //IR 1
  int IR2;      //IR 3
  int IR3;      //IR 5
  
  int THF=420;  //Threshold
  int THL=495;
  int THR=480;
  
  

  //Encoders
  int LEA=2;     //Left Encoder A
  int LEB=4;     //Left Encoder B
  int REA=3;     //Right Encode A
  int REB=5;     //Right Encode B
  int VPL= 0;    //Virtual Position Left
  int VPR= 0;    //Virtual Postion Right
  int VPMin = 55;
  int VPMax = 65;
  int Master= 180;
  int Slave= 180;
 
  int error=0;
  int kp=1;





void moveForward(){
  FW();
  while(VPL < 160 || VPR < 160){
    error= VPL-VPR;
  Slave += error/kp;
  if (Slave>255)
  {
    Slave=255;
  }
  if (Slave<25)
  {
    Slave=25;
  }

 analogWrite(LEnable, Master);
 analogWrite(REnable, Slave);
 
    delay(10);
  }
  VPL=0;
  VPR=0;

  STP();
}

void lTrn()
{
  STP();
  Master = 180;
  Slave = 180;
  analogWrite(LEnable, Master);
  analogWrite(REnable, Slave);
  boolean rightWheel = false;
  boolean leftWheel = false;
  
   while(rightWheel == false || leftWheel == false){    

    if ((VPR > VPMin) && (VPR < VPMax))
    {
      RSTP();
      rightWheel = true;
    }
    else if(VPR<VPMin && !rightWheel)
    {
      RCW();
    }

    else if(VPR > VPMax && !rightWheel)
    {
     RCCW(); 
    }
    
    
    if(VPL < -1*VPMin && VPL > -1*VPMax)
    {
      LSTP();
      leftWheel = true;
    }
    else if(VPL>-1*VPMin && !leftWheel)
    {
      
      LCCW();
    }
    else if (VPL < -1*VPMax && !leftWheel)
    {
      LCW();
    }
    
  }
  VPR = 0;
  VPL = 0;
  return;
 
}
void rTrn()
{
  Master = 200;
  Slave = 200;
  analogWrite(LEnable, Master);
  analogWrite(REnable, Slave);
  boolean rightWheel = false;
  boolean leftWheel = false;
  VPR = 0;
  VPL = 0;

  
   while(rightWheel == false || leftWheel == false){

    if ((VPL > VPMin) && (VPL < VPMax))
    {
      LSTP();
      leftWheel = true;
    }
    else if(VPL<VPMin && !leftWheel)
    {
      Serial.print("Nigga\n");
      LCW();
    }

    else if(VPL > VPMax && !leftWheel)
    {
     LCCW(); 
    }
    
    
    if(VPR < -1*VPMin && VPR > -1*VPMax)
    {
      RSTP();
      rightWheel = true;
    }
    else if(VPR>-1*VPMin && !rightWheel)
    {
      
      RCCW();
    }
    else if (VPR < -1*VPMax && !rightWheel)
    {
      RCW();
    }
    
  }
  VPR = 0;
  VPL = 0;
  return;
 
}

//IR Functions

bool IRC(int x)         //Function to Check if Somthing is Close to IR
{
  if (x==1)
  {
    IR1= analogRead(0);
    if (IR1<THL)
      return true;
    else
      return false;
  }
  if (x==2)
  {
    IR2= analogRead(2);
    if (IR2<THF)
      return true;
    else
      return false;
  }
  if (x==3)
  {
    IR3= analogRead(7);
    if (IR3<THR)
      return true;
    else
      return false;
  }
}





//Other Functions

  void isl()                                        //Left Encoder
  {
    if (digitalReadFast(LEB)== HIGH)
    {
      VPL++;
    }
    else
    {
      VPL--;
    }

    
   }

  void isr()                                        //Left Encoder
  {
    if (digitalReadFast(REB)== LOW)
    {
      VPR++;
    }
    else
    {
      VPR--;
    }
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
  
  void mouseSetup() {
  // put your setup code here, to run once:
  attachInterrupt(digitalPinToInterrupt(LEA), isl, RISING);  
  attachInterrupt(digitalPinToInterrupt(REA), isr, RISING);
  Serial.begin(9600);
  analogWrite(LEnable, Master);
  analogWrite(REnable, Slave);
  VPL=0;
  VPR=0;
    delay(5);
  
  analogWrite(LEnable, 220);
  analogWrite(REnable, 220);


Serial.begin(9600);

}

  int D4=12;

  //Motor
  int LEnable=9;  //Digital pin 9
  int REnable=10; //Digital pin 10

  //IR
  int IR1;      //IR 1
  int IR2;      //IR 3
  int IR3;      //IR 5
  
  int THF=420;  //Threshold
  int THL=495;
  int THR=480;
  
  

  //Encoders
  int LEA=2;     //Left Encoder A
  int LEB=4;     //Left Encoder B
  int REA=3;     //Right Encode A
  int REB=5;     //Right Encode B
  int VPL= 0;    //Virtual Position Left
  int VPR= 0;    //Virtual Postion Right
  int VPMin = 55;
  int VPMax = 65;
  int Master= 180;
  int Slave= 180;
 
  int error=0;
  int kp=1;


void mouseSetup() {
  // put your setup code here, to run once:
  attachInterrupt(digitalPinToInterrupt(LEA), isl, RISING);  
  attachInterrupt(digitalPinToInterrupt(REA), isr, RISING);
  Serial.begin(9600);
  analogWrite(LEnable, Master);
  analogWrite(REnable, Slave);
  VPL=0;
  VPR=0;
    delay(5);
  
  analogWrite(LEnable, 220);
  analogWrite(REnable, 220);


Serial.begin(9600);

}


void moveForward(){
  FW();
  while(VPL < 160 || VPR < 160){
    error= VPL-VPR;
  Slave += error/kp;
  if (Slave>255)
  {
    Slave=255;
  }
  if (Slave<25)
  {
    Slave=25;
  }

 analogWrite(LEnable, Master);
 analogWrite(REnable, Slave);
 
    delay(10);
  }
  VPL=0;
  VPR=0;

  STP();
}

void lTrn()
{
  STP();
  Master = 180;
  Slave = 180;
  analogWrite(LEnable, Master);
  analogWrite(REnable, Slave);
  boolean rightWheel = false;
  boolean leftWheel = false;
  
   while(rightWheel == false || leftWheel == false){    

    if ((VPR > VPMin) && (VPR < VPMax))
    {
      RSTP();
      rightWheel = true;
    }
    else if(VPR<VPMin && !rightWheel)
    {
      RCW();
    }

    else if(VPR > VPMax && !rightWheel)
    {
     RCCW(); 
    }
    
    
    if(VPL < -1*VPMin && VPL > -1*VPMax)
    {
      LSTP();
      leftWheel = true;
    }
    else if(VPL>-1*VPMin && !leftWheel)
    {
      
      LCCW();
    }
    else if (VPL < -1*VPMax && !leftWheel)
    {
      LCW();
    }
    
  }
  VPR = 0;
  VPL = 0;
  return;
 
}
void rTrn()
{
  Master = 200;
  Slave = 200;
  analogWrite(LEnable, Master);
  analogWrite(REnable, Slave);
  boolean rightWheel = false;
  boolean leftWheel = false;
  VPR = 0;
  VPL = 0;

  
   while(rightWheel == false || leftWheel == false){

    if ((VPL > VPMin) && (VPL < VPMax))
    {
      LSTP();
      leftWheel = true;
    }
    else if(VPL<VPMin && !leftWheel)
    {
      Serial.print("Nigga\n");
      LCW();
    }

    else if(VPL > VPMax && !leftWheel)
    {
     LCCW(); 
    }
    
    
    if(VPR < -1*VPMin && VPR > -1*VPMax)
    {
      RSTP();
      rightWheel = true;
    }
    else if(VPR>-1*VPMin && !rightWheel)
    {
      
      RCCW();
    }
    else if (VPR < -1*VPMax && !rightWheel)
    {
      RCW();
    }
    
  }
  VPR = 0;
  VPL = 0;
  return;
 
}

//IR Functions

bool IRC(int x)         //Function to Check if Somthing is Close to IR
{
  if (x==1)
  {
    IR1= analogRead(0);
    if (IR1<THL)
      return true;
    else
      return false;
  }
  if (x==2)
  {
    IR2= analogRead(2);
    if (IR2<THF)
      return true;
    else
      return false;
  }
  if (x==3)
  {
    IR3= analogRead(7);
    if (IR3<THR)
      return true;
    else
      return false;
  }
}





//Other Functions

  void isl()                                        //Left Encoder
  {
    if (digitalReadFast(LEB)== HIGH)
    {
      VPL++;
    }
    else
    {
      VPL--;
    }

    
   }

  void isr()                                        //Left Encoder
  {
    if (digitalReadFast(REB)== LOW)
    {
      VPR++;
    }
    else
    {
      VPR--;
    }
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
