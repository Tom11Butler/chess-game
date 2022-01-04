//
//  Game.h
//  Project
//
//  Created by Thomas Butler on 29/04/2019.
//
//  File Purpose: Class Declaration
//  Contains the declaration of the Game class
//  Instances of this class are used to play the game, as it is able to store what the current configuration of the board is, the total number of moves made so far (and so, whose turn it is due to the simple alternating scheme white-black-white...), and a vector of all the previous board configurations so that moves may be undone
//  All the data is left public, as the data ...

//  Member Data:
//  1.  A board object that stores what the current board is for the point in the game.
//  2.  An integer tally of the number of moves made in the game.
//  3.  A character indicating the colour of the player whose turn it is. This is directly calculated from the number of moves made in the game. If it is even, then it is the white player's turn, and if it is odd, then is it is the black player's turn
//  3.  A vector of boards that contain the previous moves of the game. This is used to undo a move during the game.
//	5.	An integer to record the number of moves that have been made in the game.

//  Member Functions:
//  1.  undo_move to undo the last move made on the board
//  2.  

#ifndef Game_h
#define Game_h
#include "board.h"
class Game {
public:
    board current_board;
    int number_of_moves;
    vector<board> previous_moves_boards;
    vector<pair<coords,coords>> past_moves_text;
    char whose_turn;
    
    Game();
    Game(board);
    ~Game();
    Game& undo_move();
    void write_past_moves_text() const;
};

#endif /* Game_h */
