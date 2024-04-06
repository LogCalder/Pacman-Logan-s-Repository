// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#include "defines.h"
#include "game.h"
#include <stdio.h>

extern char * map, * dot_map;
extern int height;
extern int width;
int dotCount;

//Checking if pacman has won
int check_win(int pacman_y, int pacman_x, int ghosts_y[NUM_GHOSTS], int ghosts_x[NUM_GHOSTS]) {
    if (dotCount == 0){ //If there are not dots left pacman has won
        printf("Congratulations! You win!");
        return YOU_WIN;
    }
    return KEEP_GOING;
}

//Determining if pacman has lost
int check_loss(int pacman_y, int pacman_x, int ghosts_y[NUM_GHOSTS], int ghosts_x[NUM_GHOSTS]) {
    for (int i = 0; i < NUM_GHOSTS; i++){ //Running for all ghosts
        if (pacman_x == ghosts_x[i] && pacman_y == ghosts_y[i]){ //Checking if pacman is at the same spot
            printf("Sorry, you lose.");
            return YOU_LOSE;
        }
    }
    return KEEP_GOING; //They are not therefor return keep going
}

