// APSC 142 Pacman code
// Created by John Calder 20392298 and Aslan Lauzon ####

// don't forget to update your project configuration to select "Emulate terminal in the output console"

// Make sure to include all relevant libraries
#include <stdio.h>
#include <stdlib.h>

// colours.h contains functions to change text colour and read single characters without requiring an enter
#include "colours.h"
// defines.h contains useful definitions to keep your code readable
#include "defines.h"
// map.h, game.h, and ghost.h contain prototypes of functions you must implement
#include "map.h"
#include "game.h"
#include "ghost.h"



// These global variables must be used to store map information.
// Almost every function needs these variables, so keeping them as globals helps keep things organized.
// map is a pointer to a dynamically allocated map for displaying to the user
// dot_map is a pointer to a dynamically allocated map for keeping track of what dots are left
char *map = NULL, *dot_map = NULL;
// width and height store the width and height of map, NOT counting outer walls
int width = 9, height = 9;
extern int dotCount;




/**
 * Main entry point into your program.
 * Make sure that main returns appropriate status codes depending on what
 * happens.  The codes you must use are:
 *   NO_ERROR when no error occurs
 *   ERR_NO_MAP when no map file is found
 *   ERR_NO_PACMAN when no pacman is found on the map
 *   ERR_NO_GHOSTS when fewer than 2 ghosts are found on the map
 *
 * Make sure that any allocated memory is freed before returning.
 * @return a status code
 */
int main(void) {
    int *pHeight =  &width;
    int *pWidth = &height;
    char input, direction;
    int mveactrresult;
    int  result [2];

    //tracking variables
    int  pacman_x = 0, pacman_y = 0;
    int ghosts_y[NUM_GHOSTS], ghosts_x[NUM_GHOSTS];


    map = load_map("map.txt", pHeight, pWidth);
    if (map == NULL) //If the map is not findable
        return ERR_NO_MAP;
    dot_map = load_dotMap(pHeight, pWidth);
    dotCount = initalDotCount(pHeight, pWidth);

    setbuf(stdout, NULL);
    //Creating the dot map

    //Getting
    int* cords = getCoords (PACMAN, 0); //Getting pacman coordinates
    if (cords == NULL) //If pacman can't be found
        return ERR_NO_PACMAN;
    pacman_x = cords[0],pacman_y = cords[1]; //getting pacman
    for (int i = 0; i < 2; i++){
        cords = getCoords (GHOST, i); //Getting the ghost's coords
        if (cords == NULL) //If no ghosts can be found
            return ERR_NO_GHOSTS;
        ghosts_x[i] = cords[0], ghosts_y[i] = cords[1]; //Inputing them

    }
    free(cords);
    //change to loss condition

    //Initial map print
    printMap(pHeight, pWidth);

    do{

        input = getch();
        //int tempPacCord[] = {pacman_x, pacman_y};
        mveactrresult = move_actor(&pacman_y,&pacman_x,input,1);
        if (mveactrresult ==2)
            continue;

        //check win condition
        if (check_win(pacman_y,pacman_x,ghosts_y,ghosts_x)){
            break;
        }

        for (int i = 0; i < NUM_GHOSTS; i++){
            direction = moveGhost(pacman_y, pacman_x,ghosts_y[i], ghosts_x[i]);
            result[i] = move_actor(&ghosts_y[i], &ghosts_x[i], direction, 0);
        }

        //check win condition
        if (check_win(pacman_y,pacman_x,ghosts_y,ghosts_x)){
            break;
        }

        //Printing the resulting map
        printMap(pHeight, pWidth);



    }while (!check_loss(pacman_y,pacman_x,ghosts_y,ghosts_x));

    free(map);
    free(dot_map);

    return NO_ERROR;
}
