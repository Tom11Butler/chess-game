//
//  square.h
//  Project
//
//  Created by Thomas Butler on 29/04/2019.
//
//  File Purpose: Class Declaration
//  This file contains the declaration of the square class. The constructors for a square contain several variations. The parametrised ones take only the contents, location, and colour of the square as their arguments. However, they differ in the form of the coordinates they take. One has an integer form, and the other the defined type `coords' (see Definitions.h). Both were found to be useful. Taking an int allowed for a simple for loop 1->64 when constructing an empty board.
//
//  Member data:
//  1.  A shared pointer to a piece. By pointing to the abstract base class, run-time polymorphism is used to determine what derived classes' functions to utilise. If the square is meant to be empty, this shall be a null pointer.
//  2.  A `coords' (see Definitions.h --> it is a named pair<char,int>). This specifies the location of the square on the board. May take the form D3, for example.

//	Member Functions:
//	1.	Return the contents of the square (access function)
//	2.	Return the coordinates of the square (access functions)
//	3.	Clear the contents of the square
//	4.	Change the contents of the square from one piece to another
//	5.	Swap the contents of two squares

//	Friend Function
//	Overloading cout for the square

//	Note:	Access functions will always end in a const, as we do not want to alter any information of the object, only retrieve it
//
//  Included Header Files:
//  memory  --> to be able to use smart pointers: this could allow for unique, shared, and weak pointers. Only shared pointers are needed for this file
//  piece.h --> so the square can contain the pointer to the piece


#ifndef square_h
#define square_h

#include <memory>
#include <string>

#include "piece.h"
using namespace std;


class square {
private:
    shared_ptr<piece> contents; //  the contents of the square (may be null pointer for empty)
    coords location;            //  the coordinates of where the square is
public:
    char colour;                //  colour of the square, for aesthetic output, else not important
    square();
    //  Parametrised constructor: needs to know contents, location, and colour of square
    square(shared_ptr<piece>, coords, char);
    //  Can use this constructor when creating the board, a loop from 0->63 through all squares
    square(shared_ptr<piece>, int, char);
    //  Arbitrary destructor for the square
    ~square();
    
    shared_ptr<piece> _contents() const;					//  returns the shared pointer of the square
    coords _location() const;
    square& clear_contents();                               //  sets contents to null pointer
    square& change_contents(shared_ptr<piece>);             //  changes contents to something else
    square& swap_contents(square&);
    friend ostream& operator<<(ostream&, const square&);    //  writing out a square
};


#endif /* square_h */
