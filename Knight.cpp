//
//  Knight.cpp
//  Project
//
//  Created by Thomas Butler on 29/04/2019.
//
//  File Purpose: Class Functionality
//  Overrides the pure virtual function to return the ideal valid moves the piece can make, i.e., if the board was empty
//  Overrides the pure virtual function to return the path that a piece would take to arrive at it's final position
//  --> This function is typically used in determining if a move is valid, yet is not needed for a Knight (nor a Pawn), as there is only ever a single occurance where the Pawn may be trying to jump another piece, when it can move two spaces for its first move.
//  --> It must still be defined, else this class would still be abstract as it would have an inherited pure virtual function
//  Overrides the _type function to return "Knight"

#include "Knight.h"
#include <vector>

//=======================================================================================
//                          CONSTRUCTORS & DESTRUCTOR
//  Default
Knight::Knight() : piece() {}
//  Parametrised
Knight::Knight(char col) : piece(col) {
    if (colour=='w') {
        symbol="wkt";
    } else if (colour=='b') {
        symbol="bkt";
    }
}
//  Copy
Knight::Knight(const Knight& to_deep_copy): piece(to_deep_copy) {}
Knight::~Knight() {/*cout<<"Destroy " << symbol" << endl;*/}
//=======================================================================================
//                              ACCESSOR FUNCTIONS
string Knight::_type() const {return "Knight";}
//=======================================================================================
//                              MEMBER FUNCTIONS
vector<coords> Knight::ideal_valid_moves(coords current_location) const {
    vector<coords> potential_moves;  // placeholder name for the variable
    //  Loop through all possible coordinates and determine if they satisfy the conditions
    for (char c{'A'}; c<='H'; c++) {
        for (int i{1}; i<=8; i++) {
            //  A Knight can move in an L-shape --> following condition satisfy that
            if ((abs(c-current_location.first)==1 && abs(i-current_location.second)==2) ||
                (abs(c-current_location.first)==2 && abs(i-current_location.second)==1)) {
                potential_moves.push_back(make_pair(c, i));
            }
        }
    }
    return potential_moves;
}
vector<coords> Knight::path_to_square(coords foo, coords bar) const {
    vector<coords> path;
    return path;
}
