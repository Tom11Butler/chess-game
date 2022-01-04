//
//  Game.cpp
//  Project
//
//  Created by Thomas Butler on 29/04/2019.
//
//  File Purpose: Class Functionality
//  Provides functionality to the Game class. There are only two member functions.
//  1.  Undo the last move that was made in the game
//  2.  Print out the list of all the previous moves made in the game

#include <iostream>
#include "Game.h"

//=======================================================================================
//                          CONSTRUCTORS & DESTRUCTOR
Game::Game() {}
Game::Game(board _board) { current_board = _board; number_of_moves = 0; }
Game::~Game() {}
//=======================================================================================
//                              MEMBER FUNCTIONS
Game& Game::undo_move() {
    int n=(int)previous_moves_boards.size();
    if (n!=0) {
        //  copy the last move into the current board
        board undone(previous_moves_boards[n-1]);
        current_board=undone;
        //  delete that move from the vector containing the previous moves
        previous_moves_boards.pop_back();
        //  delete the last move's text form
        past_moves_text.pop_back();
        //  decrease move number total
        number_of_moves--;
    } else {
        std::cout << "There is no move to undo." << std::endl;
    }
    return *this;
}

//  Write out
void Game::write_past_moves_text() const {
    //  Use an integer count variable to output the number of the move that was made
    int count{0};
    for (auto _move=past_moves_text.begin(); _move!=past_moves_text.end(); _move++) {
        count++;
        //  Choice to format the output so that arrows appear at the same point on the line
        cout << "Move " << count << "\t-> ";
        cout << _move->first.first << _move->first.second << " " << _move->second.first << _move->second.second << endl;
    }
}
