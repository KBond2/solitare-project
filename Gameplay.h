#include "Deck.h"

//KB: Basic functions for gameplay
Card takeCardPiles(Group[], int[]);
Card takeCardWaste(Group&);
// V -- this one is up to L
Card drawCard();

void addCardToPile(Group[],Card&);
void addCardToTableu(Group&,Card&);

void addCardToPile(Group piles[],Card& currentCard)
{
    currentCard = {"NULL","NULL",-1};
}
void addCardToTableu(Group& tableau,Card& currentCard)
{
    currentCard = {"NULL","NULL",-1};
}


