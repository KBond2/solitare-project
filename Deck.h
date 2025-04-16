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

class Group {
public:
    vector<Card> group;

    Card drawCard();
};

class Deck {
public:
    Group shuffledDeck;

    void buildDeck();
};



struct Board {
    Group PileSet[7];
    Group Waste;
    Group Tableau;
    Group Stock;

    Board() = default;

    Board(Group pileArray[7], Group w, Group t, Group s) {
        for (int r = 0; r < 7; r++) {
            PileSet[r] = pileArray[r];
        }
        Waste = w;
        Tableau = t;
        Stock = s;
    }
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

void Deck::buildDeck() {
// Builds a deck object with 52 shuffled cards stored inside of it.
    //Build the sorted deck.
    int locationTracker = 0;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            Card newCard(suits[i], ranks[j], locationTracker);

            shuffledDeck.group.push_back(newCard);

            locationTracker++;
        }
    }

    //Shuffle the deck.
    // Shuffle algoritithm taken from https://stackoverflow.com/questions/22850316/how-to-shuffle-elements-in-a-vector-randomly
    srand(time(NULL));
    
    for (int k = 0; k < shuffledDeck.group.size(); k++) {
        int r = k + rand() % (shuffledDeck.group.size() - k);
        swap(shuffledDeck.group[k], shuffledDeck.group[r]);
    }
}

Card Group::drawCard() {
    return group[0];
}


Board initializeBoardState(Deck &baseDeck) {
    Group Pile1, Pile2, Pile3, Pile4, Pile5, Pile6, Pile7;
    Group SetOfPiles[7] = { Pile1, Pile2, Pile3, Pile4, Pile5, Pile6, Pile7 };
    Group Waste, Tableau, Stock;


    //Fill out the starting piles with the top 28 cards from the starting deck and remove them from
    //the deck.
    for (int j = 0; j < 7; j++) {
        for (int k = 0; k <= j; k++) {
            SetOfPiles[j].group.push_back(baseDeck.shuffledDeck.group[0]);
            baseDeck.shuffledDeck.group.erase(baseDeck.shuffledDeck.group.begin());
        }
    }

    //Take the remaining cards and put them into the stock.
    Stock = baseDeck.shuffledDeck;    

    Board Table = {SetOfPiles, Waste, Tableau, Stock};

    return Table;
}
