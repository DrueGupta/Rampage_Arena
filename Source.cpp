#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include "Player.h"
#include "Cthulhu.h"

Player* selectCharacter()
{
	int choice = 0;
	string name, temp;
	cout << "Enter name: ";
	getline(cin, name);
	cout << "Choose your character...\n"
		<< "1. Cthulhu\n"
		<< "Enter choice: ";
	getline(cin, temp);
	choice = stoi(temp);
	if (choice == 1) {
		return new Cthulhu(name);
	}
	else
	{
		return nullptr;
	}
}

int main() {
    srand(time(NULL));

    Player* playerOne = selectCharacter();
    Player* playerTwo = selectCharacter();
    Player* currentPlayer, * targetPlayer, * temp;

    int p1Iniative = rand() % 100;
    int p2Iniative = rand() % 100;
    if (p1Iniative >= p2Iniative) {
        currentPlayer = playerTwo;
        targetPlayer = playerOne;
    }
    else {
        currentPlayer = playerOne;
        targetPlayer = playerTwo;
    }

    bool endGame = false;
    int choice = 0;
    string s = "";
    bool loseTurn = false;
    bool valid = true;

    while (!endGame) {
        temp = currentPlayer;
        currentPlayer = targetPlayer;
        targetPlayer = temp;

        endGame = currentPlayer->processEffects(loseTurn);
        if (loseTurn || endGame) {
            loseTurn = false;
            continue;
        }
        do
        {
            cout << "========================================================================\n"
                << currentPlayer->getName() << "'s Turn\n"
                << "========================================================================\n";
            currentPlayer->displayStatus();
            targetPlayer->displayStatus();
            cout << "========================================================================\n"
                << "1. Attack\n"
                << "2. " << currentPlayer->getSpecialOneName() << " ("
                << currentPlayer->getSpecialOneCost() << " " << currentPlayer->getResourceName()
                << ")\n"
                << "3. " << currentPlayer->getSpecialTwoName() << " ("
                << currentPlayer->getSpecialTwoCost() << " " << currentPlayer->getResourceName()
                << ")\n"
                << "========================================================================\n"
                << "Enter Choice: ";
            getline(cin, s);
            try
            {
                valid = true;
                choice = stoi(s);
            }
            catch(std::invalid_argument)
            {
                valid = true;
                cout << "Invalid input. Please put a valid input." << endl;
            }
        } while (!valid);

        switch (choice) {
        case 1:
            endGame = currentPlayer->attack(targetPlayer);
            break;
        case 2:
            endGame = currentPlayer->specialOne(targetPlayer);
            break;
        case 3:
            endGame = currentPlayer->specialTwo(targetPlayer);
            break;
        default:
            cout << "Play stupid games, win stupid prizes. You have lost your turn.\n\n";
        }

    }
    if (playerOne->getHealth() <= 0)
        playerOne->die();
    if (playerTwo->getHealth() <= 0)
        playerTwo->die();
    return 0;
}
