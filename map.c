// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#include <stdlib.h>
#include <stdio.h>

#include "defines.h"
#include "colours.h"
#include "map.h"


extern char *map, *dot_map;
extern int width, height, dotCount;



int cordIdxCvt (int x,int y){

    return (y * 9 + (x));
}

int move_actor(int *y, int *x, char direction, int eat_dots){

    //declaring variables, includes converted x and y cords into an idx and the direction vector and the new cords after movement
    int actorIdx = cordIdxCvt(*x, *y);

    //printf("\nORIGINAL IDX:%d", actorIdx);
    int newActorCords;
    int tempX;
    int tempY;

    //converting direction to int values
    switch(direction) {
        case UP:
            // Move up means decrement the Y value
            tempY = *y - 1;
            tempX = *x;
            break;
        case DOWN:
            // Move down means increment the Y value
            tempY = *y + 1;
            tempX = *x;
            break;
        case RIGHT:
            // Move right means increment the X value
            tempX = *x + 1;
            tempY = *y;
            break;
        case LEFT:
            // Move left means decrement the X value
            tempX = *x - 1;
            tempY = *y;
            break;
        default:
            //  Handle any unexpected direction values
            return MOVED_INVALID_DIRECTION;
    }


//    if (eat_dots == 0) {
//        //printf("\nTEMP VALUES %d %d\nWALL VALUE:%d\n", tempX, tempY,is_wall(tempX,tempY));
//
//    }
    fflush(stdout);
    //checks if new position is a wall
    if (is_wall(tempX,tempY)){
        return MOVED_WALL;
    }

    //


        //if it is a valid position (contains no walls) then it moves the actor and updates all the corresponding variables.

    if (eat_dots == 1 && dot_map[actorIdx]== '.') {
    //dot_map[cordIdxCvt(tempX, tempY)]

        dot_map[actorIdx] = ' ';
        dotCount--;
    }
    map[actorIdx] = dot_map[actorIdx];
    //printf("\nNEW CORDS (%d, %d) IDX: %d", tempX, tempY,cordIdxCvt(tempX, tempY));
    newActorCords = cordIdxCvt(tempX, tempY);

    if (eat_dots == 1)
        map[newActorCords] = 'P';
    else if (eat_dots == 0)
        map[newActorCords] = 'G';

    *y = tempY;
    *x = tempX;

    return MOVED_OKAY;

}


int is_wall(int x, int y) {

    int validMove;
    int idx = cordIdxCvt(x,y);
    if (x >= 0 && x < 9 && y < 9 && y >= 0)
        validMove = 1;
    else
        validMove = 0;

    if (map[cordIdxCvt(x,y)] == WALL || validMove == 0) {

        return 1;


    } else
        return 0;

}

int validMovement (int x, int y, char direction){
    switch (direction){ //Changing the coordinate depending on the type of movement require3d
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
    }
    return is_wall(x, y);

}

char * load_map(char * filename, int *map_height, int *map_width) {
    int dotIndex = 0; //used for testing
    FILE *fMap = NULL;
    fMap = fopen(filename, "r");
    if (fMap == NULL) { //If the map file is not available
        printf("File not found.\n");

        //closing the file
        fclose(fMap);
        return NULL; //Non-zero return to show error has occurred
    }

    //Creating the holding and map points
    char * pMap = (char*) malloc((width)*(height)*sizeof(char*));
    char * pHold = (char*) malloc(sizeof(char*));
    if (pMap == NULL || pHold == NULL) { //If there is no memory to allocate them to
        //message to the user
        printf("Memory is not available");
        //Closing the file and free the space
        fclose(fMap);
        free(pMap);
        free(pHold);
        return NULL; //indicating error has occured
    }


    //Getting the real map
    for (int i = 0; i < (*map_height); i++){
        //Loading the map
//
        for (int j = 0; j < *map_width; j++){
            fscanf(fMap, "%c", &pHold[0]); // Getting the value from the with a holding value
            if (i*height+j >= width*height)
                return NULL;
            if (pHold[0]== '\n'){
                fscanf(fMap, "%c", &pMap[i*height+j]); //The next value will be valid and can be taken
            }
            else if (pHold[0]==' '){
                fscanf(fMap, "%c", &pHold[0]); //Spaces will be in twos therefor second must be taken
                fscanf(fMap, "%c", &pMap[i*(height)+j]); //This will be valid
            }
            else{
                pMap[i*(height)+j] = pHold[0]; //If the hold passes the condition, pMap can be made that
            }

        } //Goes through 9 reps

    }
    *map_width = width;
    *map_height = height;
    return pMap;
}
char * load_dotMap(int *map_height, int *map_width){
    char * pMap = (char*) malloc((*map_width+2)*(*map_height+2)*sizeof(char*));
    if (pMap == NULL) { //If there is no memory to allocate them to
        //message to the user
        printf("Memory is not available");
        //Closing the file and free the space
        free(pMap);
        return NULL; //indicating error has occured
    }
    for (int i = 0; i < (height)*(width);i++){
        if (map[i] == 'P' || map[i] == 'G')
            pMap[i] = EMPTY;
        else
            pMap[i]=map[i];
    }
    return pMap;
}


void printMap(int *map_height, int *map_width){
    int level = -1;
    for (int i = 0; i < (*map_height+2)*(*map_width+2); i++){
        if (i < *map_width+1 || (*map_width+2)*(*map_height+1)< i){
            change_text_colour(BLUE);
            printf("W ");
        }
        else if ((i+1)%(width+2)==0){
            change_text_colour(BLUE);
            printf("W\n");
            level++;
        }
        else if (i % (*map_width+2)==0){
            change_text_colour(BLUE);
            printf("W ");
        }
        else{
            switch (map[i-(width+3)-2*level]) { //Changing the colour based on what needed to be printed
                case WALL:
                    change_text_colour(BLUE);
                    break;
                case PACMAN:
                    change_text_colour(YELLOW);
                    break;
                case GHOST:
                    change_text_colour(PINK);
                    break;
                case DOT:
                    change_text_colour(WHITE);
                    break;
            }
            printf("%c ", map[i-(width+3)-2*level]); //Printing the map value
        }
    }
    printf("\n");
}

int initalDotCount (int *map_height, int *map_width){
    int count = 0;

    for (int x = 0; x < *map_height**map_width; x++)

        if (dot_map[x] == '.'){
            count++;
        }
    //printf("COUINT %d", count);
    return  count;
}

int * getCoords (char type, int number){ //Number opperates from 0-n
    int unit_x = 0, unit_y =0, count = 0;
    int * cords = (int*) malloc(2*sizeof (int*)); //Array to store the coordinates of the object
    for (int i = 0; i < height*width; i++){
        if (map[unit_y*width+unit_x] == type){
            if (count == number){
                cords[0] = unit_x, cords[1] = unit_y;
                return cords;
            }

            count ++;
        }
        unit_x ++;
        if (unit_x == width){
            unit_x = 0;
            unit_y ++;
        }
    }

    if (unit_y > 8)
        return NULL;
}