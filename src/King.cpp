//
//  King.cpp
//  Project
//
//  Created by Thomas Butler on 29/04/2019.
//
//  File Purpose: Class Functionality
//  Overrides the pure virtual function to return the ideal valid moves the piece can make, i.e., if the board was empty
//  Overrides the pure virtual function to return the path that a piece would take to arrive at it's final position
//  Overrides the _type function to return "King"

#include "King.h"
#include <vector>

//=======================================================================================
//                          CONSTRUCTORS & DESTRUCTOR
//  Default
King::King() : piece() {}
//  Parametrised
King::King(char col) : piece(col) {
    if (colour=='w') {
        symbol="wkg";
    } else if (colour=='b') {
        symbol="bkg";
    }
}
//  Copy
King::King(const King& to_deep_copy) : piece(to_deep_copy) {}
King::~King() {/*cout<<"Destroy " << symbol" << endl;*/}
//=======================================================================================
//                              ACCESSOR FUNCTIONS
string King::_type() const {return "King";}
//=======================================================================================
//                              MEMBER FUNCTIONS
vector<coords> King::ideal_valid_moves(coords current_location) const {
    vector<coords> foobar;
    for (char c{'A'}; c<='H'; c++) {
        for (int i{1}; i<=8; i++) {
            if (abs(c-current_location.first)<=1 && abs(i-current_location.second)<=1)
                if ((c!=current_location.first)||(i!=current_location.second))
                    foobar.push_back(make_pair(c, i));
        }
    }
    return foobar;
}

//  A King can only ever move one space at a time, so the path is empty
vector<coords> King::path_to_square(coords foo, coords bar) const {
    vector<coords> path;
    return path;
}
