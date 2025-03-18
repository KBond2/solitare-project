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
