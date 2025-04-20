#pragma once

#include "Deck.h"
#include "inputValidation.h"
//KB: Get rank of card. Note: make function part of piles object?
int rankNum(Card);
//KB: Basic functions for gameplay

Card takeCardPiles(Group[], int[], int&);
Card takeCardWaste(Group&);
// V -- this one is up to L
Card drawCard(Board&);
void takeCardStack(Group[],int[], vector<Card>&, int&);

void addCardStack(Group[], int[], vector<Card>&, int);
void addCardToPile(Group[], int[], Card&, int);
void addCardToFoundations(Group&,Card&);
void addCardToWaste(Group&, Card&);

void revealHiddenCards(Group[],int[]);
void shuffleWaste(Board&);


//KB: Selects the top card from one of the piles
//NOTE: currently does not have multi card functionality, this will likely have to be implemented
//through a different function.

//KB: Card retrieval functions
    //KB: Take a single card from one of the tableau piles
Card takeCardPiles(Group piles[], int concealedIndex[], int& playerMove)
{

    int playerLineChoice;
    Card retrievedCard = {"NULL","NULL",-1};
    
    //KB: Input
    //cout << "choose line: ";

    playerLineChoice = specificRangeIntInput("Which line of the tableau to take a card from? \n",1,7);
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

    playerMove = playerLineChoice;
    //Returns the selected card.
    return retrievedCard;
}
    //KB: Draw a single card from the stock.
Card drawCard(Board& playBoard)
{
    Card currentCard = {"NULL","NULL",-1};
    string playerInput;

    if (playBoard.Stock.group.size() == 0)
    {
        cout << "No cards to draw.\n";
        if (playBoard.Waste.group.size() != 0)
        {
            shuffleWaste(playBoard);
            cout << "Shuffled the Waste into the Stock.\n";
            //KB NOTE: wasn't able to get the drawCard function to work properly? The card wouldn't be removed from the
            //stock so it would just draw the same card over and over. if u can get this fixed then I can just replace
            //this code here v-
            currentCard = playBoard.Stock.group.back();
            playBoard.Stock.group.pop_back();
        }
        else
        {
            cout << "No cards left that can be drawn.\n";
        }
    }
    else
    {
        currentCard = playBoard.Stock.group.back();
        playBoard.Stock.group.pop_back();
    }
    if (currentCard.suit != "NULL")
    {
    cout << "Drew the " << currentCard.rank << " of " << currentCard.suit << endl;
    }

    return currentCard;
}
    //KB: Take the card from the waste.
Card takeCardWaste(Group& waste)
{
    Card currentCard = {"NULL","NULL",-1};
    if (waste.group.size() == 0)
        cout << "Cannot take card from Waste, Waste is empty.\n";
    else
    {
        currentCard = waste.group.back();
        cout << "Took " << currentCard.rank << " of " << currentCard.suit << " from Waste.\n";
        waste.group.pop_back();
    }
    return currentCard;
}
    //KB: Takes a stack of cards from a chosen line.
void takeCardStack(Group piles[], int concealedIndex[], vector<Card>& cardPile, int& playerMove)
{
    int pileChoice;
    int pileDepthChoice;
    int i;
    //cout << "Which line of the tableu to take cards from?: \n";
    pileChoice = specificRangeIntInput("Which line of the Tableau to take cards from?\n",1,7);
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
        //cout << "Select the base of the pile to take: ";

        pileDepthChoice = specificRangeIntInput("Select the base of the pile to take: \n",1, piles[pileChoice].group.size() - concealedIndex[pileChoice]);
        
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
            if (i > concealedIndex[pileChoice] + pileDepthChoice - 1)
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
    playerMove = pileChoice;

}


//KB: Card placement Functions
    //KB: Puts the selected card onto one of the piles.
void addCardToPile(Group piles[],int concealedIndex[], Card& currentCard, int prevMove)
{
    //cout << "DEBUG: function addCardToPile() triggered\n";
    Card previousCard = {"NULL","NULL",-1};
    int playerLineChoice;
    bool validCardPlay = 0;
    string playerInput;

    //KB: Input
    if (prevMove != -1)
    {
        //cout << "Select line to move card to, or [c] to cancel move:\n";
        playerInput = lineOrCancel("Select line to move card to, or [c] to cancel move:\n");
        if (playerInput != "c")
        {
            playerLineChoice = stoi(playerInput);
        }
    }
    else
    {
        //cout << "Select line to move card to:\n";
        playerLineChoice = specificRangeIntInput("Select line to move card to:\n",1,7);
    }

    if (playerInput == "c" && prevMove != -1)
    {
        validCardPlay = 1;
        playerLineChoice = prevMove;
    }
    else
    {

    
    
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
            cout << "Not a valid move.\n";
        }
    }
    else if (piles[playerLineChoice].group.size() <= concealedIndex[playerLineChoice])
    {
        string inputMessage = "Return card to line " + to_string(playerLineChoice + 1) + "? (y/n)\n";
        playerInput = yOrN(inputMessage);
        if (playerInput == "y")
        {
            validCardPlay = 1;
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
    }

    if (validCardPlay)
    {
        piles[playerLineChoice].group.push_back(currentCard);
        cout << "Played " << currentCard.rank << " of " << currentCard.suit << " on line " << playerLineChoice+1 << endl;
        currentCard = {"NULL","NULL",-1};
    }


    
}
    //KB: Puts a stack of cards onto one of the piles
void addCardStack(Group tableau[],int concealedIndex[], vector<Card>& cardStack, int prevMove)
{
    int playerLineChoice, i, k;
    Card currentCard = cardStack.at(0);
    Card previousCard = {"NULL","NULL",-1};
    bool validMove = 0;
    string playerInput;

    //cout << "Select line to move stack to, or [c] to cancel move.:\n";
    playerInput = lineOrCancel("Select line to move stack to, or [c] to cancel move.:\n");

    if (playerInput == "c")
    {
        validMove = 1;
        playerLineChoice = prevMove;
    }
    else
    {

    
    playerLineChoice = stoi(playerInput);

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
        string inputMessage = "Return card to line " + to_string(playerLineChoice + 1) + "? (y/n)\n";
        playerInput = yOrN(inputMessage);
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
        
    }
}
    //KB: Puts the card onto the foundations
void addCardToFoundations(Group& foundations,Card& currentCard)
{
    int highestRank = 0;
    if (foundations.group.size() == 0)
    {
        if (rankNum(currentCard) == 1)
        {
            cout << "Added " << currentCard.rank << " of " << currentCard.suit << " to the foundations.\n";
            foundations.group.push_back(currentCard);
            currentCard = {"NULL","NULL",-1};
        }
        else
        {
            cout << "Cannot play the current card to the foundations.\n";
        }
    }
    else
    {
        for (int i = foundations.group.size() - 1; i >= 0; i--)
        {
            if (foundations.group.at(i).suit == currentCard.suit)
            {
                highestRank = rankNum(foundations.group.at(i));
                break;
            }
        }
        
        if (rankNum(currentCard) == highestRank + 1)
        {
            cout << "Added " << currentCard.rank << " of " << currentCard.suit << " to the foundations.\n";
            foundations.group.push_back(currentCard);
            currentCard = {"NULL","NULL",-1};
        }
        else
            cout << "Cannot play the current card to the foundations.";
    }
    
}
    //KB: Puts the card into the waste.
void addCardToWaste(Group& waste, Card& currentCard)
{
    waste.group.push_back(currentCard);
    cout << currentCard.rank << " of " << currentCard.suit << " moved to Waste.\n";
    currentCard = {"NULL", "NULL", -1};
}


//KB: Misc functions
    //KB: Get the rank of a card as an integer from 1 to 13
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
    //KB: Check to see if any of the piles are under the concealedIndex, and lowers the concealed index if they are
void revealHiddenCards(Group tableau[],int concealedIndex[])
{
    int i;
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
    //KB: Shuffle the waste into the stock.
void shuffleWaste(Board& playBoard)
{
    for (int i = playBoard.Waste.group.size() - 1; i >= 0; i--)
    {
        playBoard.Stock.group.push_back(playBoard.Waste.group.at(i));
        playBoard.Waste.group.pop_back();
    }
    //KB NOTE: Reused the code from L's deck building function for shuffling.
    for (int k = 0; k < playBoard.Stock.group.size(); k++) {
        int r = k + rand() % (playBoard.Stock.group.size() - k);
        swap(playBoard.Stock.group[k], playBoard.Stock.group[r]);
    }
}
