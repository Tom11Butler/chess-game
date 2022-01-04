//
//  Useful_Functions.h
//  Project
//
//  Created by Thomas Butler on 01/05/2019.
//
//  File Purpose: Function Declarations
//  Declares some useful functions to be used in the main program.
//  1.  chess_rules()
//      Writes out the rules of how to play the game to the user. This function is called from the main menu, or the pause menu
//  2.  pieces_key
//      Writes out the key for the piees, so the user knows what each 3-character string stands for
//  3.  play_game()
//      Takes a Game object as an argument. Doing this means that the game may be resumed with a Game that has already had several moves made, and not just starting from the beginning.
//  4.  start_board returns the board as it would be at the start of a chess game. That is, all the pieces are on the two boundary rows

#ifndef Useful_Functions_h
#define Useful_Functions_h

#include "board.h"
#include "Game.h"
#include "Menu.h"
#include "Definitions.h"

//  Using this namespace as only used standard library functions
using namespace std;

void chess_rules();
void pieces_key();
Game play_game(Game chess);
board start_board();

#endif /* Useful_Functions_h */
