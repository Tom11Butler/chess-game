//
//  King.h
//  Project
//
//  Created by Thomas Butler on 29/04/2019.
//
//  File Purpose: Class Declaration
//  Declares the class for Kings with inheritance from the abstract base class `piece'
//  The overridden functions must be declared in this class also, such that they may be defined in the .cpp file

//  Included Header Files:
//  piece.h --> so as to have the King class be derived from the abstract base piece

#ifndef King_h
#define King_h

#include "piece.h"
class King : public piece {
public:
    King();                 // default constructor
    King(char);             // parametrised constructor, only need colour
    King(const King&);      // copy constructor
    ~King();                // destructor
    
    //  Returns the valid moves as if the piece is on an empty chess board
	vector<coords> ideal_valid_moves(coords)const;
	vector<coords> path_to_square(coords, coords) const;
    string _type() const;
};

#endif /* King_h */
