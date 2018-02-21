#include <Wire.h>
#include <SPI.h>
#include <math.h>
#include <Adafruit_LSM9DS1.h>
#include <Adafruit_Sensor.h>  // not used in this demo but required!
#include <digitalWriteFast.h>

  // i2c
  Adafruit_LSM9DS1 lsm = Adafruit_LSM9DS1();
  int startDegree = 0;
  int sensitivity = 10;
  int degree;
  int north;
  int northHigh;
  int northLow;
  int east;
  int eastHigh;
  int eastLow;
  int south;
  int southHigh;
  int southLow;
  int west;
  int westHigh;
  int westLow;
  bool firstTime = true;

  #define LSM9DS1_SCK A5
  #define LSM9DS1_MISO 12
  #define LSM9DS1_MOSI A4
  #define LSM9DS1_XGCS 6
  #define LSM9DS1_MCS 5

  
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
  int THF=560;  //Threshold
  int THS=730;

  //Error Correcting setup
  int masterPower=150;
  int slavePower=150;
  int error=0;
  int kp= 10;

  boolean movingForward = false;

void setupSensor()
{
  // 1.) Set the accelerometer range
  lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_2G);
  //lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_4G);
  //lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_8G);
  //lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_16G);
  
  // 2.) Set the magnetometer sensitivity
  lsm.setupMag(lsm.LSM9DS1_MAGGAIN_4GAUSS);
  //lsm.setupMag(lsm.LSM9DS1_MAGGAIN_8GAUSS);
  //lsm.setupMag(lsm.LSM9DS1_MAGGAIN_12GAUSS);
  //lsm.setupMag(lsm.LSM9DS1_MAGGAIN_16GAUSS);

  // 3.) Setup the gyroscope
  lsm.setupGyro(lsm.LSM9DS1_GYROSCALE_245DPS);
  //lsm.setupGyro(lsm.LSM9DS1_GYROSCALE_500DPS);
  //lsm.setupGyro(lsm.LSM9DS1_GYROSCALE_2000DPS);
}

void setup() {
  attachInterrupt(digitalPinToInterrupt(LEA), isl, RISING);  
  attachInterrupt(digitalPinToInterrupt(REA), isr, RISING);
  
  //Moter
  pinMode(D1, OUTPUT);  //Delcaring Outputs
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(LEnable, OUTPUT);
  pinMode(REnable, OUTPUT);

  //IR
  IR1= analogRead(0);   //Setting IRs to connect to Analog Pin
  IR2= analogRead(1);
  IR3= analogRead(2);
  IR4= analogRead(3);
  IR5= analogRead(6);

    while (!Serial) {
    delay(1); // will pause Zero, Leonardo, etc until serial console opens
  }
  
  Serial.println("LSM9DS1 data read demo");
  
  // Try to initialise and warn if we couldn't detect the chip
  if (!lsm.begin())
  {
    Serial.println("Oops ... unable to initialize the LSM9DS1. Check your wiring!");
    while (1);
  }
  Serial.println("Found LSM9DS1 9DOF");

  // helper to just set the default scaling we want, see above!
  setupSensor();

  //startDegree = atan(m.magnetic.y/m.magnetic.x)*180/M_PI);
  
  Serial.begin(9600);
}
int IRV1;
int IRV2;
int IRV3;
int IRV4;
int IRV5;

void loop() 
{
  //IR
  IRV1=analogRead(A0);
  IRV2=analogRead(A1);
  IRV3=analogRead(A2);
  IRV4=analogRead(A3);
  IRV5=analogRead(A7);
//  Serial.print("IR5");
//  Serial.print("\t");
  Serial.println(IRV2);
//  Serial.print("\n");
//  Serial.print("IR4");
  Serial.print("\t");
  Serial.println(IRV4);
  Serial.print("\n");
  Serial.print("\n");
  delay(100);
    lsm.read();  /* ask it to read in the data */ 
  
    /* Get a new sensor event */ 
    sensors_event_t a, m, g, temp;
  
    lsm.getEvent(&a, &m, &g, &temp); 

    analogWrite(REnable, masterPower);
    analogWrite(LEnable, slavePower);   //Speed
//    FW();

//    Serial.println();
  degree = atan(m.magnetic.y/m.magnetic.x)*360/M_PI;
  
  if(degree < 0){
    degree += 360;
  }
  if(degree>360){
    degree -= 360;
  }
  if(firstTime){
    startDegree = degree;
    
    north = startDegree;
    if(north<sensitivity){
      northLow = 360-sensitivity+north;
    }
    else{
      northLow = (north-sensitivity)%360;
    }
    northHigh = (north+sensitivity)%360;
    
    east = (startDegree+90)%360;
    if(east<sensitivity){
      eastLow = 360-sensitivity+east;
    }
    else{
      eastLow = (east-sensitivity)%360;
    }
    eastHigh = (east+sensitivity)%360;
    
    south = (startDegree+180)%360;
    if(south<sensitivity){
      southLow = 360-sensitivity+south;
    }
    else{
      southLow = (south-sensitivity)%360;
    }
    southHigh = (south+sensitivity)%360;
    
    west = (startDegree+270)%360;
    if(west<sensitivity){
      westLow = 360-sensitivity+west;
    }
    else{
      westLow = (west-sensitivity)%360;
    }
    westHigh = (west+sensitivity)%360;
    
    firstTime = false;
  }
  if(degree>northLow && degree<northHigh){
//    Serial.println("North");
  }
  else if(degree>eastLow && degree<eastHigh){
//    Serial.println("East");
  }
  else if(degree>southLow && degree<southHigh){
//    Serial.println("South");
  }
  else if(degree>westLow && degree<westHigh){
//    Serial.println("West");
  }
  
//  Serial.println(degree);
//  Serial.println();
    
   
    

  //Straight Line Correction
//    error= VPR-VPL;
//    slavePower += error *kp;
//    VPL=0;
//    VPR=0;    
//    delay(10); 
}

//Functions
//====================================================

//Encoder Inturupt Functions
void isl()                                        //Left Encoder
{
      VPL++;
//  Serial.print("Left");
  //Serial.print(VPL);
 // Serial.print("\n");
 }

void isr()                                        //Right Encoder
{
  VPR++;
  //Serial.print("Right");
  //Serial.print(VPR);
  //Serial.print("\n");
 }
 

//Turning Fucntions
void LT() //Left Turn
{
  LCCW();
  RCW();
}
void RT() //Right Turn
{
  int currentDegree = degree;
  while(degree){
      RCCW();
      LCW(); 
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

//IR Functions

bool IRC(int x)         //Function to Check if Somthing is Close to IR
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
