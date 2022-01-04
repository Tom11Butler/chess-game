//
//  piece.cpp
//  Project
//
//  Created by Thomas Butler on 29/04/2019.
//
//  File Purpose: Class Functionality
//  Defines the functions for the abstract base class `piece', so must include piece.h
//  Functions defined here are inherited in each derived class, and ALWAYS will have the same functionality
//  The overidden functions may change in each derived class --> derived classes are a type of piece, and so will behave differently in these aspects

#include "piece.h"

//=======================================================================================
//                          CONSTRUCTORS & DESTRUCTOR
//  Default: chosen to intialise the data with invalid information that could be changed
piece::piece() {colour='e';symbol="dead";}
//  Parametrised
piece::piece(char col) {colour=col;}
//  Copy
piece::piece(const piece& copying_piece) {
    colour=copying_piece.colour;
    symbol=copying_piece.symbol;
}
//  Destructor for the abstract base piece class
piece::~piece() {}

//=======================================================================================
//                              ACCESSOR FUNCTIONS
//  Use of an underscore to differentiate the function from the member data
//  Returns the colour of the piece
char piece::_colour() const {return colour;}
//  Returns the symbol that is displayed on the chess board for this piece
string piece::_symbol() const {return symbol;}

