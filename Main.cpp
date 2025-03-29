/*WIP of figuring out the basics of how to put together solitare, as of 03/17/2025 I have gotten to making a shuffled deck*/


/*
Cards are stored in string arrays, 3 digit string representing a random card ("s01"-"s13" represents spade ace up to king)
Every pile has a revealed variable, number up to which they are revealed for display.
*/

#include <iostream>
#include <array>
#include <cstdlib>
#include "Deck.h"

using namespace std;

int main()
{
    Deck baseDeck;
    buildDeck(baseDeck);
    shuffleDeck(baseDeck);

    for (Card currentCard : baseDeck.shuffled) {
        cout << "Suit: " << currentCard.suit << " Rank: " << currentCard.rank << " Location: " << currentCard.deckLocation << endl;
    }
    
    //KB - Fill lines
    for (currentLineNum = 1; currentLineNum <= LINES; currentLineNum++)
    {
        for (currentCardNum = 0; currentCardNum < currentLineNum; currentCardNum++)
        {
            linesInPlay[currentLineNum-1].push_back(drawCard(baseDeck));
        }
    }
    
    //KB - Temp display of lines
    for (currentLineNum = 1; currentLineNum <= LINES; currentLineNum++)
    {
        cout << "Line " << currentLineNum << ": ";
        for (currentCardNum = 0; currentCardNum < currentLineNum; currentCardNum++)
        {
            cout << linesInPlay[currentLineNum-1].at(currentCardNum).rank << " OF " << linesInPlay[currentLineNum-1].at(currentCardNum).suit << " ";
        }
        cout << endl;
    }
    /*
    string line1[DECK_SIZE];
    string line2[DECK_SIZE];
    string line3[DECK_SIZE];
    string line4[DECK_SIZE];
    string line5[DECK_SIZE];
    string line6[DECK_SIZE];
    string line7[DECK_SIZE];

    string waste[DECK_SIZE];
    string deck[DECK_SIZE];
    */
}
