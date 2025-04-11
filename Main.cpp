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

using namespace std;

int main()
{
    Deck baseDeck;
    Board baseBoard;
    baseDeck.buildDeck();
    baseBoard = initializeBoardState(baseDeck);

    //for (Card currentCard : baseDeck.shuffledDeck) {
    //    cout << currentCard.suit << " " << currentCard.rank << endl;
    //}

    for (Group currentPile : baseBoard.PileSet) {
        for (Card currentCard : currentPile.group) {
            cout << currentCard.rank << " of " << currentCard.suit << "    ";
        }
    //    cout << currentPile.pile[1].suit << endl;
        cout << endl;
    }
}