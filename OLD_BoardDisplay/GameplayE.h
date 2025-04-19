#include "DeckE.h"
//KB: Get rank of card. Note: make function part of piles object?
int rankNum(Card);
//KB: Basic functions for gameplay
Card takeCardPiles(Group[], int[]);

Card takeCardWaste(Group&);
// V -- this one is up to L
Card drawCard();

void addCardToPile(Group[],Card&);
void addCardToTableu(Group&,Card&);

//KB: Selects the top card from one of the piles
//NOTE: currently does not have multi card functionality, this will likely have to be implemented
//through a different function.

Card takeCardPiles(Group piles[], int concealedIndex[])
{

    int playerLineChoice;
    Card retrievedCard = {"NULL","NULL",-1};
    
    //KB: Input
    cout << "choose line: ";
    //TEMP, ADD INPUT VALIDATION LATER 
    cin >> playerLineChoice;
    playerLineChoice -= 1;

    //KB: Makes sure the pile being chosen has cards
    if (piles[playerLineChoice].group.size() == 0)
    {
        cout << "No cards found in line " << playerLineChoice+1;
    }
    else
    {
        //KB: Takes the last card in the pile & sets it as the card to be returned, & removes it from the pile
        retrievedCard = piles[playerLineChoice].group.back();
        piles[playerLineChoice].group.pop_back();
        cout << "Taking the " << retrievedCard.rank << " of " << retrievedCard.suit << " from line " << playerLineChoice+1 << endl; 
    }
    //KB: Reveals the card underneath the selected card if it is hidden.
    if (piles[playerLineChoice].group.size() == concealedIndex[playerLineChoice] && concealedIndex[playerLineChoice] != 0)
    {
        concealedIndex[playerLineChoice] -= 1;
        cout << "Revealed the " << piles[playerLineChoice].group.at(concealedIndex[playerLineChoice]).rank << " of ";
        cout << piles[playerLineChoice].group.at(concealedIndex[playerLineChoice]).suit << endl;
    }

    //Returns the selected card.
    return retrievedCard;
}

//KB: Puts the selected card onto one of the piles.
void addCardToPile(Group piles[],Card& currentCard)
{
    Card previousCard = {"NULL","NULL",-1};
    int playerLineChoice;

    //KB: Input
    cout << "choose line: ";
    //TEMP, ADD INPUT VALIDATION LATER 
    cin >> playerLineChoice;
    playerLineChoice -= 1;

    //KB: If the pile has no cards, the only card that can be placed there is a king.
    if (piles[playerLineChoice].group.size() == 0)
    {
        if (rankNum(currentCard) == 13)
        {
            piles[playerLineChoice].group.push_back(currentCard);
            cout << "Played " << currentCard.rank << " of " << currentCard.suit << " on line " << playerLineChoice+1 << endl;
            currentCard = {"NULL","NULL",-1};
        }
        else
        {
            cout << "Card cannot be played on line " << playerLineChoice+1 << endl;
            
        }
    }
    else
    {
        //KB: Gets the card currently on top of the pile for comparison.
        previousCard = piles[playerLineChoice].group.back();

        //KB: Suits[1] & suits[3] represent hearts & diamonds, suits[0] and suits[2] represent spades and clubs.
        //Using this so that the suits of the cards can be changed & not mess up the whole code as much.
        //Comparing suits (current card must be a different color than the previous card):
        if (previousCard.suit == suits[1] || previousCard.suit == suits[3])
        {
            if (currentCard.suit == suits[1] || currentCard.suit == suits[3])
            {
                cout << "Card cannot be played on line " << playerLineChoice+1 << endl;
            }
        }
        else if (currentCard.suit == suits[0] || currentCard.suit == suits[2])
        {
            cout << "Card cannot be played on line " << playerLineChoice+1 << endl;
        }

        //KB: Comparing ranks (current card must be one rank lower than the previous one)
        else if (rankNum(currentCard) != rankNum(previousCard) - 1)
        {
            cout << "Card cannot be played on line " << playerLineChoice+1 << endl;
        }
        //KB: If the card is a different color & one rank lower, add it to the line, and clear out the players
        //chosen card for the next turn.
        else
        {
            piles[playerLineChoice].group.push_back(currentCard);
            cout << "Played " << currentCard.rank << " of " << currentCard.suit << " on line " << playerLineChoice+1 << endl;
            currentCard = {"NULL","NULL",-1};
        }
    }


    
}
void addCardToTableu(Group& tableau,Card& currentCard)
{
    currentCard = {"NULL","NULL",-1};
}

int rankNum(Card rankCheck)
{
    int rank;
    for (rank = 1; rank <= 13; rank++)
    {
        if (rankCheck.rank == ranks[rank - 1])
            break;
    }
    return rank;
}

