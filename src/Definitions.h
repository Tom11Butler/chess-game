//
//  Definitions.h
//  Project
//
//  Created by Thomas Butler on 29/04/2019.
//
//  File Purpose:
//  Contains useful definitions that are used throughout the program
//  1.  typedef renames something that is already in the C++ program. Wanted to rename a pair of a character and an integer as a coordinate that can be used on a chess board, e.g., A4.

#ifndef Definitions_h
#define Definitions_h

typedef std::pair<char,int> coords;  //  Character with an integer defines a coordinate on a chess board
//  Member function first() returns the char in the pair
//  Member function second() returns the int in the pair

//	The following will define the characters that print out a white and black cell to the screen
#define WHITE_SQUARE 0xDB
#define BLACK_SQUARE 0xFF

#endif /* Definitions_h */
