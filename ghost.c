// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#include "defines.h"
#include <stdlib.h>
#include "ghost.h"
#include "map.h"
#include <stdio.h>


char sees_pacman(int pacman_y, int pacman_x, int ghost_y, int ghost_x) {
    if (pacman_x == ghost_x && pacman_y == ghost_y) {
        return EATING_PACMAN;
    }

    int step;
    // Check for vertical alignment (same column)
    if (pacman_x == ghost_x) {
        if (pacman_y > ghost_y) {
            step = 1; // Pacman is below the ghost
        } else {
            step = -1; // Pacman is above the ghost
        }

        int y = ghost_y + step;
        while (y != pacman_y) {

            if (is_wall(ghost_x, y)==1) {
                return SEES_NOTHING;

            }

            y += step;

        }

        if (step == 1) {
            return DOWN;
        } else {
            return UP;
        }
    }

    // Check for horizontal alignment (same row)
    if (pacman_y == ghost_y) {
        if (pacman_x > ghost_x) {
            step = 1; // Pacman is to the right of the ghost
        } else {
            step = -1; // Pacman is to the left of the ghost
        }
        int x = ghost_x + step;
        while (x != pacman_x) {
            if (is_wall(x, ghost_x)) {
                return SEES_NOTHING;
            }
            x += step;
        }
        if (step == 1) {
            return RIGHT;
        } else {
            return LEFT;
        }
    }

    return SEES_NOTHING;
}

char moveGhost(int pacmanY, int pacmanX, int ghost_y, int ghost_x) {
    char direction = sees_pacman(pacmanY, pacmanX, ghost_y, ghost_x); //Seeing if it sees pacman

    if (direction == SEES_NOTHING){
        int randDirn;
        int drnCount = 0; //Possible directions
        char allDirns [] = {UP, DOWN, LEFT, RIGHT};
        char* possibleDirns = malloc(sizeof (char*));;
        if (possibleDirns == NULL){
            printf("Memory is not available");
            free(possibleDirns);
            return 'z'; //Error has occured
        }
        for (int i = 0; i < 4; i++){
            if (validMovement(ghost_x, ghost_y, allDirns[i])==0){
                drnCount++;
                //printf("Valid direction is: %c", allDirns[i]);
                possibleDirns = realloc(possibleDirns, drnCount* sizeof(char)); //Adding
                possibleDirns[drnCount-1] = allDirns[i];

            }
        }
        if (drnCount == 0)
            return 'z';
        randDirn = rand() % drnCount; //Creating the random direction
        direction = possibleDirns[randDirn]; //setting the direction

    }
    // Based on the direction, the ghost will make a decision
    // For the sake of this example, we just return the direction seen
    // In a real game, additional logic would be used to handle movement and strategy
    //printf("for ghost x: %d, y: %d\nDirection: %c\n", ghost_x, ghost_y,direction);
    return direction;
}