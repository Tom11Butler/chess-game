//
//  board.cpp
//  Project
//
//  Created by Thomas Butler on 29/04/2019.
//
//  File Purpose: Class Functionality
//  Defines the functionality of the board class. See the associated for a brief description of what the purpose of each function is. The comments in these functions give some more detail on how each was accomplished.

#include <iostream>
#include <vector>
#include "Pawn.h"
#include "Knight.h"
#include "Bishop.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"
#include "board.h"
#include "Menu.h"
using namespace std;

//=======================================================================================
//                          CONSTRUCTORS & DESTRUCTOR
board::board() {}
//  Parametrised constructor
board::board(vector<vector<square>> _elements) {elements=_elements;}
//  Copy constructor
board::board(const board& _board) {elements=_board.elements;}
board::~board() {}
//=======================================================================================
//                              ACCESSOR FUNCTIONS
shared_ptr<piece> board::_elements_contents(coords location) {
    int x=location.first-65; int y=location.second-1;
    return elements[y][x]._contents();
}
//=======================================================================================
//                              MEMBER FUNCTIONS
//  Draw out the board, using data from all of the 64 squares contained in the vector of vectors
void board::draw() {
    //========================
    //  Console Version
    if (!elements.empty()) {
        vector<vector<square>>::iterator row;
        vector<square>::iterator col;
        int count{1};
        for (row = elements.begin(); row != elements.end(); row++) {
            for (int square_row=0; square_row<5; square_row++) {
                if (square_row==2) cout << count << " ";
                else cout << "  ";
                for (col=row->begin(); col!=row->end(); col++) {

                    if (square_row!=2 || col->_contents()==nullptr) {
						//	Write out each of the 5 cells that make up a single row of the square
						if (col->colour == 'w') cout << (char)WHITE_SQUARE << (char)WHITE_SQUARE << (char)WHITE_SQUARE << (char)WHITE_SQUARE << (char)WHITE_SQUARE;
						else cout << (char)BLACK_SQUARE << (char)BLACK_SQUARE << (char)BLACK_SQUARE << (char)BLACK_SQUARE << (char)BLACK_SQUARE;

						//	Write out the name of the piece in the middle row of the square
                    } else if (col->_contents()!=nullptr) {
						if (col->colour == 'w') cout << (char)WHITE_SQUARE << *col << (char)WHITE_SQUARE;
						else cout << (char)BLACK_SQUARE << *col << (char)BLACK_SQUARE;
                    }
                }
                cout << endl;
            }
            count++;
        }
        cout << "    A    B    C    D    E    F    G    H" << endl;
    } else cout << "Empty board." << endl;
    //========================
}

//  Move a piece
board& board::move_piece(coords initial, coords finish) {
    //  Now move the pieces
    int x_i=initial.first-65; int y_i=initial.second-1;
    int x_f=finish.first-65; int y_f=finish.second-1;
    
    shared_ptr<piece> chosen=elements[y_i][x_i]._contents();
    //chosen->increment_move_count();
    
    //  Now move the pieces
    if (elements[y_f][x_f]._contents()==nullptr) {
        elements[y_i][x_i].swap_contents(elements[y_f][x_f]);
    } else {
        //cout << "Taking another piece" << endl;
        elements[y_f][x_f].clear_contents();
        elements[y_i][x_i].swap_contents(elements[y_f][x_f]);
    }
    return *this;
}

//  Pawn promotion move, where a pawn is changed to another piece as per the user's choice
board& board::pawn_promotion(coords pawn_location, coords end_location) {
    int x_i=pawn_location.first-65; int y_i=pawn_location.second-1;
    int x_f=end_location.first-65; int y_f=end_location.second-1;
    shared_ptr<piece> chosen_pawn = elements[y_i][x_i]._contents();
    char colour = chosen_pawn->_colour();
    
    //  If at the black end, it must be a white pawn that got there
    //  If at the white end, it must be a black pawn that got there
    //  User a menu to provide the selections to turn the piece into
    menu pawn_promotion_menu("Select what piece to promote the pawn to:\n",
                   "Invalid input.",
                   "-> ",
                   //    Now include all of the inputs, and the functions that they call
                   {
                       //   First option: promote pawn to a knight
                       {"knight", [&chosen_pawn,&colour] { //  Write the function that is executed on this selection
                           shared_ptr<piece> replacement (new Knight(colour));
                           chosen_pawn.reset();
                           chosen_pawn=replacement;
                       }},
                       //   Second option: promote pawn to a rook
                       {"rook", [&chosen_pawn,&colour] {
                           shared_ptr<piece> replacement (new Rook(colour));
                           chosen_pawn.reset();
                           chosen_pawn=replacement;
                       }},
                       //   Third option: promote pawn to a bishop
                       {"bishop", [&chosen_pawn,&colour] {
                           shared_ptr<piece> replacement (new Bishop(colour));
                           chosen_pawn.reset();
                           chosen_pawn=replacement;
                       }},
                       //   Fourth option: promote pawn to a queen
                       {"queen", [&chosen_pawn,&colour] {
                           shared_ptr<piece> replacement (new Queen(colour));
                           chosen_pawn.reset();
                           chosen_pawn=replacement;
                       }}
                   });
    //  This runs the menu, which will keep requesting input until it matches one of the keys
    pawn_promotion_menu();
    elements[y_i][x_i].clear_contents();
    elements[y_f][x_f].change_contents(chosen_pawn);
    return *this;
}

//  Determines if a move is valid, discarding the location of the king
bool board::valid_move(coords initial, coords finish) {
    //  Checks that this functions goes through
    //  --> we are actually moving a piece, not chosen an empty square
    //  --> the square we are moving to is either empty, or has an enemy piece
    //  --> we have found the suggested move in the map of idealised possible moves
    //  --> the path of the piece is not obstructed by any other pieces
    //  Convert the coordinates into integers, that can be used in accessing elements of the vector<vector<square>>
    int x_i=initial.first-65; int y_i=initial.second-1;
    int x_f=finish.first-65; int y_f=finish.second-1;
    
    //  Get the chosen piece
    shared_ptr<piece> chosen_piece = _elements_contents(initial);
    //  If there is nothing in the chosen space, nothing to move
    if (chosen_piece==nullptr) return false;
    //  Get the piece in the square we are trying to attack
    shared_ptr<piece> attacked_piece = _elements_contents(finish);
    //  Get the vector of coordinates where the chosen piece could move on an empty board
    vector<coords> possible_moves = chosen_piece->ideal_valid_moves(initial);
    //  Determine if any of these possible moves match the selected finishing coordinate
    bool found_move{false};
    for (auto it=possible_moves.begin(); it!=possible_moves.end(); it++) {
        if (*it==finish) {found_move=true;break;}
    }
    if (!found_move) return false; //  no match means empty vector, so return false
    
    //  Now make sure we are moving to either an empty square or one containing an enemy piece
    if (attacked_piece!=nullptr) {
        if (attacked_piece->_colour()==chosen_piece->_colour()) return false;
    }
    
    //  Make sure that there is nothing in the path of the piece as it moves along the board
    if (chosen_piece->_type()=="Pawn") {
        //  For a Pawn to move diagonally, it must be attacking a piece
        if (attacked_piece==nullptr && (initial.first!=finish.first)) return false;
        //  A pawn cannot attack a piece directly in front of it
        if (attacked_piece!=nullptr && initial.first==finish.first) return false;
        //  A Pawn cannot jump over another piece
        //  The following checks what direction the pawn is trying to move
        //  Then it checks that there is nothing in the middle spot
        if ((y_f-y_i==2) && elements[y_i+1][x_i]._contents()!=nullptr) return false;
        if ((y_f-y_i==-2) && elements[y_f+1][x_f]._contents()!=nullptr) return false;
    }
    
    if (chosen_piece->_type()=="Bishop" || chosen_piece->_type()=="Rook" || chosen_piece->_type()=="Queen") {
        //  Get the path that the piece would need to take to get to the final square
        vector<coords> path = chosen_piece->path_to_square(initial, finish);
        //  Determine if any of the squares on that path have a piece in it
        if (!path.empty()) {
            for (auto it=path.begin(); it!=path.end(); it++) {
                if (_elements_contents(*it)!=nullptr) return false;
            }
        }
    }
    
    //  The King cannot move to a spot where it could be taken by an enemy piece
    //  Call the function specifically for the King
    //  This function determines all of the places that the other pieces can possibly move to
    
    //  If it has passed ALL of these checks, then return true
    return true;
}

//  Determines if a move will leave the King vulnerable
bool board::leaves_king_vulnerable(coords initial, coords finish) {
    //  Uses the colour of the chosen piece to determine what King we are wanting to protect
    //  Finds the position of that King
    //  We are assuming that we are not moving the King, but rather moving another friendly piece
    //  Need to know if the piece we are moving is intercepting the path of any of the other peices
    //  More specifically, we need to know if the piece we are wanting to move is the LAST in the path between the enemy and the King
    char colour = _elements_contents(initial)->_colour();
    board bar(*this);
    bar.move_piece(initial, finish);
    //  Must decrement move count
    //  See if the owners of the shared pointer increase
    
    if (check(colour)) {
        if (bar.check(colour)) return true;
        if (!bar.check(colour)) return false;
    } else {
        if (bar.check(colour)) return true;
        if (!bar.check(colour)) return false;
    }
    return false;
}

//  Returns all the possible moves that can be made by a given player
vector<vector<coords>> board::all_possible_valid_moves(char player_colour) {
    //  Object to return, arbitrary name
    vector<vector<coords>> foobar;
    //  Loop through every place on the board
    for (auto row=elements.begin(); row!=elements.end(); row++) {
        for (auto col=row->begin(); col!=row->end(); col++) {
            //  See if this square is empty or not
            shared_ptr<piece> contents=col->_contents();
            if (contents!=nullptr) {
                //  See if the piece belongs to the player
                if (contents->_colour()==player_colour) {
                    //  Get all the idealised possible moves for this piece
                    vector<coords> idealised_possible_moves=contents->ideal_valid_moves(col->_location());
                    //  Now loop through all of these moves
                    for (auto _move=idealised_possible_moves.begin(); _move!=idealised_possible_moves.end();) {
                        //  If this move is not a valid move, then delete it from the vector
						if (!valid_move(col->_location(), *_move)) {
							idealised_possible_moves.erase(_move); _move = idealised_possible_moves.begin();
						}
						else if (leaves_king_vulnerable(col->_location(), *_move)) {
							idealised_possible_moves.erase(_move); _move = idealised_possible_moves.begin();
						}
                        //  If it is a valid move, increment the iterator
                        else _move++;
                    }
                    //  Left the loop. If the vector of coordinates is not empty, add it to the all_possible_valid_moves
                    if (!idealised_possible_moves.empty()) {
                        idealised_possible_moves.insert(idealised_possible_moves.begin(), col->_location());
                        foobar.push_back(idealised_possible_moves);
                    }
                }
            }
        }
    }
    
    return foobar;
}

//  Write out all of the possible moves that can be made by a given player
void board::write_all_possible_valid_moves(char player_colour) {
    //  Get all the possible valid moves from the member function of board
    vector<vector<coords>> foobar = all_possible_valid_moves(player_colour);
    //  Loop through each valid starting coordinates on the board for the player
    for (auto _piece=foobar.begin(); _piece!=foobar.end(); _piece++) {
        //  Loop through the relevant pieces valid moves, and write them out
        for (auto _move=_piece->begin(); _move!=_piece->end(); _move++) {
            if (_move==_piece->begin()) cout << _elements_contents(*_move)->_type() << '\t';
            cout << _move->first << _move->second;
            if (_move==_piece->begin()) cout << " -> ";
            else cout << " ";
        }
        cout << endl;
    }
}

//  Determine if a given player is in check, i.e., their King is vulnerable
bool board::check(char player_colour) {
    //  Find where the player's King is located
    coords king_location;
    bool found{false};
    for (auto row=elements.begin(); row!=elements.end(); row++) {
        for (auto col=row->begin(); col!=row->end(); col++) {
            shared_ptr<piece> contents = col->_contents();
            if (contents!=nullptr)
                if (contents->_type()=="King" && contents->_colour()==player_colour) {
                    king_location=col->_location();
                    found=true;
                    break;
                }
        }
    }
    if (!found) return false;
    
    for (unsigned int i{0}; i<elements.size(); i++) {
        for (unsigned int j{0}; j<elements[i].size(); j++) {
            shared_ptr<piece> contents=elements[i][j]._contents();
            if (contents!=nullptr)
                if (contents->_colour()!=player_colour) {
                    coords piece_location=elements[i][j]._location();
                    if (valid_move(piece_location, king_location)) return true;
                }
        }
    }
    return false;
}

