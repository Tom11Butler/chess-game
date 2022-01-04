//
//  main.cpp
//  Project
//
//  Created by Thomas Butler on 29/04/2019.
//
//  File Purpose:
//  This file brings all of the code together to present a playable game of chess, with menus, to the user.
//  --> also see Useful_Function.h and .cpp to see where the playable game part is implemented and brought together
//  The bulk of the logical aspects of the game are included in the board.cpp file. Its associated header file contains the class declaration of the board, which has member functions such as check(), checkmate(), that determine if the board is in a configuration such that a King is in check and if the King is able to move anywhere respectively.
//  --> go to board.h and board.cpp to see the bulk of the implementation

//  Included Header Files: Standard Library
//  iostream    --> to write out to the console, input/output streams
//  string      --> to use string variables, such as analysing input from the user

//  Included Header Files: Author Written
//  Definitions.h   --> defines the pair<char,int> type as `coords', and the WHITE_SQUARE and BLACK_SQUARE used in drawing the board
//  Game.h          --> declaration of the Game class, which stores information about the game, such as the board and the number of moves made in the game
//  Menu.h          --> declaration of the Menu class. This class is used when the user must input one of a, usually small, set of predetermined options. The first instantiation below is for the main menu, with options such as [start], [help], etc. The other two uses in the program are for the pause menu, and for the pawn promotion selection
//  Useful_Functions.h --> declares functions, written in Useful_Functions.cpp, that are needed to bring the program together. This files requires the start_board() function, which sets up the board configuration as would be at the start of a game of chess

//  Functionality of this file:
//  The main function initialises a Game object named chess with the starting game board
//  The main menu -- an object of the Menu class -- is constructed and called to introduce the player to the game
//  The pause menu is also constructed, and only called if the user pauses their game

#include <iostream>
#include <string>
#include "Definitions.h"
#include "Game.h"
#include "Menu.h"
#include "Useful_Functions.h"

//  Using this namespace as only used standard library functions
using namespace std;

int main(int argc, const char * argv[]) {
    //  Use a parametrised constructor to instantiate an object of the Game class with the starting board
    //  Boolean variable to state whether the game has began
    Game chess(start_board());
    bool began_game{false};

    //  The main menu is only used once, at the beginning of each game
    menu main_menu("Welcome to the game of chess!\n",
                   "Invalid input.",
                   "-> ",
                   //    Now include all of the inputs, and the functions that they call
                   {
                       //   First option: start the game
                       {"start", [&chess, &began_game] {
                           chess = play_game(chess);
                           began_game=true;
                       }},
                       //   Second option: get rules
                       {"help", [/*no need to capture anything*/] {chess_rules();}},
                       //   Third option: print out the key for the pieces
                       {"key", [/*no need to capture anything*/] {pieces_key();}},
                       //   Fourth option: quitting the game
                       {"quit", [/*no need to capture anything*/] {cout << "Quitting game.\n"; exit(1);}},
                   });
    //  The menu that is called when the user chooses to pause the game
    menu pause_menu("Paused Game\n",
                    "Invalid input.",
                    "->",
                    {
                        //  First option: resume the game
                        {"resume", [&chess] {chess=play_game(chess);}},
                        //  Second option: undo the last move made
                        {"undo", [&chess] {
                            cout << "Undoing the move." << endl;
                            chess.undo_move();
                            chess=play_game(chess);
                        }},
                        //  Third option: restart the game
                        {"restart", [&chess] {
                            //  Restarting the game
                            //  This necessitates:
                            //  --> resetting the board to the starting configuration,
                            //  --> clearing all the previous moves,
                            //  --> setting the total number of moves to zero
                            chess.current_board = start_board();
                            chess.previous_moves_boards.clear();
                            chess.number_of_moves=0;
                            chess = play_game(chess);
                        }},
                        //  Fourth option: print out the help text
                        {"help", [/*no need to capture anything*/] {chess_rules();}},
                        //  Fifth option: print out all the possible moves
                        {"key", [/*no need to capture anything*/] {pieces_key();}},
                        //  Sixth option: print out all the possible moves
                        {"possible moves", [&chess] {chess.current_board.write_all_possible_valid_moves(chess.whose_turn);}},
                        //  Seventh option: print out all the past moves
                        {"past moves", [&chess] {chess.write_past_moves_text();}},
                        //  Eigth option: quit the game and end the program
                        {"quit", [/*no need to capture anything*/] {cout << "Quitting game.\n"; exit(1);}}
                    });
    //  `Runs' the menus with the operator ()
    
    while (!began_game) main_menu();
    while (chess.current_board.all_possible_valid_moves('w').size()!=0 &&
            chess.current_board.all_possible_valid_moves('b').size()!=0) {
        pause_menu();
    }
    
    if (chess.whose_turn=='b') cout << "Black player wins!" << endl;
    if (chess.whose_turn=='w') cout << "White player wins!" << endl;
    
    return 0;
}
