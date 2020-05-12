#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>
#include "Card.h"

using namespace std;

class Game {
	private:
		vector<Card *> deck;

	public:
		Game() {
			//deck = new vector<Card *>;
			shuffle();
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
};

#endif //GAME_H