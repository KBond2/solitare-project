/*WIP of figuring out the basics of how to put together solitare, as of 03/17/2025 I have gotten to making a shuffled deck*/


/*
Cards are stored in string arrays, 3 digit string representing a random card ("s01"-"s13" represents spade ace up to king)
Every pile has a revealed variable, number up to which they are revealed for display. 
*/

#include <iostream>
#include <array>
#include <cstdlib>
using namespace std;

string cardDecoder(string);

int main()
{
    const int DECK_SIZE = 52;
    const int RANKS = 13;
    const int SUITS = 4;
    string line1[DECK_SIZE];
    string line2[DECK_SIZE];
    string line3[DECK_SIZE];
    string line4[DECK_SIZE];
    string line5[DECK_SIZE];
    string line6[DECK_SIZE];
    string line7[DECK_SIZE];

    string waste[DECK_SIZE];
    string deck[DECK_SIZE];

    string blankDeck[DECK_SIZE];
    
    string hearts[RANKS];
    string diamonds[RANKS];
    string spades[RANKS];
    string clubs[RANKS];

    string cardToRandomize;
    
    int randomDeckNumber;

    int deckNum = 0;
    int i;
    int j;

    srand(time(NULL));
    /*
    randomDeckNumber = rand() % 52;
    cout << randomDeckNumber << endl;
    deck[randomDeckNumber] = "abc";
    cout << sizeof(deck) << endl;
    deck[51] = "gef";
    cout << sizeof(deck);
    */

    //Create unshuffled deck of 52 cards
    for (i = 1; i <= 13; i++)
    {
        for (j = 1; j <= 4; j++)
        {
            //cout << "DEBUG: i = " << i << ", j = " << j << ", deckNum = " << deckNum << endl;
   
            switch(j)
            {    
                case 1:
                    if (i < 10)
                        blankDeck[deckNum] = "h" + to_string(i);
                    else if (i == 10)
                        blankDeck[deckNum] = "h0";
                    else if (i == 11)
                        blankDeck[deckNum] = "hj";
                    else if (i == 12)
                        blankDeck[deckNum] = "hq";
                    else
                        blankDeck[deckNum] = "hk";
                    break;
                case 2:
                    if (i < 10)
                        blankDeck[deckNum] = "d" + to_string(i);
                    else if (i == 10)
                        blankDeck[deckNum] = "d0";
                    else if (i == 11)
                        blankDeck[deckNum] = "dj";
                    else if (i == 12)
                        blankDeck[deckNum] = "dq";
                    else
                        blankDeck[deckNum] = "dk";
                    break;
                case 3:
                    if (i < 10)
                        blankDeck[deckNum] = "s" + to_string(i);
                    else if (i == 10)
                        blankDeck[deckNum] = "s0";
                    else if (i == 11)
                        blankDeck[deckNum] = "sj";
                    else if (i == 12)
                        blankDeck[deckNum] = "sq";
                    else
                        blankDeck[deckNum] = "sk";
                    break;
                case 4:
                    if (i < 10)
                        blankDeck[deckNum] = "c" + to_string(i);
                    else if (i == 10)
                        blankDeck[deckNum] = "c0";
                    else if (i == 11)
                        blankDeck[deckNum] = "cj";
                    else if (i == 12)
                        blankDeck[deckNum] = "cq";
                    else
                        blankDeck[deckNum] = "ck";
            }
            deckNum += 1;
        }
    }
    
    //for (i = 0; i < 52; i++)
        //cout << blankDeck[i] << " ";


    // Shuffle deck of 52 cards
    
    for (deckNum = 0; deckNum < 52; deckNum++)
    {
        
        randomDeckNumber = rand() % (52 - (deckNum));
        deck[deckNum] = blankDeck[randomDeckNumber];
        //if (blankDeck[randomDeckNumber - 1] == "ck")
            //cout << "aye";
        for (i = (randomDeckNumber); i < 51; i++)
        {
            blankDeck[i] = blankDeck[i + 1];                        
        }

        /*cout << "DEBUG: deck[" << deckNum << "] = " << deck[deckNum] << endl;
        cout << "DEBUG: blankDeck = ";
        for (j = 0; j < 52; j++)
            cout << blankDeck[j] << " ";
        string debugVariable;
        cin >> debugVariable;     
        */
    }
    for (i = 0; i < 52; i++)
        cout << deck[i] << " ";

    cout << "\nlast card in deck: " << deck[-1];
    cout << "\nCard number 5 in deck is the " << cardDecoder(deck[4]) << endl;
    
}

string cardDecoder(string card)
{
    string suit;
    string rank;
    string cardValue;
    switch (card[0])
    {
        case 'h':
            suit = "Hearts";
            break;
        case 'd':
            suit = "Diamonds";
            break;
        case 's':
            suit = "Spades";
            break;
        case 'c':
            suit = "Clubs";
            break;
    }
    switch (card[1])
    {
        case '1':
            rank = "Ace";
            break;
        case '2':
            rank = "Two";
            break;
        case '3':
            rank = "Three";
            break;
        case '4':
            rank = "Four";
            break;
        case '5':
            rank = "Five";
            break;
        case '6':
            rank = "Six";
            break;
        case '7':
            rank = "Seven";
            break;
        case '8':
            rank = "Eight";
            break;
        case '9':
            rank = "Nine";
            break;
        case '0':
            rank = "Ten";
            break;
        case 'j':
            rank = "Jack";
            break;
        case 'q':
            rank = "Queen";
            break;
        case 'k':
            rank = "King";
            break;
    }
    cardValue = rank + " of " + suit;
    return cardValue;
}
