#include <iostream>
#include <array>
#include <cstdlib>
#include <iomanip>
#include "DeckE.h"
#include "GameplayE.h"

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
    bool gameOver = 0;
    string turnInput;
    Card currentCard = {"NULL","NULL",-1};




    //KB: Gameplay loop
    do
    {
        cout << "l";

        int maxRows = 0;
        for (int i = 0; i < 7; i++) {
            if (baseBoard.PileSet[i].group.size() > maxRows) {
                maxRows = baseBoard.PileSet[i].group.size();
            }
        }
        
        // Piles labeled for faster user selection.
        cout << "\n   P1:" << setw(18) << "P2:" << setw(18) << "P3:" << setw(18) << "P4:" << setw(18) << "P5:"
        << setw(18) << "P6:" << setw(18) << "P7:";
        cout << "\n";
        
        // Print each row of cards vertically
        for (int row = 0; row < maxRows; row++) {
            for (int col = 0; col < 7; col++) {
                if (row < baseBoard.PileSet[col].group.size()) {
                    if (row < concealedIndex[col]) {
                        cout << left << setw(18) << "[HIDDEN]";
                    } else {
                        Card current = baseBoard.PileSet[col].group[row];
                        string cardText = current.rank + " of " + current.suit[0];
                        cout << left << setw(18) << cardText;
                    }
                } else {
                    cout << left << setw(18) << " ";
                }
            }
            cout << endl;
        }


        do
        {
            currentCard = {"NULL","NULL",-1};
            cout << "\t\t\t\t\t\tSelect a move:\n";
            cout << "[p] Move card from piles \t [w] Move card from waste (w)\t [d] Draw card from stock \t [END] End game\n";
            //KB: TEMP, ADD INPUT VALIDATION LATER
            cin >> turnInput;

            //KB: Choose method of getting a card.
            if (turnInput == "p")
            {
                currentCard = takeCardPiles(baseBoard.PileSet, concealedIndex);
                //cout << "This is where taking a card from one of the main piles goes\n";
            }
            else if (turnInput == "w")
            {
                //currentCard = takeCardWaste(baseBoard.Waste);
                cout << "This is where taking a card from the waste goes\n";
            }
            else if (turnInput == "d")
            {
                //    V -- fill in with function of choice -KB
                //currentCard = drawCard();
                cout << "This is where the card drawing function goes\n";
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

        } while (currentCard.suit == "NULL");

        if (gameOver)
            break;
        do
        {
        cout << "You now have the " << currentCard.rank << " of " << currentCard.suit << endl;
        cout << "Move the card to: \n";
        cout << "Piles (p)\nTableu (t)\n";

        //KB:Add display of board here as well?
        
        cin >> turnInput;
        if (turnInput == "p")
        {
            addCardToPile(baseBoard.PileSet,currentCard);
            //cout << "This is where the chosen card will be added to one of the seven piles\n";
        }
        else if (turnInput == "t")
        {
            //addCardToTableu(baseBoard.Tableau,currentCard);
            cout << "This is where the chosen card will be added to the tableau\n";
        }
        else
        {
            cout << "No action found corresponding to input.";
        }
        } while (currentCard.suit != "NULL");

    
    } while (!gameOver);
    
}