/*********************************************
Kethry Bond, Liam Block, Steve Saelee
Final Project
Date Completed: April 20
Description: A program that runs a simulation of Solitare.
Version: 1.0
*********************************************/

#include <iostream>
#include <array>
#include <cstdlib>
#include <iomanip>
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

        //Display of board

        cout << "Current cards in stock: " << baseBoard.Stock.group.size();
        cout << "   Current cards on foundations: ";
        outputFoundationsHighCard(baseBoard.Foundation);
        cout << endl;

        //KB: Integrated Steve's vertical display code w/ small modifications.
        int maxRows = 0;
         for (int i = 0; i < 7; i++) {
             if (baseBoard.Tableau[i].group.size() > maxRows) {
                 maxRows = baseBoard.Tableau[i].group.size();
             }
         }
        // Piles labeled for faster user selection.
        cout << "\n";
        for (int i = 0; i < 7; i++) {
            cout << left << setw(18) << "   P" + to_string(i + 1) + ":";
        }
        cout << "\n";
         
        // Print each row of cards vertically
        for (int row = 0; row < maxRows; row++) {
            for (int col = 0; col < 7; col++) {
                if (row < baseBoard.Tableau[col].group.size()) {
                    if (row < concealedIndex[col]) {
                        cout << left << setw(18) << "[HIDDEN]";
                    } else {
                        Card current = baseBoard.Tableau[col].group[row];
                        string cardText = current.rank + " of " + current.suit;
                        cout << left << setw(18) << cardText;
                    }
                } else {
                    cout << left << setw(18) << " ";
                }
            }
             cout << endl;
         }
        cout << "Waste: ";
        if (baseBoard.Waste.group.size() == 0)
            cout << "[EMPTY]\n\n";
        else
            cout << baseBoard.Waste.group.back().rank << " of " << baseBoard.Waste.group.back().suit << "\n\n";

        //User turn begins
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
            }
            else if (turnInput == "m")
            {
                takeCardStack(baseBoard.Tableau, concealedIndex, currentCardStack, playerMove);
            }
            else if (turnInput == "w")
            {
                currentCard = takeCardWaste(baseBoard.Waste);
                drawnCard = 1;
            }
            else if (turnInput == "d")
            {
                currentCard = drawCard(baseBoard);
                drawnCard = 1;
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


        //KB: Place a stack of cards (Tableau only)
        while (currentCardStack.at(0).suit != "NULL")
        {
            cout << "You now have a stack starting with the " << currentCardStack.at(0).rank << " of " << currentCardStack.at(0).suit << endl;
            addCardStack(baseBoard.Tableau, concealedIndex, currentCardStack,playerMove);
        }


        //KB: Place a singular card
        while (currentCard.suit != "NULL")
        {
            cout << "You now have the " << currentCard.rank << " of " << currentCard.suit << endl;

            string turnInputMessage = "Move card to: \nTableau (t)\nFoundations (f)\n";
            if (drawnCard)
                turnInputMessage = turnInputMessage + "Waste (w)\n";
            
            //KB:Add display of board here as well?
            
            turnInput = endTurnInput(turnInputMessage);

            if (turnInput == "t")
            {
                addCardToPile(baseBoard.Tableau,concealedIndex,currentCard,playerMove);
            }
            else if (turnInput == "f")
            {
                addCardToFoundations(baseBoard.Foundation,currentCard);
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
    //KB: Reveal cards that are at the concealedIndex & lower it.
    revealHiddenCards(baseBoard.Tableau,concealedIndex);

    //KB: Win condition
    if (baseBoard.Foundation.group.size() == 52)
        gameOver = 1;

    Clear();
    } while (!gameOver);

    if (gameOver && turnInput != "END")
        cout << "Congratulations! You've won!";
}
