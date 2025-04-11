/*WIP of figuring out the basics of how to put together solitare, as of 03/17/2025 I have gotten to making a shuffled deck*/


/*
Cards are objects with a suit, rank, and location. The location is an integer that represents the card's position in the deck.
The deck is a vector of cards, with a sorted and shuffled deck. The sorted deck is a deck with cards in order of suit and rank.
The shuffled deck is a deck with cards in random positions (deckLocation has been randomized) but still sorted by suit and rank.
Every pile has a revealed variable, number up to which they are revealed for display.
*/

#include <iostream>
#include <array>
#include <cstdlib>
#include "Deck.h"
#include "Gameplay.h"

using namespace std;

int main()
{
    Deck baseDeck;
    Board baseBoard;
    baseDeck.buildDeck();
    baseBoard = initializeBoardState(baseDeck);

    //KB: Variables for how many cards on the main piles are currently concealed
    int concealedIndex[7] = {0,1,2,3,4,5,6};

    //KB: Variables for gameplay
    bool gameOver = 0;
    string turnInput;
    Card currentCard = {"NULL","NULL",-1};




    //KB: Gameplay loop
    do
    {
        //NOTE: Display of board goes here v
        //for (Card currentCard : baseDeck.shuffledDeck) {
        //    cout << currentCard.suit << " " << currentCard.rank << endl;
        //}

        for (Group currentPile : baseBoard.PileSet) {
            for (Card currentCard : currentPile.group) {
                cout << currentCard.rank << " of " << currentCard.suit << "    ";
            }
            //cout << currentPile.pile[1].suit << endl;
            cout << endl;
        }


        do
        {
            currentCard = {"NULL","NULL",-1};
            cout << "Select a move:\n";
            cout << "Move card from piles (p)\nMove card from waste (w)\nDraw card from stock (d)\nEnd game (END)";
            //KB: TEMP, ADD INPUT VALIDATION LATER
            cin >> turnInput;

            //KB: Choose method of getting a card.
            if (turnInput == "p")
            {
                //currentCard = takeCardPiles(baseBoard.PileSet, concealedIndex);
                cout << "This is where taking a card from one of the main piles goes\n";
            }
            else if (turnInput == "w")
            {
                //currentCard = takeCardWaste(baseBoard.Waste);
                cout << "This is where taking a card from the waste goes\n";
            }
            else if (turnInput == "d")
            {
                //    V -- fill in with function of choice -KB
                //currentCard = drawCard()
                cout << "This is where the card drawing function goes\n";
                //NOTE: drawn card goes to waste functionality goes here? if drawn card cannot go anywhere it automatically
                //goes to the waste.
            }
            else if (turnInput == "END")
            {
                gameOver = 1;
                break;
            }
            else
            {
                cout << "No action found corresponding to input.\n";
            }

        } while (currentCard.suit == "NULL");

        if (gameOver)
            break;
        do
        {
        cout << "You now have the " << currentCard.rank << " of " << currentCard.suit << endl;
        cout << "Move the card to: \n";
        cout << "Piles (p)\nTableu (t)\n";

        cin >> turnInput;
        if (turnInput == "p")
        {
            //addCardToPile(baseBoard.PileSet,currentCard)
            cout << "This is where the chosen card will be added to one of the seven piles\n";
        }
        else if (turnInput == "t")
        {
            //addCardToTableu(baseBoard.Tableau,currentCard)
            cout << "This is where the chosen card will be added to the tableau\n";
        }
        else
        {
            cout << "No action found corresponding to input.";
        }
        } while (currentCard.suit != "NULL");

    
    } while (!gameOver);
    
}