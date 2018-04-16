#include <iostream>
#include "Mouse.h"
#include "movingFunctions.h"
using namespace std;

void setup(){
	int i = 0;
	while(i<60){
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
			if(hMaze[m+1][n] == -1 && n != mazeSize){
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
		for(int n=0; n<mazeSize+1; n++){
			printf("%d ", maze[m][n]);
		}
	}
	printf("\n\n");
}



