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

	public:
		Game() {
			shuffle();
			top = deck.back();
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

		friend ostream &operator<<(ostream &lhs, Game &rhs) {
			char c;
			int v;
			
			lhs << "S1   S2   S3   S4" << endl;

			for (int c=0; c < 5; c++) {
				for (int s=0; s < 4; s++) {
					try {
						c = rhs.stack[s].at(c)->suite();
						v = rhs.stack[s].at(c)->value();
						lhs << setw(5) << v << c;
					} catch (out_of_range e) {
						lhs << "     ";
					}
				}
				lhs << endl << endl;
			}

			lhs << "Current Card: " 
				<< rhs.top->value() << rhs.top->suite()
				<< endl;

			return lhs;
		}

};

#endif //GAME_H