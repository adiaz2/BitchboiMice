//#include <iostream>
using namespace std;

//Andrew Constants
  int D1=6;     //H Bridge Outputs
  int D2=7;
  int D3=9;
  int D4=10;

  //Motor
  int LEnable=5;  //Analog pin 5
  int REnable=6; //Analog pin 6
  int MSpeed;

  //Encoders
  int LEA=2;     //Left Encoder A
  int LEB=4;     //Left Encoder B
  int REA=3;     //Right Encode A
  int REB=5;     //Right Encode B
  int VP=0;
  
  int LEV;       //
  int REV;    
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

  int i = 0;
//Alex Constants
int mazeSize = 8;
int GOAL_X = 7;
int GOAL_Y = 0;

int Y = 7; // row
int X = 0; // column

int currentDirection = 2;
int south = 0;
int west  = 1;
int north = 2;
int east  = 3;

bool openPath = false;

int hWalls[9][8] = {
//0  1  2  3  4  5  6  7
{-1,-1,-1,-1,-1,-1,-1,-1}, //[0]
{ 0,-1,-1,-1, 0, 0,-1, 0}, //[1]
{ 0,-1, 0,-1,-1,-1,-1, 0}, //[2]
{-1,-1,-1, 0, 0,-1,-1, 0}, //[3]
{-1,-1, 0,-1, 0,-1,-1,-1}, //[4]
{ 0,-1, 0, 0,-1,-1, 0,-1}, //[5]
{ 0, 0,-1, 0, 0,-1, 0, 0}, //[6]
{ 0,-1,-1, 0,-1,-1,-1, 0}, //[7]
{-1,-1,-1,-1,-1,-1,-1,-1}, //[8]
//0  1  2  3  4  5  6  7
};

int vWalls[8][9] = {
//0  1  2  3  4  5  6  7  8
{-1, 0, 0, 0, 0,-1, 0,-1,-1}, //[0]
{-1, 0,-1, 0,-1, 0, 0, 0,-1}, //[1]
{-1, 0, 0, 0, 0, 0, 0,-1,-1}, //[2]
{-1, 0, 0,-1,-1,-1, 0, 0,-1}, //[3]
{-1, 0, 0,-1, 0, 0,-1, 0,-1}, //[4]
{-1,-1, 0,-1, 0, 0,-1, 0,-1}, //[5]
{-1,-1, 0,-1,-1, 0,-1,-1,-1}, //[6]
{-1, 0, 0, 0, 0, 0, 0, 0,-1}, //[7]
//0  1  2  3  4  5  6  7  8
};

int hMaze[9][8] = {
//0  1  2  3  4  5  6  7
{-1,-1,-1,-1,-1,-1,-1,-1}, //[0]
{ 0, 0, 0, 0, 0, 0, 0, 0}, //[1]
{ 0, 0, 0, 0, 0, 0, 0, 0}, //[2]
{ 0, 0, 0, 0, 0, 0, 0, 0}, //[3]
{ 0, 0, 0, 0, 0, 0, 0, 0}, //[4]
{ 0, 0, 0, 0, 0, 0, 0, 0}, //[5]
{ 0, 0, 0, 0, 0, 0, 0, 0}, //[6]
{ 0, 0, 0, 0, 0, 0, 0, 0}, //[7]
{-1,-1,-1,-1,-1,-1,-1,-1}, //[8]
//0  1  2  3  4  5  6  7
};

int vMaze[8][9] = {
//0  1  2  3  4  5  6  7  8
{-1, 0, 0, 0, 0, 0, 0, 0,-1}, //[0]
{-1, 0, 0, 0, 0, 0, 0, 0,-1}, //[1]
{-1, 0, 0, 0, 0, 0, 0, 0,-1}, //[2]
{-1, 0, 0, 0, 0, 0, 0, 0,-1}, //[3]
{-1, 0, 0, 0, 0, 0, 0, 0,-1}, //[4]
{-1, 0, 0, 0, 0, 0, 0, 0,-1}, //[5]
{-1, 0, 0, 0, 0, 0, 0, 0,-1}, //[6]
{-1, 0, 0, 0, 0, 0, 0, 0,-1}, //[7]
//0  1  2  3  4  5  6  7  8
};

int maze[8][8] = {
//0  1  2  3  4  5  6  7
{ 0, 0, 0, 0, 0, 0, 0, 0}, //[0]
{ 0, 0, 0, 0, 0, 0, 0, 0}, //[1]
{ 0, 0, 0, 0, 0, 0, 0, 0}, //[2]
{ 0, 0, 0, 0, 0, 0, 0, 0}, //[3]
{ 0, 0, 0, 0, 0, 0, 0, 0}, //[4]
{ 0, 0, 0, 0, 0, 0, 0, 0}, //[5]
{ 0, 0, 0, 0, 0, 0, 0, 0}, //[6]
{ 2, 0, 0, 0, 0, 0, 0, 0}, //[7]
//0  1  2  3  4  5  6  7
};





//Functions
bool leftWall(){
  int left = (currentDirection + 3)%4;
  if(left == south)
    return(hWalls[Y+1][X] == -1);

  if(left == west)
    return(vWalls[Y][X] == -1);

  if(left == north)
    return(hWalls[Y][X] == -1);

  if(left == east)
    return(vWalls[Y][X+1] == -1);

  return false;
}

bool frontWall(){
  if(currentDirection == south)
    return(hWalls[Y+1][X] == -1);

  if(currentDirection == west)
    return(vWalls[Y][X] == -1);

  if(currentDirection == north)
    return(hWalls[Y][X] == -1);

  if(currentDirection == east)
    return(vWalls[Y][X+1] == -1);

  return false;
}

bool rightWall(){
  int right = (currentDirection + 1)%4;
  if(right == south)
    return(hWalls[Y+1][X] == -1);

  if(right == west)
    return(vWalls[Y][X] == -1);

  if(right == north)
    return(hWalls[Y][X] == -1);

  if(right == east)
    return(vWalls[Y][X+1] == -1);

  return false;
}

//void turnLeft(){
//  currentDirection = (currentDirection + 3)%4;
//}
//
//void turnRight(){
//  currentDirection = (currentDirection + 1)%4;
//}

void turn180(){
  turnRight();
  turnRight();
}

//finds any adjacent walls detectable by the IR sensors and marks them as walls
void readSurroundings(){
  if(currentDirection == west){
    //check what's west and record it
    if(frontWall()){
      vMaze[Y][X] = -1; //west
    }
    else{
      vMaze[Y][X] = 1;//west
    }
    //check what's south and record it
    if(leftWall()){
      hMaze[Y+1][X] = -1;
    }
    else{
      hMaze[Y+1][X] = 1;
    }
    //Check what's north and record it
    if(rightWall()){
      hMaze[Y][X] = -1;
    }
    else{
      hMaze[Y][X] = 1;
    }
  }
  else if(currentDirection == east){
    //check what's east and record it
    if(frontWall()){
      vMaze[Y][X+1] = -1;
    }
    else{
      vMaze[Y][X+1] = 1;
    }
    //check what's north and record it
    if(leftWall()){
      hMaze[Y][X] = -1;
    }
    else{
      hMaze[Y][X] = 1;
    }
    //Check what's south and record it
    if(rightWall()){
      hMaze[Y+1][X] = -1;
    }
    else{
      hMaze[Y+1][X] = 1;
    }
  }
  else if(currentDirection == south){
    //check what's south and record it
    if(frontWall()){
      hMaze[Y+1][X] = -1;
    }
    else{
      hMaze[Y+1][X] = 1;
    }
    //check what's east and record it
    if(leftWall()){
      vMaze[Y][X+1] = -1;
    }
    else{
      vMaze[Y][X+1] = 1;
    }
    //Check what's west and record it
    if(rightWall()){
      vMaze[Y][X] = -1; //west
    }
    else{
      vMaze[Y][X] = 1;//west
    }
  }
  else if(currentDirection == north){
    //check what's north and record it
    if(frontWall()){
      hMaze[Y][X] = -1;
    }
    else{
      hMaze[Y][X] = 1;
    }
    //check what's east and record it
    if(leftWall()){
      vMaze[Y][X] = -1;
    }
    else{
      vMaze[Y][X] = 1;
    }
    //Check what's west and record it
    if(rightWall()){
      vMaze[Y][X+1] = -1; //west
    }
    else{
      vMaze[Y][X+1] = 1;//west
    }
  }

}

void nextUnit(){
  moveForward();
  if(currentDirection == west)
    X--;
  else if(currentDirection == east)
    X++;
  else if(currentDirection == south)
    Y++;
  else if(currentDirection == north)
    Y--;
  if(maze[Y][X] >= 2){
    //printf("\n%d",maze[Y][X]);
    maze[Y][X]++;
    //printf("%d\n",maze[Y][X]);

  }
  else{
    maze[Y][X] = 2;
  }
  delay(1000);
  //readSurroundings();
}


void newTile(){
  readSurroundings();

  //if you are at the end
  if(X == GOAL_X && Y == GOAL_Y){
    return;
  }
  //first check if you can keep going forward
  if(currentDirection == east){
    if(!leftWall() && (maze[Y-1][X]<maze[Y][X+1] || frontWall())){
      turnLeft();
      nextUnit();
      printf("North\n");
      return;
    }
    if(!frontWall()){
      nextUnit();
      printf("East\n");
      return;
    }
    if(!leftWall() && maze[Y-1][X] < 2){ //if you can go north instead of east, do it
      turnLeft();
      nextUnit();
      printf("North\n");
      return;
    }
    //you cannot go east or north, so check if there is a path that will take you north behind you
    for(int i = Y; i<mazeSize && vMaze[Y][X-i] != -1; i++){
      if(hMaze[Y][X] == 1){
        openPath = true;
        turn180();
        nextUnit();
        printf("West\n");
        return;
      }
    }
    if(!rightWall()){
      turnRight();
      nextUnit();
      printf("South\n");
      return;
    }
    if(!leftWall()){ //if you can go north instead of east, do it
      turnLeft();
      nextUnit();
      printf("North\n");
      return;
    }
    else{
      turn180();
      nextUnit();
      printf("West\n");
      return;
    }

  }
  if(currentDirection == north){
    if(!rightWall() && (maze[Y][X+1]<maze[Y-1][X] || frontWall())){
      turnRight();
      nextUnit();
      printf("East\n");
      return;
    }
    if(!frontWall()){
      nextUnit();
      printf("North\n");
      return;
    }
    if(!rightWall() && maze[Y][X+1] < 2){ //if you can go east instead of north, do it
      turnRight();
      nextUnit();
      printf("East\n");
      return;
    }

    //you cannot go east or north, so check if there is a path that will take you north behind you
    for(int i = 0; i<mazeSize && hMaze[Y+i+1][X] != -1; i++){
      if(vMaze[Y][X+i+1] == 1){
        openPath = true;
        turn180();
        nextUnit();
        printf("South\n");
        return;
      }
    }

    if(!leftWall()){
      turnLeft();
      nextUnit();
      printf("West\n");
      return;
    }
    if(!rightWall()){ //if you can go east instead of north, do it
      turnRight();
      nextUnit();
      printf("East\n");
      return;
    }
    else{
      turn180();
      nextUnit();
      printf("South\n");
      return;
    }
  }

  //if you are facing west,
  if(currentDirection == west){
    //try to go north
    if(!rightWall() && maze[Y-1][X] < 2){
      turnRight();
      nextUnit();
      openPath = false;
      printf("North\n");
      return;
    }
    //if you know there is an open path ahead or there is a wall south, move west
    if((openPath || leftWall()) && !frontWall()){
      nextUnit();
      printf("West\n");
      return;
    }
    
    else if(!frontWall() && maze[Y][X-1] < 2){
      nextUnit();
      printf("West\n");
      return;
    }

    //if there is no wall south and no open path further west
    else if(!leftWall() && maze[Y+1][X] < 2){
      turnLeft();
      nextUnit();
      openPath = false;
      printf("South\n");
      return;
    }
    else if(!leftWall()){
      turnLeft();
      nextUnit();
      openPath = false;
      printf("South\n");
      return;
    }
    if(!rightWall()){
      turnRight();
      nextUnit();
      printf("North\n");
      return;
    }
    else{
      turn180();
      if(!frontWall()){
        nextUnit();
        openPath = false;
        printf("East\n");
      }
      return;
    }


  }

  if(currentDirection == south){
    //try to go east
    if(!leftWall() && maze[Y][X+1] < 2){
      turnLeft();
      nextUnit();
      openPath = false;
      printf("East\n");
      return;
    }
    //if you know there is an open path ahead or there is a wall west, move south
    if((openPath || rightWall()) && !frontWall()){
      nextUnit();
      printf("South\n");
      return;
    }
    else if(!frontWall() && maze[Y+1][X] < 2){
      nextUnit();
      printf("South\n");
      return;
    }
    //if there is no wall west and no open path further south
    else if(!rightWall() && maze[Y+1][X] < 2){
      turnRight();
      nextUnit();
      openPath = false;
      printf("West\n");
      return;
    }
    
    else if(!rightWall()){
      turnRight();
      nextUnit();
      openPath = false;
      printf("West\n");
      return;
    }
    else if(!leftWall()){
      turnLeft();
      nextUnit();
      openPath = false;
      printf("East\n");
      return;
    }
    else{
      turn180();
      if(!frontWall()){
        nextUnit();
        openPath = false;
        printf("North\n");
      }
      return;
    }

  }
}

//Functions
//====================================================
void moveForward(){
  //VP=0;
  int TS = 70; //the turn sensitivity
  while(VP != TS){
      if(VP<TS)
        {
          FW();
        }
       else if(VP>TS)
        {
          BW();
        }
  }
  STP();
  VP = 0; 
  
}
void turnLeft(){
  //VP=0;
  currentDirection = (currentDirection + 3)%4;
  int TS = -20; //the turn sensitivity
  while(VP != TS){
      if(VP>TS)
        {
          LT();
        }
       else if(VP<TS)
        {
          RT();
        }
  }
  STP();
  VP = 0; 
        
}

void turnRight(){
  //VP=0;
  currentDirection = (currentDirection + 1)%4;
  int TS = 20; //the turn sensitivity
  while(VP != TS){
      if(VP<TS)
        {
          RT();
        }
       else if(VP>TS)
        {
         LT();
        }
  }
  STP();
  VP = 0; 
        
}




void isr()
{
  static unsigned long lastInterruptTime = 0;
  unsigned long interruptTime= millis();
  if (interruptTime - lastInterruptTime > 1)
  {
    if(digitalRead(LEB)== LOW)
    {
      VP++;
    }
    else 
    {
      VP--;
    }
  }
  lastInterruptTime = interruptTime;
  Serial.print(VP);
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
void setup() {

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

  attachInterrupt(digitalPinToInterrupt(LEA), isr, LOW);
  
  
  Serial.begin(9600);

  
  // put your setup code here, to run once:
  int i = 0;
  while(!(X == GOAL_X && Y == GOAL_Y)){
    newTile();
    printf("%d %d\n%d moves\n", X,Y,i);
    i++;
  }
  printf("%d moves used\n", i);
  printf("Memorized maze:\n");
  for(int j = 0; j<mazeSize; j++){
    printf(" _");
  }
  for(int m = 0; m<mazeSize; m++){
    printf("\n");
    for(int n=0; n<mazeSize+1; n++){
      if(vMaze[m][n] == -1){
        printf("|");
      }
      else{
        printf(" ");
      }
      if(n != mazeSize && hMaze[m+1][n] == -1){
        printf("_");
      }
      else{
        printf(" ");
      }

    }
  }
  printf("\n");

  for(int m = 0; m<mazeSize; m++){
    printf("\n");
    for(int n=0; n<mazeSize; n++){
      printf("%d ", maze[m][n]);
    }
  }
  printf("\n\n");
}

void loop() {
  // put your main code here, to run repeatedly:

}
