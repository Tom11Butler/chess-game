//
//  board.h
//  Project
//
//  Created by Thomas Butler on 29/04/2019.
//
//  File Purpose: Class Declaration
//  This file contains the declaration of the board class. The entire board is what is outputted to the user
//
//  Member Data:
//  1.  A vector of vector of squares. Essentially a matrix of squares, and always shall be 8x8, as is a chess board
//
//  Member Functions:
//  1.  draw
//      Draws out the board to the user. Very important to the interactivity of the game.
//  2.  _elements_contents()
//      Takes coordinates (see Definitions.h), and returns whatever the contents of that square is. This was useful as it saved from converting the pair back into integers that could then be used in the standard vector accessors []
//  3.  move_piece()
//      Moves a piece on the board from one square to another. Coorindates for the squares are sent down as arguments of the function
//  4.  pawn_promotion()
//      Will only ever be called if the conditions for when a pawn promotion can occur are filled. This asks the user for what piece they want to change their pawn to, then fulfills that.
//  5.  valid_move()
//      This determines if a move is valid. Takes the same arguments as the move_piece function
//  6.  leaves_king_vulnerable
//      Determines if carrying out the suggested move will leave the King vulnerable to an attack from an enemy piece
//  7.  all_possible_valid_moves
//      Determines all the possible moves for a given player. Takes the colour of the player whose turn it as an argument
//  8.  write_all_possible_valid_moves
//      Writes out all the possible valid moves for a given player. Takes the same argument as above. If the size of this is zero for a given player, then that player is either in stalemate or checkmate. That is, the game is over.
//  9.  check
//      Determines if a given player's King is vulnerable to attack

//  Included Header Files:
//  vector      --> so can use the standard library container
//  square.h    --> so can have a pointer to a square object as a member data.

#ifndef board_h
#define board_h

#include <vector>
#include "square.h"

class board {
private:
    vector<vector<square>> elements;    //  need `matrix' of board squares
public:
    board();                            //  default constructor
    board(vector<vector<square>>);      //  parametrised constructor
    board(const board&);                //  copy constructor
    ~board();
    
    void draw();
    shared_ptr<piece> _elements_contents(coords);
    board& move_piece(coords, coords);
    board& pawn_promotion(coords,coords);
    bool valid_move(coords, coords);
    bool leaves_king_vulnerable(coords, coords);
    vector<vector<coords>> all_possible_valid_moves(char);
    void write_all_possible_valid_moves(char);
    bool check(char);
};

#endif /* board_h */

/*
 +---------+------------+------------+
 |  color  | foreground | background |
 |         |    code    |    code    |
 +---------+------------+------------+
 | black   |     30     |     40     |
 | red     |     31     |     41     |
 | green   |     32     |     42     |
 | yellow  |     33     |     43     |
 | blue    |     34     |     44     |
 | magenta |     35     |     45     |
 | cyan    |     36     |     46     |
 | white   |     37     |     47     |
 +---------+------------+------------+
 */
