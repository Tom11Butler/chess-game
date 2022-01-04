//
//  Menu.cpp
//  Project
//
//  Created by Thomas Butler on 29/04/2019.
//
//  File Purpose: Class Functionality
//  Gives functionality to the menu class. Only the constructor and `run' function need to be defined


#include "Menu.h"
#include <functional>
#include <iostream>

//=======================================================================================
//                          CONSTRUCTORS & DESTRUCTOR
//  Constructor for the menu
//  Added an underscore to the variable names to indicate they are the inputted values
menu::menu(const string& message_, const string& invalid_command_message_,
                 const string& prompt_,
                 const unordered_map<string, function<void()>>& command_choices_)
//  Now set all of the member data to their appropiate values
{
    message=message_;
    invalid_command_message=invalid_command_message_;
    prompt=prompt_;
    command_choices=command_choices_;
}
//  Destructor for the menu
menu::~menu() {}
//=======================================================================================
//                              MEMBER FUNCTIONS

//  To `run' a menu, only need to call with () at the end of its name
//  This function
void menu::operator()() {
    string user_choice;
    //  Write out the menu
    cout << message;
    for (const auto& command_choice : command_choices) {    //  loop through all options in the menu
        //  Each key is accessed by the member function `first()' of <unordered_map>
        cout << '[' << command_choice.first << ']' << '\n';
    }
    cout << prompt;
    //  Will use an iterator to loop through each of the elements of the unordered map
    //  Set the iterator `result' to the end of the command choices
    auto result=command_choices.end();
    //  If the user input is not found in the map, then the iterator will be equal to the end
    //  This loop will always run at least once
    while ((result=command_choices.find(user_choice)) == command_choices.end()) {
        //  Gets the line from the input stream, stores into the string `user_choice'
        getline(cin,user_choice);
        //  Output an error message if the user input is not found
        if (command_choices.find(user_choice) == command_choices.end()) {
            cout << "Invalid input." << endl;
            cout << prompt;
        }
    }
    //  Access the `value' (in this case a function) of the unordered map with the iterator
    //  The member function `second()' of an unordered map returns the value of that entry
    result->second();
}
