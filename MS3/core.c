/*
*****************************************************************************
                        Assignment 1 - Milestone 3
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

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "core.h"

//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void)
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}

// Wait for user to input the "enter" key to continue
void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

//
// Copy your work done from Milestone #2 (core.c) into this file
// - Organize your functions in the same order as they are listed in the core.h file
//



//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

//test 1
int inputInt(void)
{
    int number = 0;
    char newline = 'x';
    do
    {
        scanf("%d%c", &number, &newline);
        if (newline != '\n')
        {
            printf("Error! Input a whole number: ");
            clearInputBuffer();
        }
        else
        {
            break;
        }
    } while (newline != '\n');
    return number;
}

//test 2
int inputIntPositive(void)
{
    int number = 0;
    char newline = 'x';
    do
    {
        scanf("%d%c", &number, &newline);
        if (newline != '\n' || number < 0)
        {
            if (newline == '\n')
            {
                printf("ERROR! Value must be > 0: ");
            }
            else
            {
                printf("Error! Input a whole number: ");
                clearInputBuffer();
            }
        }
    } while (newline != '\n' || number < 0);
    return number;
}

//test 3.4
int inputIntRange(int lowerBound, int upperBound)
{
    int number = 0;
    char newline = 'x';
    do
    {
        scanf("%d%c", &number, &newline);
        if (newline != '\n' || number < lowerBound || number > upperBound)
        {
            if (number < lowerBound || number > upperBound)
            {
                printf("ERROR! Value must be between %d and %d inclusive: ", lowerBound, upperBound);
            }
            else
            {
                printf("Error! Input a whole number: ");
                clearInputBuffer();
            }
        }
    } while (newline != '\n' || number < lowerBound || number > upperBound);
    return number;
}


//test 5
char inputCharOption(const char* charOption)
{
    char firstChar = 'y';
    char newline = 'x';
    int flag = 0;
    do
    {
        scanf("%c%c", &firstChar, &newline);
        if (newline == '\n')
        {
            int i = 0;
            while (charOption[i] != 0 && flag == 0)  // ??????
            {
                if (charOption[i] == firstChar)
                {
                    flag = 1;
                }
                else
                    i++;
            }
        }
        else
        {
            clearInputBuffer();
        }
        if (flag == 0)
        {
            printf("ERROR: Character must be one of [yn]: ");
        }
    } while (flag == 0);
    return firstChar;
}


//test 6.7.8
void inputCString(char* string, int minNum, int maxNum)
{
    char temChar[20] = { '\0' };
    int counter = 0;
    int flag = 0;
    int i = 0;
    do
    {
        scanf("%[^\n]", temChar);
        int i = 0;
        counter = 0;
        while (temChar[i] != '\0')
        {
            counter++;
            i++;
        }
        if (maxNum == minNum && counter != maxNum)
        {
            printf("ERROR: String length must be exactly %d chars: ", maxNum);
            clearInputBuffer();
        }
        else if (counter > maxNum)
        {
            printf("ERROR: String length must be no more than %d chars: ", maxNum);
            clearInputBuffer();
        }
        else if (counter < minNum)
        {
            printf("ERROR: String length must be between %d and %d chars: ", minNum, maxNum);
            clearInputBuffer();
        }
        else if (counter >= minNum && counter <= maxNum)
        {
            flag = 1;
        }
    } while (flag == 0);
    clearInputBuffer();
    for (i = 0; i < counter; i++)
    {
        string[i] = temChar[i];
    }
}

//test 9
void displayFormattedPhone(const char* phoneNum)
{
    int i = 0;
    int counter = 0;
    if (phoneNum == NULL)
    {
        printf("(___)___-____");
    }
    else
    {
        i = 0;
        counter = 0;
        while (phoneNum[i] != '\0')
        {
            if (phoneNum[counter] < '0' || '9' < phoneNum[counter])
            {
                break;
            }
            counter++;
            i++;
        }
        if (counter != 10)
        {
            printf("(___)___-____");
        }
        else
        {
            printf("(");
            for (i = 0; i < 3; i++)
            {
                printf("%c", phoneNum[i]);
            }
            printf(")");
            for (i = 3; i < 6; i++)
            {
                printf("%c", phoneNum[i]);
            }
            printf("-");
            for (i = 6; i < 10; i++)
            {
                printf("%c", phoneNum[i]);
            }
        }
    }
}

