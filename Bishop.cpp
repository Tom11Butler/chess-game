//
//  Bishop.cpp
//  Project
//
//  Created by Thomas Butler on 29/04/2019.
//
//  File Purpose: Class Functionality
//  Overrides the pure virtual function to return the ideal valid moves the piece can make, i.e., if the board was empty
//  Overrides the pure virtual function to return the path that a piece would take to arrive at it's final position
//  Overrides the _type function to return "Bishop"

#include "Bishop.h"
#include <vector>

//=======================================================================================
//                          CONSTRUCTORS & DESTRUCTOR
//  Default
Bishop::Bishop() : piece() {}
//  Parametrised
Bishop::Bishop(char col) : piece(col) {
    if (colour=='w') {
        symbol="wbs";
    } else if (colour=='b') {
        symbol="bbs";
    }
}
//  Copy
Bishop::Bishop(const Bishop& to_deep_copy): piece(to_deep_copy) {}
Bishop::~Bishop() {/*cout<<"Destroy " << symbol" << endl;*/}
//=======================================================================================
//                              ACCESSOR FUNCTIONS
string Bishop::_type() const {return "Bishop";}
//=======================================================================================
//                              MEMBER FUNCTIONS
vector<coords> Bishop::ideal_valid_moves(coords current_location) const {
    vector<coords> potential_moves;
    //  Will need to make sure the difference in both coordinates is identical
    for (char c{'A'}; c<='H'; c++) {
        for (int i{1}; i<=8; i++) {
            if (abs(c-current_location.first)==abs(i-current_location.second))
                if ((c!=current_location.first)||(i!=current_location.second))
                    potential_moves.push_back(make_pair(c, i));
        }
    }
    return potential_moves;
}
vector<coords> Bishop::path_to_square(coords starting, coords ending) const {
    vector<coords> path;
    
    //  Both are increasing
    if ((int)ending.first-(int)starting.first > 1 && ending.second-starting.second > 1) {
        for (int step{1}; step<abs(ending.second-starting.second); step++)
            path.push_back(make_pair((char)starting.first+step,starting.second+step));
    }
    //  Letter increasing, number decreasing
    if ((int)ending.first-(int)starting.first > 1 && ending.second-starting.second < -1) {
        for (int step{1}; step<abs(ending.second-starting.second); step++)
            path.push_back(make_pair((char)starting.first+step,starting.second-step));
    }
    //  Both are decreasing
    if ((int)ending.first-(int)starting.first < -1  && ending.second-starting.second < -1) {
        for (int step{1}; step<abs(ending.second-starting.second); step++)
            path.push_back(make_pair((char)starting.first-step,starting.second-step));
    }
    //  Letter decreasing, number increasing
    if ((int)ending.first-(int)starting.first < -1 && ending.second-starting.second > 1) {
        for (int step{1}; step<abs(ending.second-starting.second); step++)
            path.push_back(make_pair((char)starting.first-step,starting.second+step));
    }
    return path;
}
