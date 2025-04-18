#include "Deck.h"
//KB: Get rank of card. Note: make function part of piles object?
int rankNum(Card);
//KB: Basic functions for gameplay
Card takeCardPiles(Group[], int[]);

Card takeCardWaste(Group&);
// V -- this one is up to L
Card drawCard();
void takeCardStack(Group[],int[], vector<Card>&);

void addCardStack(Group[], int[], vector<Card>&);
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


//KB: Takes a stack of cards from a chosen line.
void takeCardStack(Group piles[], int concealedIndex[], vector<Card>& cardPile)
{
    int pileChoice;
    int pileDepthChoice;
    int i;
    cout << "Which line of the tableu to take cards from: ";
    //KB: NOTE: ADD INPUT VALIDATION LATER
    cin >> pileChoice;
    pileChoice -= 1;
    if (piles[pileChoice].group.size() - concealedIndex[pileChoice] <= 1)
    {
        cout << "Too few cards.\n";
    }
    else
    {
        cout << "Line " << pileChoice + 1 << " has the cards ";
        i = concealedIndex[pileChoice];
        for (i; i < piles[pileChoice].group.size(); i++)
        {
            if (i != piles[pileChoice].group.size() - 1)
            {
                cout << piles[pileChoice].group.at(i).rank << " of " << piles[pileChoice].group.at(i).suit;
                cout << "(" << i - concealedIndex[pileChoice] + 1 << "), ";
            }
            else
            {
                cout << "and " << piles[pileChoice].group.at(i).rank << " of " << piles[pileChoice].group.at(i).suit << endl;
            }
        }
        cout << "Select the base of the pile to take: ";
        //KB: NOTE: ADD INPUT VALIDATION (value must be non-negative int between 1 and 1 below the amount of cards in the pile)
        //do not want user using this for single card ideally? unless i go and restructure the. entire code ig.
        cin >> pileDepthChoice;
        
        //i = pileDepthChoice + concealedIndex[pileChoice] - 1 ;
        //cout << "DEBUG: i value = " << i << endl;
        //cout << "DEBUG: size of pile = " << piles[pileChoice].group.size() << endl;

        //KB: i don't know why this function didn't work but the other one did.
        /*for (i; i < piles[pileChoice].group.size(); i++);
        {
            cardPile.push_back(piles[pileChoice].group.at(i));
            cout << "DEBUG: Adding " << piles[pileChoice].group.at(i).rank << " of " << piles[pileChoice].group.at(i).suit;
            cout << "to current stack.\n";
        }
        */
        i = 0;
        for (Card cardToAdd : piles[pileChoice].group)
        {
            i++;
            if (i > concealedIndex[pileChoice])
            {
                cardPile.push_back(cardToAdd);
                //cout << "DEBUG: Adding " << cardToAdd.rank << " of " << cardToAdd.suit << " to current stack.\n";
            }
            
        }
        cardPile.erase(cardPile.begin());
        for (Card card : cardPile)
        {
            piles[pileChoice].group.pop_back();
        }
        
    }
}

//KB: Puts the selected card onto one of the piles.
void addCardToPile(Group piles[],Card& currentCard)
{
    //cout << "DEBUG: function addCardToPile() triggered\n";
    Card previousCard = {"NULL","NULL",-1};
    int playerLineChoice;
    bool validCardPlay = 0;

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
            validCardPlay = 1;
        }
        else
        {
            cout << "Card cannot be played on line " << playerLineChoice+1 << endl;
            
        }
    }
    else
    {
        previousCard = piles[playerLineChoice].group.back();

        if (rankNum(currentCard) == rankNum(previousCard) - 1)
        {
            if (currentCard.suit == suits[1] || currentCard.suit == suits[3])
            {
                if (previousCard.suit == suits[0] || previousCard.suit == suits[2]) 
                {
                    validCardPlay = 1;
                }
                else
                {
                    cout << "Not a valid move.\n";
                }
            }
            else if (currentCard.suit == suits[0] || currentCard.suit == suits[2])
            {
                if (previousCard.suit == suits[1] || previousCard.suit == suits[3]) 
                {
                    validCardPlay = 1;
                }
                else
                {
                    cout << "Not a valid move.\n";
                }
            }

        }
    }

    if (validCardPlay)
    {
        piles[playerLineChoice].group.push_back(currentCard);
        cout << "Played " << currentCard.rank << " of " << currentCard.suit << " on line " << playerLineChoice+1 << endl;
        currentCard = {"NULL","NULL",-1};
    }


    
}

void addCardStack(Group tableau[],int concealedIndex[], vector<Card>& cardStack)
{
    int playerLineChoice, i, k;
    Card currentCard = cardStack.at(0);
    Card previousCard = {"NULL","NULL",-1};
    bool validMove = 0;
    string playerInput;

    //KB: ADD INPUT VALIDATION LATER
    cout << "Select line to move stack to:\n";
    cin >> playerLineChoice;
    playerLineChoice -= 1;

    if (tableau[playerLineChoice].group.size() == 0)
    {
        if (rankNum(currentCard) == 13)
        {
            validMove = 1;
        }
        else
        {
            cout << "Not a valid move.\n";
        }
    }
    else if (tableau[playerLineChoice].group.size() <= concealedIndex[playerLineChoice])
    {
        cout << "Cancel move? (y/n)\n";
        cin >> playerInput;
        if (playerInput == "y")
        {
            validMove = 1;
        }
    }
    else
    {
        previousCard = tableau[playerLineChoice].group.back();

        if (rankNum(currentCard) == rankNum(previousCard) - 1)
        {
            if (currentCard.suit == suits[1] || currentCard.suit == suits[3])
            {
                if (previousCard.suit == suits[0] || previousCard.suit == suits[2]) 
                {
                    validMove = 1;
                }
                else
                {
                    cout << "Not a valid move.\n";
                }
            }
            else if (currentCard.suit == suits[0] || currentCard.suit == suits[2])
            {
                if (previousCard.suit == suits[1] || previousCard.suit == suits[3]) 
                {
                    validMove = 1;
                }
                else
                {
                    cout << "Not a valid move.\n";
                }
            }

        }
    }

    if (validMove)
    {
        k = cardStack.size();
        for (i = 0; i < k; i++)
        {
            tableau[playerLineChoice].group.push_back(cardStack.front());
            cardStack.erase(cardStack.begin());
        }
        cardStack.push_back({"NULL", "NULL", -1});
        for (i = 0; i < 7; i++)
        {
            //cout << "DEBUG: tableau line " << i << " group size: " << tableau[i].group.size() << endl;
            //cout << "DEBUG: concealiedIndex[" << i << "]: " << concealedIndex[i] << endl;
            if (tableau[i].group.size() <= concealedIndex[i] && tableau[i].group.size() != 0)
            {
                cout << "Revealed the " << tableau[i].group.at(concealedIndex[i]-1).rank << " of " << tableau[i].group.at(concealedIndex[i]-1).suit;
                cout << " on line " << i + 1 << endl;
                concealedIndex[i] -= 1;
                break;
            }
            
        }
    }
}


void addCardToFoundations(Group& tableau,Card& currentCard)
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

