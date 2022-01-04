//
//  Pawn.h
//  Project
//
//  Created by Thomas Butler on 29/04/2019.
//
//  File Purpose: Class Declaration
//  Declares the class for Pawns with inheritance from the abstract base class `piece'
//  The overridden functions must be declared in this class also, such that they may be defined in the .cpp file
//  A copy constructor is defined for a deep copy of the Pawn. This is necessary when copying boards, etc, so that all of the information of all of the pieces are correctly copied. With a deep copy, editing the data of the copy should not affect the data of the original, and vise versa

//  Included Header Files:
//  piece.h --> so as to have the Pawn class be derived from the abstract base piece

#ifndef Pawn_h
#define Pawn_h

#include "piece.h"

class Pawn : public piece {
public:
    Pawn();                 // default constructor
    Pawn(char);             // parametrised constructor, only need colour
    Pawn(const Pawn&);      // copy constructor
    ~Pawn();                // destructor
    
    //  Returns the valid moves as if the piece is on an empty chess board
	vector<coords> ideal_valid_moves(coords)const;
	vector<coords> path_to_square(coords, coords) const;
    string _type() const;
};

#endif /* Pawn_h */
