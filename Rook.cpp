//
//  Rook.cpp
//  Project
//
//  Created by Thomas Butler on 29/04/2019.
//
//  File Purpose: Class Functionality

//  Overrides the pure virtual function to return the ideal valid moves the piece can make, i.e., if the board was empty
//  Overrides the pure virtual function to return the path that a piece would take to arrive at it's final position
//  Overrides the _type function to return "Rook"

#include "Rook.h"
#include <vector>
#include <utility>
#include <iostream>
using namespace std;

//=======================================================================================
//                          CONSTRUCTORS & DESTRUCTOR
//Default
Rook::Rook() : piece() {}
//  Parametrised
Rook::Rook(char col) : piece(col) {
    if (colour=='w') {
        symbol="wrk";
    } else if (colour=='b') {
        symbol="brk";
    }
}
Rook::Rook(const Rook& to_deep_copy): piece(to_deep_copy) {}
Rook::~Rook() {/*cout<<"Destroy " << symbol" << endl;*/}
//=======================================================================================
//                              ACCESSOR FUNCTIONS
string Rook::_type() const {return "Rook";}
//=======================================================================================
//                              MEMBER FUNCTIONS

vector<coords> Rook::ideal_valid_moves(coords current_location) const {
    vector<coords> foobar;
    for (char c{'A'}; c<='H'; c++) {
        for (int i{1}; i<=8; i++) {
            if (c==current_location.first || i==current_location.second)
                if ((c!=current_location.first)||(i!=current_location.second))
                    foobar.push_back(make_pair(c, i));
        }
    }
    return foobar;
}
vector<coords> Rook::path_to_square(coords start_point, coords end_point) const {
    vector<coords> path;
    //  The rook may only travel vertically or horizontally
    //  Check which of the chess coordinates remains constant
    if (start_point.first==end_point.first) {
        //  The rook is trying to stay in the same column
        //  Is it trying to move up the board, or down the board?
        if (end_point.second-start_point.second>1) {    //  Down the board
            for (int i{1}; i<abs(end_point.second-start_point.second); i++) {
                path.push_back(make_pair(start_point.first,start_point.second+i));
            }
        } else if (end_point.second-start_point.second<-1) {    //  Up the board
            for (int i{1}; i<abs(end_point.second-start_point.second); i++) {
                path.push_back(make_pair(start_point.first,end_point.second+i));
            }
        }
    } else if (start_point.second==end_point.second) {
        //  The rook is trying to stay in the same row
        //  Is it trying to move to the left or right in the row?
        if (end_point.first-start_point.first>1) {  //  Moving to the left
            for (int i{1}; i<abs((int)(end_point.first-start_point.first)); i++) {
                path.push_back(make_pair((char)(start_point.first+i),end_point.second));
            }
        } else if (start_point.first-end_point.first>1) {  //  Moving to the right
            for (int i{1}; i<abs((int)(end_point.first-start_point.first)); i++) {
                path.push_back(make_pair((char)(start_point.first-i),end_point.second));
            }
        }
    }
    return path;
}
