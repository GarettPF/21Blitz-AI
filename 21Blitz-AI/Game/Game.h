#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <time.h>
#include <vector>
#include "Card.h"

using namespace std;

class Game {
	private:
		vector<Card *> deck;
		vector<Card *> stack[4];

		Card *top;

		int points;
		int size;
		int busts;
		bool GameOver;

		void clearStack(vector<Card *> &s) {
			Card *card;
			while (s.size()) {
				card = s.back();
				s.pop_back();
				delete card;
			}
		}

		bool results(int sum, int size, bool hasAce, bool hasWild) {
			bool clear = false;
			if (hasWild) { // has a black Jack
				clear = true;
				points += 200;
			} else if (hasAce && sum+1 > 21) {
				busts += 1;
				clear = true;
			} else if (!hasAce && sum > 21) {
				busts += 1;
				clear = true;
			}
			if (size == 5) { // contains 5 cards
				clear = true;
				points += 600;
			}
			if (hasAce && (sum+1 == 21 || sum+11 == 21)) {
				clear = true;
				points += 400;
			} else if (!hasAce && sum == 21) {
				clear = true;
				points += 400;
			}
			return clear;
		}

	public:
		Game() {
			GameOver = false;
			busts = 0;
			points = 0;
			shuffle();
			top = deck.back();
			size = deck.size();
		}

		~Game() {
			while (deck.size()) {
				delete deck.back();
				deck.pop_back();
			}
		}

		void shuffle() {
			char suites[4] = { 's','c','h','d' };
			int v, s;
			bool temp_deck[4][13] = { false };
			Card *c_ptr;

			while (deck.size() != 52) {
				do {
					v = rand() % 13;
					s = rand() % 4;
				} while (temp_deck[s][v]);

				temp_deck[s][v] = true;
				c_ptr = new Card(suites[s], v+1);

				deck.push_back(c_ptr);
			}
		}

		void choose() {
			int s;

			do {
				cout << "Choose a stack (1-4): ";
				cin >> s;
			} while (s < 1 || s > 4);

			stack[s-1].push_back(top);
			deck.pop_back();
			size--;
			top = deck.back();
		}

		void update() {
			int sum = 0, val = 0;
			bool hasAce = false, hasWild = false;
			Card *card;

			for (int s=0; s < 4; s++) {
				sum = 0;
				hasAce = hasWild = false;

				for (int c=0; c < stack[s].size(); c++) {
					card = stack[s].at(c);
					val = 0;

					if (card->value() > 10)
						val = 10;
					else if (card->value() == 1)
						hasAce = true;
					else
						val = card->value();
					if (card->isWild())
						hasWild = true;

					sum += val;
				}

				if (results(sum, stack[s].size(), hasAce, hasWild))
					clearStack(stack[s]);
			}

			if (busts == 3)
				GameOver = true;
		}

		bool done() const {
			return GameOver;
		}

		friend ostream &operator<<(ostream &lhs, Game &rhs) {
			char suite, display[13] = {'A','2','3','4','5','6','7','8','9','T','J','Q','K'};
			int value;
			
			lhs << "Busts: " << rhs.busts << endl;
			lhs << "POINTS: " << rhs.points << endl;
			lhs << " S1   S2   S3   S4" << endl;

			for (int c=0; c < 5; c++) {
				for (int s=0; s < 4; s++) {
					try {
						lhs << setw(2);
						suite = rhs.stack[s].at(c)->suite();
						value = rhs.stack[s].at(c)->value();
						lhs << display[value-1];
						lhs << suite << "  ";
					} catch (out_of_range e) {
						lhs << "--   ";
					}
				}
				lhs << endl << endl;
			}

			lhs << "Current Card: " 
				<< display[rhs.top->value()-1] << rhs.top->suite()
				<< endl;
			lhs << "Cards left: " << rhs.deck.size() << endl;

			return lhs;
		}


};

#endif //GAME_H