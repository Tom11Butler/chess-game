//
//  Pawn.cpp
//  Project
//
//  Created by Thomas Butler on 29/04/2019.
//
//  File Purpose: Class Functionality
//  Overrides the pure virtual function to return the ideal valid moves the piece can make, i.e., if the board was empty
//  Overrides the pure virtual function to return the path that a piece would take to arrive at it's final position
//  --> This function is typically used in determining if a move is valid, yet is not needed for a Pawn (nor a Knight), as there is only ever a single occurance where the Pawn may be trying to jump another piece, when it can move two spaces for its first move.
//  --> It must still be defined, else this class would still be abstract as it would have an inherited pure virtual function
//  Overrides the _type function to return "Pawn"

#include "Pawn.h"
#include <vector>

//=======================================================================================
//                          CONSTRUCTORS & DESTRUCTOR
//  Default
Pawn::Pawn() : piece() {}
//  Parametrised
Pawn::Pawn(char col) : piece(col) {
    colour=col;
    if (colour=='w'){
        symbol="wpn";
    } else if (colour=='b') {
        symbol="bpn";
    }
}
//  Copy constructor, calls the base class copy constructor
Pawn::Pawn(const Pawn& to_deep_copy) : piece(to_deep_copy) {}
Pawn::~Pawn() {/*cout<<"Destroy " << symbol" << endl;*/}

//=======================================================================================
//                              ACCESSOR FUNCTIONS
string Pawn::_type() const {return "Pawn";}
//=====================================================================================
//                              MEMBER FUNCTIONS
//  Returns the ideal (as for an empty board) moves the piece can make
vector<coords> Pawn::ideal_valid_moves(coords current_location) const {
    vector<coords> potential_moves;  // placeholder name for the variable
    int sign{0};
    //  white (black) pawns can only move up (down) the board
    //  in this board geometry, this is in the direction of decreasing (increasing) integer
    if (colour=='w') sign=-1;
    if (colour=='b') sign=1;
    
    //  Can only move a pawn 2 spaces forward if it is in its starting position
    if (colour=='w') {
        if (current_location.second==7) potential_moves.push_back(make_pair(current_location.first, current_location.second+2*sign));
    }
    if (colour=='b') {
        if (current_location.second==2) potential_moves.push_back(make_pair(current_location.first, current_location.second+2*sign));
    }
    
    if (current_location.first>'A' && current_location.first<'H') {   //  Could move left or right if there is a piece to take
        for (int i{-1}; i<2; i++) {
            potential_moves.push_back(make_pair(current_location.first+i, current_location.second+sign));
        }
    } else if (current_location.first=='A') {
        for (int i{0}; i<2; i++) {
            potential_moves.push_back(make_pair(current_location.first+i, current_location.second+sign));
        }
    } else if (current_location.first=='H') {
        for (int i{-1}; i<1; i++) {
            potential_moves.push_back(make_pair(current_location.first+i, current_location.second+sign));
        }
    }
    return potential_moves;
}

//  This is, in a sense, a null function.
//  In validating if a move is valid
vector<coords> Pawn::path_to_square(coords foo, coords bar) const {
    vector<coords> path;
    return path;
}
