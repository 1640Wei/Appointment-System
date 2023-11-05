/*
*****************************************************************************
                        Assignment 1 - Milestone 2
Full Name  :Ching Wei Lai
Student ID#:136893211
Email      :cwlai6@myseneca.ca
Section    :NHH

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/

// SAFE-GUARD: 
// It is good practice to apply safe-guards to header files
// Safe-guard's ensures only 1 copy of the header file is used in the project build
// The macro name should be mirroring the file name with _ for spaces, dots, etc.

// !!! DO NOT DELETE THE BELOW 2 LINES !!!
#ifndef CORE_H
#define CORE_H


// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// 
// Copy your work done from Milestone #1 (core.h) into this file
// 
// NOTE:
// - Organize your functions into the below categories
// - Make sure the core.c file also lists these functions in the same order!
// - Be sure to provide a BRIEF comment for each function prototype
// - The comment should also be copied to the core.c function definition
//
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void);

// Wait for user to input the "enter" key to continue
void suspend(void);

//test 9
void displayFormattedPhone(const char* phoneNum);


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

//test 1
int inputInt(void);

//test 2
int inputIntPositive(void);

//test 3.4
int inputIntRange(int lowerBound, int upperBound);

//test 5
char inputCharOption(const char charOption[]);

//test 6.7.8
void inputCString(char* string, int minNum, int maxNum);

// !!! DO NOT DELETE THE BELOW LINE !!!
#endif // !CORE_H


