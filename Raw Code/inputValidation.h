/*********************************************
Kethry Bond, Liam Block, Steve Saelee
Final Project - Header
Date Completed: April 20
Description: Contains the functions used to validate the user's input
Version: 1.0
*********************************************/

#pragma once

#include <iostream>
#include <string>

using namespace std;

string beginTurnInput (string getInputMessage) {
    //get t, m, w, d, or END. 
    bool isValidInput;
    string userInput;
    do
    {
        isValidInput = 1;
        cout << getInputMessage;
        cin >> userInput;
        if (userInput != "t" && userInput != "m" && userInput != "w" && userInput != "d" && userInput != "END")
        {
            isValidInput = 0;
            cin.ignore(1000, '\n');
        }


    } while (!isValidInput);

    return userInput;
};

string endTurnInput (string getInputMessage) {
    //get t, f, or w.
    bool isValidInput;
    string userInput;
    do
    {
        isValidInput = 1;
        cout << getInputMessage;
        cin >> userInput;
        if (userInput != "t" && userInput != "f" && userInput != "w")
        {
            isValidInput = 0;
            cin.ignore(1000, '\n');
        }


    } while (!isValidInput);

    return userInput;
};

string yOrN (string getInputMessage) {
    //get bool yes or no answer
    bool isValidInput;
    string userInput;
    do
    {
        isValidInput = 1;
        cout << getInputMessage;
        cin >> userInput;
        if (userInput != "y" && userInput != "n")
        {
            isValidInput = 0;
            cin.ignore(1000, '\n');
        }


    } while (!isValidInput);

    return userInput;
};

int specificRangeIntInput (string getInputMessage, int minVal, int maxVal) {
    bool isValidInput;
    string userInput;
    int userNum;
    do
    {
        isValidInput = 1;
        cout << getInputMessage;
        cin >> userInput;
        if (userInput.length() > 2)
        {
            isValidInput = 0;

        }
        else
        {
            for (char character : userInput)
            {
                if (!isdigit(character))
                {
                    isValidInput = 0;
                }
            }

        }
        if (isValidInput)
        {
            userNum = stoi(userInput);
            if (userNum > maxVal || userNum < minVal)
            {
                isValidInput = 0;
            }
        }
        if (!isValidInput)
        {
            cin.ignore(1000, '\n');
        }
    } while (!isValidInput);

    return userNum;
};

string lineOrCancel (string getInputMessage) {
    bool isValidInput;
    string userInput;
    do
    {
        isValidInput = 1;
        cout << getInputMessage;
        cin >> userInput;
        if (userInput.length() > 2)
        {
            isValidInput = 0;

        }
        else
        {
            if (userInput == "c")
            {
                continue;
            }
            else
            {
                for (char character : userInput)
                {
                    if (!isdigit(character))
                    {
                        isValidInput = 0;
                    }
                }
            }

        }
        if (isValidInput)
        {
            if (stoi(userInput) > 7 || stoi(userInput) < 1)
            {
                isValidInput = 0;
            }
        }
        if (!isValidInput)
        {
            cin.ignore(1000, '\n');
        }
    } while (!isValidInput);

    return userInput;
};

//Functionality taken from https://stackoverflow.com/questions/6486289/how-to-clear-the-console-in-c
void Clear()
{
#if defined _WIN32
    system("cls");
    //clrscr(); // including header file : conio.h
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
    //std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences 
#elif defined (__APPLE__)
    system("clear");
#endif
}
