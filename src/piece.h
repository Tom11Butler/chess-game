//
//  piece.h
//  Project
//
//  Created by Thomas Butler on 29/04/2019.
//
//  File Purpose: Class Declaration
//  This file contains the declaration of the abstract base class from which all named piece classes are derived.
//  Each member data and function is inherited for all derived classes
//  Pure virtual functions are prefixed with `virtual', suffixed with '=0'
//  --> having at least a single pure virtual function makes a class abstract
//  --> these functions are overidden in derived classes. If they are not, the derived classes are also abstract
//  Note: no objects of an abstract class may be created

//  Pure Virtual Member Functions:
//  1.  ideal_valid_moves returns the possible moves a piece could make if the board was empty
//  2.  path_to_square returns the path that a piece needs to take from its starting coordinates to its ending coordinates
//  3.  _type returns a string matching the name of the class type

//  Defined Member Functions:
//  1.  _colour returns the colour of the piece
//  2.  _symbol returns the symbol to represent the piece

//	Note:	All member functions end in const, as they do not change anything abot the object, only get information about it

//  Included Header Files:
//  string      --> to be able to have a variable that is a string
//  cwchar      --> so that a wide character variable to store Unicode characters may be used
//  vector      --> to use the standard library container vector
//  Definitions.h   --> so that the file knows what `coords' are (see file: uses a typedef for a specific 'pair' container)

#ifndef piece_h
#define piece_h

#include <string>

#include <cwchar>
#include <vector>
#include "Definitions.h"

using namespace std;

class piece {
protected:
    char colour;        //  The only variable that must be taken as argument in constructor
    string symbol;      //  Variable to be written out depending on colour
    piece();            //  Default constructor
    piece(char);        //  Parametrised constructor
    piece(const piece&);//  Copy constructor
    
public:
    virtual ~piece();
    //piece(const piece&);
    //  These are the moves that could be made if the board was empty
    virtual vector<coords> ideal_valid_moves(coords) const = 0;
    //  Will return the path the piece must take to get from one square to another
    virtual vector<coords> path_to_square(coords,coords) const = 0;
    //  Accessor functions, such as for the string that holds the unicode character
    char _colour() const;					//  returns the colour of the piece
    string _symbol() const ;				//  returns the symbol for the piece
    virtual string _type() const = 0;		//  so we know what type of piece it is
};

#endif /* piece_h */
