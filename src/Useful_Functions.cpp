//
//  Useful_Functions.cpp
//  Project
//
//  Created by Thomas Butler on 01/05/2019.
//
//  File Purpose: Function Definitions
//  Defines the functions in the associated header file.
//  1.  chess_rules is very standard, uses cout to write to the screen the rules of the game.
//  2.  pieces_key writes out the key to the user, simple.
//  3.  play_game is where the majority of the program comes together into the functioning game
//  4.  start_board sets up the board as it should be to start the game


//  Included Header Files: Standard Library
//  iostream    --> to write out to the console, input/output streams
//  string      --> to use string variables, such as analysing input from the user
//  cctype      --> character handling functions, classifying and transforming individual characters

//  Included Header Files: Author Written
//  ALL of them, as this is where the code is all brought together into becoming a functioning game


#include <iostream>
#include <string>
#include <cctype>
#include "Definitions.h"
#include "piece.h"
#include "Pawn.h"
#include "Knight.h"
#include "Rook.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Game.h"
#include "Menu.h"

//  Using this namespace as only used standard library functions
using namespace std;

void chess_rules() {
    cout << endl << "Goal of Chess:" << endl;
    cout << "The aim of the game is to out-manoeuvre the opponent to a point where they can make no moves that will save their King from being under attack. " << endl;
    cout << endl;
    cout << "How the pieces move: " << endl;
    cout << "--> Generally, pieces can not jump other pieces." << endl;
    cout << "--> It is not allowed to take your own piece." << endl;
    cout << "--> Any piece can take any other enemy piece." << endl;
    cout << "Pawns: Generally, Pawns can only move forward one space at a time. They can attack diagonally, again only moving one space forward. If the pawn has yet to be moved, they can move forward two spaces." << endl;
    cout << "Knights --> move in an L-shape, i.e., two places horizontally (vertically) and one place vertically (horizontally). Knights are allowed to jump pieces." << endl;
    cout << "Rooks --> move horiztonally or vertically any number of space." << endl;
    cout << "Bishops --> move diagonally any number of space in any direction." << endl;
    cout << "Queens --> move as rooks and bishops do." << endl;
    cout << "Kings --> may only move one space at a time in any direction." << endl;
    cout << endl;
    cout << "To pause the game, enter `pause' when prompted for input." << endl;
    cout << endl;
}

void pieces_key() {
    cout << "Piece Key:" << endl;
    cout << "Piece \t | white | black" << endl;
    cout << "Pawn  \t |  wpn  |  bpn" << endl;
    cout << "Knight\t |  wkt  |  bkt" << endl;
    cout << "Rook  \t |  wrk  |  brk" << endl;
    cout << "Bishop\t |  wbs  |  bbs" << endl;
    cout << "Queen \t |  wqn  |  bqn" << endl;
    cout << "King  \t |  wkg  |  bkg" << endl;
}

Game play_game(Game chess) {
    //  Draws the current board
    chess.current_board.draw();
    
    //  Variable to hold opposing player. Initialise to avoid warnings
    char opposing_player{'n'};
    
    //  This character will be sent down to functions, dependent on whose turn it is
    while  (chess.current_board.all_possible_valid_moves('w').size()!=0 &&
            chess.current_board.all_possible_valid_moves('b').size()!=0) {
        //  Determine whose turn it is by if it is an even or odd number of turns
        if (chess.number_of_moves%2==0) {
            chess.whose_turn='w';
            opposing_player='b';
            cout << "White player's turn." << endl;
        }
        if (chess.number_of_moves%2==1) {
            chess.whose_turn='b';
            opposing_player='w';
            cout << "Black player's turn." << endl;
        }
        
        cout << "Enter a move of the form C6 A3, or `pause' to pause." << endl;
        cout << "-> ";
        
        
        //  Get an validate input from the user
        bool valid_input{false};
        vector<coords> input_coordinates;
        do {
            //  Empty the input coordinates vector. If this is not done, can get stuck in an infinite loop
            input_coordinates.clear();
            //  Get the input from the user
            string input;
            getline(cin, input);
            //  If the user has inputted to pause the game, pause the game
            if (input=="pause") {cout << endl; return chess;}
            
            //  Now see if the input is of the form A4 C5
            //  Now try to extract two pairs of characters: do not need to be separated by a space
            //  Loop through the string and determine if any characters are not a space or alphanumeric
            
            //  Use a try and catch so that can skip sections of code at different tests
            try {
                //  Loop through the string, see if there are any unwelcome characters
                //  Functions such as isalnum, isspace need the <cctype> header include
                //  Note: important to not always increase the iterator when erasing characters
                for (auto it=input.begin(); it!=input.end();) {
                    //  If not an alpha-numerical character or a space, go to catch block
                    if (!isalnum(*it)&&!isblank(*it)) throw valid_input;
                    //  If it is a space, erase that character --> unnecessary character
                    if (isblank(*it)) input.erase(it);
                    //  Only if not erasing a character is the iterator increase, else characters are missed
                    else it++;
                }
                
                //  If the user has not entered 4 useful characters, throw to catch block
                if (input.size()!=4) throw valid_input;
                
                //  Now need to make sure that the input is of the form A4 D6
                //  Characters 1 and 3 must be alphabetical (counting in C++, -> 0 and 2)
                //  Characters 2 and 4 must be numerical (counting in C++, -> 1 and 3)
                //  If these conditions are not met, through to the catch block
                if (!isalpha(input[0])||!isalpha(input[2])) throw valid_input;
                if (!isdigit(input[1])||!isdigit(input[3])) throw valid_input;
                
                
                //  Now make sure that the input is in a valid range
                if (input[0]<'A'||input[0]>'H') throw valid_input;
                if ((int)(input[1]-'0')<1||(int)(input[1]-'0')>8) throw valid_input;
                if (input[2]<'A'||input[2]>'H') throw valid_input;
                if ((int)(input[3]-'0')<1||((int)input[3]-'0')>8) throw valid_input;
                
                //  If we have got here, we are good to go!
                //  Convert the two pairs of characters into type coords
                coords first_location(make_pair(input[0],(int)(input[1]-'0')));
                coords second_location(make_pair(input[2], (int)(input[3]-'0')));
                input_coordinates.push_back(first_location);
                input_coordinates.push_back(second_location);
                
                
                //  Make an initial check that the square chosen first is not empty
                if (chess.current_board._elements_contents(input_coordinates[0])==nullptr) throw valid_input;
                //  Check that the player is trying to move a piece that belongs to them
                if (chess.current_board._elements_contents(input_coordinates[0])->_colour()!=chess.whose_turn) throw valid_input;
                //  Now check is to see if this is, in fact, a valid move on the board
                //  Do this order as this will cover the majority of checks
                if (!chess.current_board.valid_move(input_coordinates[0], input_coordinates[1])) throw valid_input;
                //  Last, make sure that the move does not leave the King vulnerable to an attack
                if (chess.current_board.leaves_king_vulnerable(input_coordinates[0], input_coordinates[1])) throw valid_input;
                
                //  Move is valid, store the move in the past moves text member of the game
                chess.past_moves_text.push_back(make_pair(input_coordinates[0],input_coordinates[1]));
                
                //  The input has been validated, now may continue with the execution of the program
                valid_input=true;
            } catch (bool) {
                cout << "Invalid input." << endl;
            }
            //  Continues to loop, requesting input until the input is valid
        } while (!valid_input);
        
        //  Got to a point where the move is valid, now just need to execute the move
        chess.previous_moves_boards.push_back(chess.current_board);
        shared_ptr<piece> chosen=chess.current_board._elements_contents(input_coordinates[0]);
        //  Now ask if a piece was taken off the board. This is done by checking if the square moving to was not empty
        //  Determine if the move has qualified for a pawn promotion
        if (chosen->_type()=="Pawn"&&(input_coordinates[1].second-1==0||input_coordinates[1].second-1==7)) {
            chess.current_board.pawn_promotion(input_coordinates[0], input_coordinates[1]);
        } else {    //  If not, then proceed with simply moving the piece
            chess.current_board.move_piece(input_coordinates[0], input_coordinates[1]);
        }
        chess.number_of_moves++;
        chess.current_board.draw();
        
        //  Determine if the board is in check due to the move just made
        if (chess.current_board.check(opposing_player)) {
            cout << "Check" << endl;
            //  If the game is in check, see if it is in checkmate
            if (chess.current_board.all_possible_valid_moves(opposing_player).size()==0) {
                cout << "Checkmate." << endl;
                return chess;
            }
            //  If not in check, the game can still be in stalemate
        } else if (chess.current_board.all_possible_valid_moves(opposing_player).size()==0){
            cout << "Stalemate." << endl;
            return chess;
        }
    }
    return chess;
}

board start_board() {
    vector<vector<square>> board_elements;
    vector<square> rows;
    
    for (int i{0}; i<65; i++) {
        if ((i%8==0 && i!=0) || i==64) {    //  every 8, start a new row
            board_elements.push_back(rows);
            rows.clear();
        }
        //  alternates between black and white squares appropriately
        if ((i%2 + i/8)%2 == 0) {
            square bar(nullptr,i,'w');
            rows.push_back(bar);
        } else {
            square bar(nullptr,i,'b');
            rows.push_back(bar);
        }
    }
    
    //  Use shared pointers for the pieces
    //  Can swap the contents of two shared pointers without destroying the contents or changing the number of ownership
    
    //  Set up the black unique row
    //  Create the two black Rooks
    shared_ptr<piece> black_rook (new Rook('b'));
    board_elements[0][0].change_contents(black_rook);
    black_rook.reset(); // free this black rook from ownership
    //  Must create another black rook, else the same rook will have two owners
    shared_ptr<piece> black_rook2 (new Rook('b'));
    board_elements[0][7].change_contents(black_rook2);
    black_rook2.reset(); // free this black rook from ownership
    //  Create the two black Knights
    shared_ptr<piece> black_knight (new Knight('b'));
    shared_ptr<piece> black_knight2 (new Knight('b'));
    board_elements[0][1].change_contents(black_knight);
    board_elements[0][6].change_contents(black_knight2);
    black_knight.reset(); black_knight2.reset();
    //  Create the two black Bishops
    shared_ptr<piece> black_bishop (new Bishop('b'));
    shared_ptr<piece> black_bishop2 (new Bishop('b'));
    board_elements[0][2].change_contents(black_bishop);
    board_elements[0][5].change_contents(black_bishop2);
    black_bishop.reset(); black_bishop2.reset();
    //  Create the black Queen
    shared_ptr<piece> black_queen (new Queen('b'));
    board_elements[0][4].change_contents(black_queen);
    //  Create the black King
    shared_ptr<piece> black_king (new King('b'));
    board_elements[0][3].change_contents(black_king);
    //  Set up all the black pawns
    for (unsigned int i{0}; i<board_elements[1].size(); i++) {
        shared_ptr<piece> black_pawn (new Pawn('b'));
        board_elements[1][i].change_contents(black_pawn);
        black_pawn.reset();
    }
    //  Set up all the white pawns
    for (unsigned int i{0}; i<board_elements[6].size(); i++) {
        shared_ptr<piece> white_pawn (new Pawn('w'));
        board_elements[6][i].change_contents(white_pawn);
        white_pawn.reset();
    }
    
    //  Set up the white unique row
    //  Create the two white Rooks
    shared_ptr<piece> white_rook (new Rook('w'));
    board_elements[7][0].change_contents(white_rook);
    white_rook.reset(); // free this black rook from ownership
    //  Must create another white rook, else the same rook will have two owners
    shared_ptr<piece> white_rook2 (new Rook('w'));
    board_elements[7][7].change_contents(white_rook2);
    white_rook2.reset(); // free this black rook from ownership
    //  Create the two white Knights
    shared_ptr<piece> white_knight (new Knight('w'));
    shared_ptr<piece> white_knight2 (new Knight('w'));
    board_elements[7][1].change_contents(white_knight);
    board_elements[7][6].change_contents(white_knight2);
    white_knight.reset(); white_knight2.reset();
    //  Create the two white Bishops
    shared_ptr<piece> white_bishop (new Bishop('w'));
    shared_ptr<piece> white_bishop2 (new Bishop('w'));
    board_elements[7][2].change_contents(white_bishop);
    board_elements[7][5].change_contents(white_bishop2);
    white_bishop.reset(); white_bishop2.reset();
    //  Create the white Queen
    shared_ptr<piece> white_queen (new Queen('w'));
    board_elements[7][4].change_contents(white_queen);
    //  Create the white King
    shared_ptr<piece> white_king (new King('w'));
    board_elements[7][3].change_contents(white_king);
    
    board foo(board_elements);
    return foo;
}
