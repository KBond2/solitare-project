#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;

void startMenu();
void displayGameBoard();
void gameInfo();
int choice();

int main()
{
    int choice;

    startMenu();
    cin >> choice;
    while(cin.fail() || choice > 2 || choice < 1){ 
		cin.clear();
		cin.ignore(200, '\n');
		cout << "Invalid input! Enter choice between 1 - 2: ";
		cin >> choice;
	}

    if(choice == 1){
        cout << "Starting!";
        //displayGameBoard();
    }
    else if(choice == 2){
        gameInfo();
    }
}

void startMenu(){
    cout << "\t\tSolitare!\n";
    cout << "\t    K.B. / L.B. / S.S.\n\n";
    cout << "\t\t1. Start\n";
    cout << "\t\t2. How to Play\n\n\n";
    cout << "\t  Enter your choice (1-2): ";
}

int choice(){
    int choice;

    cin >> choice;
	while(cin.fail() || choice > 2 || choice < 1){
		cin.clear();
		cin.ignore(200, '\n');
		cout << "Invalid input! Enter choice between 1 - 2: ";
		cin >> choice;
	}
    return choice;
}

// When "How to Play" is selected, displays a series of 
// steps that explains how to play our version of Solitare.
void gameInfo(){
    int input;

// (INCOMPLETE) Steps to explain how to play standard Solitare and our C++ version of it.
    vector<string> soltaireSteps = {
        "1) ",
        "2) ",
        "3) ",
        "4) "
    };

// Loop that allows the user to read steps at their own pace.
    for(int i = 0; i < soltaireSteps.size(); i++){
        cout << soltaireSteps[i] << endl;
        cout << "Enter 1 to continue to next step: ";
        cin >> input;
        while(input != 1){
            cout << "Enter 1 to proceed to next step. ";
            cin.clear();
            cin.ignore(200, '\n');
            cin >> input;
        }
        cout << endl;
    }
    cout << "Starting game of Solitare...";
}

// (INCOMPLETE - SAMPLE) - Finish product will display board appropriately.

// Was thinking of having something similar to exercise 09 (Movie Theater Program) and having it
// print out the game board after each player action.
void gameBoard(){
    cout << "\t\tGame board: \n\n";
}

