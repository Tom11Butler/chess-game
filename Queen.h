//
//  Queen.h
//  Project
//
//  Created by Thomas Butler on 29/04/2019.
//
//  File Purpose: Class Declaration
//  Declares the class for Queens with inheritance from the abstract base class `piece'
//  The overridden functions must be declared in this class also, such that they may be defined in the .cpp file

//  Included Header Files:
//  piece.h --> so as to have the Queen class be derived from the abstract base piece

#ifndef Queen_h
#define Queen_h

#include "piece.h"
class Queen : public piece {
public:
    Queen();                // default constructor
    Queen(char);            // parametrised constructor, only need colour
    Queen(const Queen&);    //  Copy constructor
    ~Queen();               // destructor
    
    //  Returns the valid moves as if the piece is on an empty chess board
	vector<coords> ideal_valid_moves(coords)const;
	vector<coords> path_to_square(coords, coords) const;
    string _type() const;
};


#endif /* Queen_h */
