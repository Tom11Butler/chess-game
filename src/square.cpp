//
//  square.cpp
//  Project
//
//  Created by Thomas Butler on 29/04/2019.
//
//  File Purpose: Class Functionality
//  Defines the functionality of the square class.
//  Each function is quite self-explanatory

#include "square.h"
#include "piece.h"
#include "Pawn.h"
#include <iostream>
#include <utility>
#include <memory>
#include <vector>

//=======================================================================================
//                          CONSTRUCTORS & DESTRUCTOR
//  Default constructor: set to invalid coordinates 
square::square() {contents=nullptr;location=make_pair('z',-1);colour=' ';}
//  Parametrised constructor
square::square(shared_ptr<piece> _contents, coords _location, char _colour) {
    contents=_contents;
    location=_location;
    colour=_colour;
}
//  Parametrised constructor: takes an int rather than a pair
square::square(shared_ptr<piece> _contents, int loc, char _colour) {
    contents=_contents;
    colour=_colour;
    location=make_pair((char)(loc%8+65),loc/8+1);
}
square::~square() {}
//=======================================================================================
//                              ACCESSOR FUNCTIONS
shared_ptr<piece> square::_contents() const {return contents;}
coords square::_location() const {return location;}

//=======================================================================================
//                              MEMBER FUNCTIONS
square& square::change_contents(shared_ptr<piece> shared_pointer_to_piece) {
    contents.reset();
    contents=shared_pointer_to_piece;
    return *this;
}
square& square::clear_contents() {contents.reset(); return *this;}
square& square::swap_contents(square& square_to_swap_with) {
    contents.swap(square_to_swap_with.contents);
    return *this;
}
ostream& operator<<(ostream& os, const square& square_to_draw) {
    if (square_to_draw.contents!=nullptr) os << square_to_draw.contents->_symbol();
    return os;
}
