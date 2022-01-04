//
//  Queen.cpp
//  Project
//
//  Created by Thomas Butler on 29/04/2019.
//
//  File Purpose: Class Functionality

//  Overrides the pure virtual function to return the ideal valid moves the piece can make, i.e., if the board was empty
//  Overrides the pure virtual function to return the path that a piece would take to arrive at it's final position
//  Overrides the _type function to return "Queen"

#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include <vector>
#include <memory>

//=======================================================================================
//                          CONSTRUCTORS & DESTRUCTOR
//  Default
Queen::Queen() : piece() {}
//  Parametrised
Queen::Queen(char col) : piece(col) {
    if (colour=='w') {
        symbol="wqn";
    } else if (colour=='b') {
        symbol="bqn";
    }
}
Queen::Queen(const Queen& to_deep_copy) : piece(to_deep_copy) {}
Queen::~Queen() {/*cout<<"Destroy " << symbol" << endl;*/}
//=======================================================================================
//                              ACCESSOR FUNCTIONS
string Queen::_type() const {return "Queen";}
//=======================================================================================
//                              MEMBER FUNCTIONS

vector<coords> Queen::ideal_valid_moves(coords current_location) const {
    vector<coords> potential_moves;
    //  Combination of the Rook and Bishop moves
    for (char c{'A'}; c<='H'; c++) {
        for (int i{1}; i<=8; i++) {
            if ((c!=current_location.first)||(i!=current_location.second)) {
                if (c==current_location.first || i==current_location.second) potential_moves.push_back(make_pair(c, i));
                if (abs(c-current_location.first)==abs(i-current_location.second)) potential_moves.push_back(make_pair(c, i));
            }
        }
    }
    return potential_moves;
}
vector<coords> Queen::path_to_square(coords starting, coords ending) const {
    vector<coords> path;
    //  A Queen can make the same moves as a rook
    //  Get the horizontal or vertical path from the function for a Rook
    shared_ptr<piece> rook (new Rook(colour));
    vector<coords> rook_path = rook->path_to_square(starting, ending);
    if (!rook_path.empty()) return rook_path;
    
    //  A Queen can make the same moves as a bishop
    //  Get the diagonal path from the function for a Bishop
    shared_ptr<piece> bishop (new Bishop(colour));
    vector<coords> bishop_path = bishop->path_to_square(starting, ending);
    if (!bishop_path.empty()) return bishop_path;
    
    //  Should only be called if the move has been checked against the possibilities
    //  Should never have to return finish
    return path;
}
