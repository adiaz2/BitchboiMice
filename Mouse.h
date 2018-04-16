#include <iostream>
#include "movingFunctions.h"
using namespace std;


//Constants
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

/*
   0 1 2 3 4 5 6 7
   _ _ _ _ _ _ _ _
0 | | |  _|_ _ _ _| 0
1 | | | |   |_ _  | 1
2 | | |_ _   _ _| | 2
3 | |        _ _ _| 3
4 | |       |_ _ _| 4
5 |     |  _   _  | 5
6 | |     |_| |_| | 6
7 |_|_ _ _ _ _ _ _| 7
   0 1 2 3 4 5 6 7
*/
// int hWalls[9][8] = {
// //0  1  2  3  4  5  6  7
// {-1,-1,-1,-1,-1,-1,-1,-1}, //[0]
// { 0,-1,-1,-1, 0, 0,-1, 0}, //[1]
// { 0,-1, 0,-1,-1,-1,-1, 0}, //[2]
// {-1,-1,-1, 0, 0,-1,-1, 0}, //[3]
// {-1,-1, 0,-1, 0,-1,-1,-1}, //[4]
// { 0,-1, 0, 0,-1,-1, 0,-1}, //[5]
// { 0, 0,-1, 0, 0,-1, 0, 0}, //[6]
// { 0,-1,-1, 0,-1,-1,-1, 0}, //[7]
// {-1,-1,-1,-1,-1,-1,-1,-1}, //[8]
// //0  1  2  3  4  5  6  7
// };

// int vWalls[8][9] = {
// //0  1  2  3  4  5  6  7  8
// {-1, 0, 0, 0, 0,-1, 0,-1,-1}, //[0]
// {-1, 0,-1, 0,-1, 0, 0, 0,-1}, //[1]
// {-1, 0, 0, 0, 0, 0, 0,-1,-1}, //[2]
// {-1, 0, 0,-1,-1,-1, 0, 0,-1}, //[3]
// {-1, 0, 0,-1, 0, 0,-1, 0,-1}, //[4]
// {-1,-1, 0,-1, 0, 0,-1, 0,-1}, //[5]
// {-1,-1, 0,-1,-1, 0,-1,-1,-1}, //[6]
// {-1, 0, 0, 0, 0, 0, 0, 0,-1}, //[7]
// //0  1  2  3  4  5  6  7  8
// };

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
	IRC(1);
	// int left = (currentDirection + 3)%4;
	// if(left == south)
	// 	return(hWalls[Y+1][X] == -1);

	// if(left == west)
	// 	return(vWalls[Y][X] == -1);

	// if(left == north)
	// 	return(hWalls[Y][X] == -1);

	// if(left == east)
	// 	return(vWalls[Y][X+1] == -1);

	// return false;
}

bool frontWall(){
	IRC(2);
	// if(currentDirection == south)
	// 	return(hWalls[Y+1][X] == -1);

	// if(currentDirection == west)
	// 	return(vWalls[Y][X] == -1);

	// if(currentDirection == north)
	// 	return(hWalls[Y][X] == -1);

	// if(currentDirection == east)
	// 	return(vWalls[Y][X+1] == -1);

	// return false;
}

bool rightWall(){
	IRC(3);
	// int right = (currentDirection + 1)%4;
	// if(right == south)
	// 	return(hWalls[Y+1][X] == -1);

	// if(right == west)
	// 	return(vWalls[Y][X] == -1);

	// if(right == north)
	// 	return(hWalls[Y][X] == -1);

	// if(right == east)
	// 	return(vWalls[Y][X+1] == -1);

	// return false;
}

void turnLeft(){
	lTrn();
	currentDirection = (currentDirection + 3)%4;
}

void turnRight(){
	rTrn();
	currentDirection = (currentDirection + 1)%4;
}

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









