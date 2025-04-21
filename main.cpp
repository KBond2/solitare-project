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
#include "inputValidation.h"

using namespace std;

int main()
{
    Deck baseDeck;
    Board baseBoard;
    baseDeck.buildDeck();
    baseBoard = initializeBoardState(baseDeck);

    //KB: Variables for how many cards on the main piles are currently concealed
    int concealedIndex[7] = {0,1,2,3,4,5,6};
    int index;
    int pileIndex = 0;

    //KB: Variables for gameplay
    bool gameOver = 0, drawnCard;
    string turnInput;
    Card currentCard = {"NULL","NULL",-1};
    vector<Card> currentCardStack;
    int playerMove;

    currentCardStack.push_back({"NULL", "NULL", -1});


    //KB: Gameplay loop
    do
    {
        //NOTE: Display of board goes here v
        //for (Card currentCard : baseDeck.shuffledDeck) {
        //    cout << currentCard.suit << " " << currentCard.rank << endl;
        //}
        cout << "Current cards in stock: " << baseBoard.Stock.group.size();
        cout << "   Current cards on foundations: ";
        outputFoundationsHighCard(baseBoard.Foundation);
        cout << endl;
        pileIndex = 0;
        for (Group currentPile : baseBoard.Tableau) {
            index = 0;
            for (Card currentCard : currentPile.group) {
                if (index < concealedIndex[pileIndex])
                    cout << " [HIDDEN] ";
                else
                    cout << currentCard.rank << " of " << currentCard.suit << "    ";
                index += 1;
            } 
            pileIndex += 1;
            //cout << currentPile.pile[1].suit << endl;
            cout << endl;
        }
        cout << "Waste: ";
        if (baseBoard.Waste.group.size() == 0)
            cout << "[EMPTY]\n";
        else
            cout << baseBoard.Waste.group.back().rank << " of " << baseBoard.Waste.group.back().suit << endl;


        do
        {
            playerMove = -1;
            drawnCard = 0;
            currentCard = {"NULL","NULL",-1};
            cout << "Select a move:\n";
            turnInput = beginTurnInput("Move card from tableau (t)\nMove multiple cards from tableau (m)\nMove card from waste (w)\nDraw card from stock (d)\nEnd game (END)\n");

            //KB: Choose method of getting a card.
            if (turnInput == "t")
            {
                currentCard = takeCardPiles(baseBoard.Tableau, concealedIndex, playerMove);
                //cout << "This is where taking a card from one of the main piles goes\n";
            }
            else if (turnInput == "m")
            {
                //KB: Get multiple cards from the tableu
                takeCardStack(baseBoard.Tableau, concealedIndex, currentCardStack, playerMove);
            }
            else if (turnInput == "w")
            {
                currentCard = takeCardWaste(baseBoard.Waste);
                drawnCard = 1;
                //cout << "This is where taking a card from the waste goes\n";
            }
            else if (turnInput == "d")
            {
                //    V -- fill in with function of choice -KB
                currentCard = drawCard(baseBoard);
                drawnCard = 1;
                //cout << "This is where the card drawing function goes\n";
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
        //KB: If the user has no cards selected, repeats the first section of code.
        } while (currentCard.suit == "NULL" && currentCardStack.at(0).suit == "NULL");


        if (gameOver)
            break;


        //KB: Place a stack of cards (Tableu only)
        while (currentCardStack.at(0).suit != "NULL")
        {
            cout << "You now have a stack starting with the " << currentCardStack.at(0).rank << " of " << currentCardStack.at(0).suit << endl;
            addCardStack(baseBoard.Tableau, concealedIndex, currentCardStack,playerMove);
        }


        //KB: Place singular card
        while (currentCard.suit != "NULL")
        {
        
        cout << "You now have the " << currentCard.rank << " of " << currentCard.suit << endl;
        //cout << "Move the card to: \n";
        //cout << "Tableu (t)\nFoundations (f)\n";
        //if (drawnCard)
        //cout << "Waste(w)\n";

        string turnInputMessage = "Move card to: \nTableau (t)\nFoundations (f)\n";
        if (drawnCard)
            turnInputMessage = turnInputMessage + "Waste (w)\n";
        //KB:Add display of board here as well?
        
        turnInput = endTurnInput(turnInputMessage);

        if (turnInput == "t")
        {
            addCardToPile(baseBoard.Tableau,concealedIndex,currentCard,playerMove);
            //cout << "This is where the chosen card will be added to one of the seven piles\n";
        }
        else if (turnInput == "f")
        {
            addCardToFoundations(baseBoard.Foundation,currentCard);
            //cout << "This is where the chosen card will be added to the tableau\n";
        }
        else if (turnInput == "w" && drawnCard)
        {
            addCardToWaste(baseBoard.Waste,currentCard);
        }
        else
        {
            cout << "No action found corresponding to input.";
        }
        }

    revealHiddenCards(baseBoard.Tableau,concealedIndex);

        if (baseBoard.Foundation.group.size() == 52)
        {
            cout << "You've completed the game of solitare! Congratulations!\n\n";
            gameOver = 1;
        }
    Clear();
    } while (!gameOver);
    

    if (gameOver && turnInput != "END")
        cout << "Congratulations! You've won!";
}
