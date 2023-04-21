#include <iostream>
#include <cstdlib> 
#include <ctime> 
#include <fstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <cstring>
char* strcpy(char* to, const char* from);

#define maxpS 10

using namespace std;

// class representing the dice
class Dice {
private:
	int SidesofDie;
	void generator() {
		srand((unsigned)time(0));
	}
public:
	// Roll of dice with dice between 1 and n
	int roll() {
		return (rand() % SidesofDie) + 1;
	}
	Dice(int nS) {
		SidesofDie = nS;
		generator();
	}
};


class Player {
private:
	string name;
	int score;
public:
	// Player name and score wiht constructors
	Player(string a, int b) {
		name = a;
		score = b;
	}
	//return the name
	string getName() {
		return name;
	}
	//return score
	int getScore() {
		return score;
	}
	// Increase score by indicated value
	void addToScore(int val) {
		score += val;
	}
};


class DiceGame {

public:
	Player* players[maxpS];
	Dice* dice;
	int AmountPlayers, DiceAmount;
		
	virtual void play() = 0;

	DiceGame(Dice dice, int AmountPlayers, int DiceAmount)
	{
		this->dice = &dice;
		this->AmountPlayers = AmountPlayers;
		this->DiceAmount = DiceAmount;

	}

	void initPlayers() {
		string name;
		int score;
		for (int i = 0; i < AmountPlayers; i++) {
			//Inputs for player name and player score.
			cout << "Player Name: ";
			cin >> name;
			cout << "Player Score: ";
			cin >> score;

			players[i] = new Player(name, score);
		}
	}
	// Name and score displaying
	void displayScores() {
		for (int i = 0; i < AmountPlayers; i++) {
			cout << players[i]->getName() << ":" << players[i]->getScore() << endl;
		}
	}

	// Task 6 code
	void writeScoresToFile() {
		ofstream myfile("Game.txt");
		if (myfile.is_open()) {
			for (int i = 0; i < AmountPlayers; i++) {
				myfile << "Player's name: " << players[i]->getName() << ":"
					<< "Player's score: " << players[i]->getScore() << endl;
			}
			myfile.close();
		}
		else {
			cout << "Unable to open file";
		}
		return;
	}

	//Task 7 code
	void getHighestScore() {
		string line;
		ifstream myfile("Game.txt");
		if (myfile.is_open()) {
			string maxp;
			int max_s = 0;
			while (getline(myfile, line)) {
				string deli = ":";
				int sequence_counter = 0;
				int currentscore;
				string currentplayer;
				int start = 0;
				int end = line.find(deli);
				while (end != -1) {
					if (sequence_counter == 1)
					{
						currentplayer = line.substr(start, end - start);
					}
					start = end + deli.size();
					end = line.find(deli, start);
					sequence_counter++;
				}
				string str_currentscore = line.substr(start, end - start);
				int  n = str_currentscore.length();
				char char_array[]{ n + 1 };
				strcpy(char_array, str_currentscore.c_str());
				currentscore = atoi(char_array);

				if (currentscore > max_s)
				{
					max_s = currentscore;
					maxp = currentplayer;
				}
			}
			myfile.close();
			cout << "Player with Highest Score = " << maxp << endl;
			cout << "Highest Score = " << max_s << endl;

		}
		else {
			cout << "Unable to open file";
		}
		return;
	}

};

//Task 4 code
class KnockOut : public DiceGame {
public:
	KnockOut(Dice dice, int AmountPlayer, int DiceAmount) : DiceGame(dice, AmountPlayers, DiceAmount) {};
	void play() {
		initPlayers();
		cout << "Play start";

		int dice_roll, winner = -1, KO = 0;
		// this is an array of players where each players has value of 0 as a start
		int player_eliminated_check[maxpS] = { 0 };
		int current_no_of_players = AmountPlayers;
		KO = 0;
		for (int i = 0; i < DiceAmount; i++) {
			KO += dice->roll();
		}

		
		while (current_no_of_players > 1) {
			for (int i = 0; i < AmountPlayers; i++) {

				// for if the players are still in the game.
				if (player_eliminated_check[i] == 0) {
					int pscore = 0;
					for (int j = 0; j < DiceAmount; j++) {
						int dice_roll = dice->roll();
						// calculation for Adding up player score thru dice throwing.
						for (int k = 0; k < DiceAmount; k++) {
							pscore += dice_roll;
						}
					}
					// Elimination code.
					if (pscore == KO) {
						current_no_of_players -= 1;
						
						player_eliminated_check[i] = 1;
					}
					// if there is only one player remaining
					if (current_no_of_players == 1) {
						winner = i;
					}
				}
			}


		}
		// add points to winner
		players[winner]->addToScore(10);
	}
};

//Task 5 code:
class Boston : public DiceGame {
public:
	Boston(Dice dice, int num_p, int num_dice) : DiceGame(dice, AmountPlayers, DiceAmount) {};
	void play() {
		initPlayers();
		
		int maxp = -1;
		int max_pscore = 0;
		for (int i = 0; i < AmountPlayers; i++) {
			int cur_pscore = 0;
			for (int j = 0; j < DiceAmount; j++) {
				int max_roll = 0;
				int cur_roll;
				for (int k = 0; k < (DiceAmount - j); k++) {
					cur_roll = dice->roll();
					if (cur_roll > max_roll) {
						max_roll = cur_roll;
					}
				}
				cout << "Maximum roll: " << max_roll << endl;
				cur_pscore += max_roll;
			}
			
			if (cur_pscore > max_pscore) {
				max_pscore = cur_pscore;
				maxp = i;//Winner is announced!
			}
			cout << "The winner is: " << maxp << endl;
		}
	}

};


int main() {
	DiceGame* game;

	// Obtains players, number of Dices, and number of sides.
	int AmountPlayers, DiceAmount, SidesofDie;
	cout << "Players: ";
	cin >> AmountPlayers;
	cout << "Sides of Dice: ";
	cin >> SidesofDie;
	cout << "Dice Amount: ";
	cin >> DiceAmount;

	int choice;
	cout << "enter your choce : 1 for knockout game, 2 for boston game";
	cin >> choice;

	Dice dice(SidesofDie);

	//Calling the KnockOut class.
	if (choice == 1) {
		KnockOut objt(dice, AmountPlayers, DiceAmount);
		game = &objt;
	}
	else {
		Boston objt(dice, AmountPlayers, DiceAmount);
		game = &objt;
	}

	game->play();
	game->displayScores();
	game->getHighestScore();

}