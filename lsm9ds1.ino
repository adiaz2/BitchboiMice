#include <Wire.h>
#include <SPI.h>
#include <math.h>
#include <Adafruit_LSM9DS1.h>
#include <Adafruit_Sensor.h>  // not used in this demo but required!

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
// You can also use software SPI
//Adafruit_LSM9DS1 lsm = Adafruit_LSM9DS1(LSM9DS1_SCK, LSM9DS1_MISO, LSM9DS1_MOSI, LSM9DS1_XGCS, LSM9DS1_MCS);
// Or hardware SPI! In this case, only CS pins are passed in
//Adafruit_LSM9DS1 lsm = Adafruit_LSM9DS1(LSM9DS1_XGCS, LSM9DS1_MCS);


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


void setup() 
{
  Serial.begin(115200);

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
}

void loop() 
{
  lsm.read();  /* ask it to read in the data */ 

  /* Get a new sensor event */ 
  sensors_event_t a, m, g, temp;

  lsm.getEvent(&a, &m, &g, &temp); 

  

//  Serial.print("Accel X: "); Serial.print(a.acceleration.x); Serial.print(" m/s^2");
//  Serial.print("\tY: "); Serial.print(a.acceleration.y);     Serial.print(" m/s^2 ");
//  Serial.print("\tZ: "); Serial.print(a.acceleration.z);     Serial.println(" m/s^2 ");
//
//  Serial.print("Mag X: "); Serial.print(m.magnetic.x);   Serial.print(" gauss");
//  Serial.print("\tY: "); Serial.print(m.magnetic.y);     Serial.print(" gauss");
//  Serial.print("\tZ: "); Serial.print(m.magnetic.z);     Serial.println(" gauss");
//
//  Serial.print("Gyro X: "); Serial.print(g.gyro.x);   Serial.print(" dps");
//  Serial.print("\tY: "); Serial.print(g.gyro.y);      Serial.print(" dps");
//  Serial.print("\tZ: "); Serial.print(g.gyro.z);      Serial.println(" dps");
  Serial.println();
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
    Serial.println("North");
  }
  else if(degree>eastLow && degree<eastHigh){
    Serial.println("East");
  }
  else if(degree>southLow && degree<southHigh){
    Serial.println("South");
  }
  else if(degree>westLow && degree<westHigh){
    Serial.println("West");
  }
  
  Serial.println(degree);
  Serial.println();
  delay(200);
}
