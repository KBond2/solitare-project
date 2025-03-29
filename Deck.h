#pragma once


#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

class Card {
    public:
        string suit;
        string rank;
        int deckLocation;

        Card(string x, string y, int num) {
            suit = x;
            rank = y;
            deckLocation = num;
        }
};


class Deck {
public:
    vector<Card> sorted;
    vector<Card> shuffled;
};

string suits[] = {
    "SPADES",
    "HEARTS",
    "CLUBS",
    "DIAMONDS"
};

string ranks[] = {
    "ACE",
    "TWO",
    "THREE",
    "FOUR",
    "FIVE",
    "SIX",
    "SEVEN",
    "EIGHT",
    "NINE",
    "TEN",
    "JACK",
    "QUEEN",
    "KING"
};

void buildDeck(Deck &deck) {
// Builds a deck object with a sorted vector containing Cards with Suit, Rank, and Location information.
    int locationTracker = 0;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            Card newCard(suits[i], ranks[j], locationTracker);

            deck.sorted.push_back(newCard);

            locationTracker++;
        }
    }
}

void shuffleDeck(Deck &deck) {
// Assigns a new, unique, deck location value for each card in the current sorted deck.
// Shuffle algoritithm taken from https://stackoverflow.com/questions/22850316/how-to-shuffle-elements-in-a-vector-randomly
    vector<Card> temp;
    vector<int> shuffledNums;
    srand(time(NULL));
    
    temp = deck.sorted;

    for (Card currentCard : temp) {
        int j = currentCard.deckLocation;
        int r = j + (rand() % (temp.size() - j));
        swap(temp[j].deckLocation, temp[r].deckLocation);
    }

    deck.shuffled = temp;
}

int cardsRemoved(Deck&);


//KB - Returns a single card from the deck (the one at the highest location), and sets that card's location at -1 
//to represent that card being 'removed' from the deck.
Card drawCard(Deck &deck)
{
    int location = deck.shuffled.size() - cardsRemoved(deck) -1;
    //cout << "DEBUG: Looking for card at location " << location << endl;
    Card cardToDraw = {"BLANK","BLANK", -1};
    bool noCardsFound = 1;
    for (Card &currentCard : deck.shuffled)
    {
        if (currentCard.deckLocation == location)
        {
            //cout << "DEBUG: The current card is " << cardToDraw.rank << " of " << cardToDraw.suit << " which is at location ";
            //cout << currentCard.deckLocation << ", which should be " << location << endl;
            cardToDraw = currentCard;
            //considering -1 as 'removed from deck'
            currentCard.deckLocation = -1;
            //if (currentCard.deckLocation == -1)
                //cout << "DEBUG: " << currentCard.rank << " of " << currentCard.suit << " removed from Deck\n";
            noCardsFound = 0;
            break;
            
        }
    }

    if (noCardsFound)
    {
        cout << "TEMP NO CARDS FOUND CONDITION, IMPLEMENT SOMETHING LATER\n";
    }

    //cout << "DEBUG: Drawing card " << cardToDraw.rank << " of " << cardToDraw.suit << endl;
    return cardToDraw;
}

//KB - Counts how many cards have been 'removed' (have a deck location of -1) from the deck
int cardsRemoved(Deck &deck)
{
    int numRemovedCards = 0;
    for (Card currentCard : deck.shuffled)
    {
        if (currentCard.deckLocation == -1)
            {
                numRemovedCards++;
            }
    }

    //cout << "DEBUG: " << numRemovedCards << " cards removed from the deck\n";
    return numRemovedCards;
}
