//
//  Menu.h
//  Project
//
//  Created by Thomas Butler on 29/04/2019.
//
//  File Purpose: Class Declaration
//  This file contains the declaration of the Menu class, which is used when a user must enter one of a few predetermined options to advance in the program

//  Member data:
//  1.  A string for the message that will be outputted at the top of the menu
//  2.  A string for what will be outputted if the user input is not valid
//  --> The condition for invalid input is it not matching any of the keys of the unordered map
//  3.  An unordered map of all the commands that can be done from the menu
//  --> The user sees the possible inputs, and must type and enter any of them
//  --> If the input equals any of the keys of the map, then the associated function is called.
//  --> Unordered was chosen because, by cplusplusreference.com, the find() algorithm is logarithmic for <map>, yet constant in time for <unordered_map>. The difference is negligible, yet there was no special reason to choose <map> so went for unordered
//  This utitlises a map, where the key is the string (which will be inputted by the user), and the value is a function that will execute whatever the selection by the user was

//  Included Header Files:
//  unordered_map   --> allows use of the standard container of the same name
//  string          --> to be able to use string variables

#ifndef Menu_h
#define Menu_h

#include <unordered_map>
#include <functional>
#include <string>

using namespace std;

class menu {
private:
    string message;
    string invalid_command_message;
    string prompt;
    unordered_map<string, function<void()>> command_choices;
    
public:
    //  Constructor for the menu class
    menu(const string&, const string&, const string&, const unordered_map<string, function<void()>>&);
    ~menu(); // destructor
    void operator()();  //  overload the () operator so can simply write menu() to use the menu
};


#endif /* Menu_h */
