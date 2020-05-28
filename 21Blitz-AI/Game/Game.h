#ifndef GAME_H
#define GAME_H

#include "../Header.h"
#include "Card.h"

using namespace std;

class Game {
	private:
		// private variables
		struct GameState {
			vector<Card *> deck;
			vector<Card *> stack[4];
			Card *top;
			int points;
			int deckSize;
			int busts;
		};
		GameState mem;
		GameState cur;

		vector<Card *> cards; // container for all cards
		bool GameOver;
		time_t startTime, currentTime;

		// private functions
		void clearStack(vector<Card *> &s) {
			Card *card;
			while (s.size()) {
				card = s.back();
				s.pop_back();
			}
		}
		
		bool results(int sum, int size, bool hasAce, bool hasWild) {
			bool clear = false;

			if (hasWild) {
				cur.points += 200;
				clear = true;
				if (size == 5)
					cur.points += 600;
			} else if ((hasAce && sum+1 > 21) ||
				(sum > 21)) {
				cur.busts += 1;
				clear = true;
			}

			if ((hasAce && sum+1 == 21) ||
				(hasAce && sum+11 == 21) ||
				(sum == 21)) {
				cur.points += 400;
				clear = true;
				if (size == 5)
					cur.points += 600;
			}

			if (!clear && size == 5) {
				cur.points += 600;
				clear = true;
			}

			return clear;
		}

		void shuffle() {
			char suites[4] = { 's','c','h','d' };
			int v, s;
			bool temp_deck[4][13] = { false };
			Card *c_ptr;

			while (cur.deck.size() != 52) {
				do {
					v = rand() % 13;
					s = rand() % 4;
				} while (temp_deck[s][v]);

				temp_deck[s][v] = true;
				c_ptr = new Card(suites[s], v+1);

				cur.deck.push_back(c_ptr);
				cards.push_back(c_ptr);
			}
		}


	public:
		Game() {
			GameOver = false;
			cur.points = 0;
			cur.busts = 0;
			shuffle();
			cur.deckSize = cur.deck.size();
			cur.top = cur.deck.back();
			mem = cur;
			time(&startTime);
		}
		~Game() {
			Card *card;
			
			while (!cards.empty()) {
				card = cards.back();
				cards.pop_back();
				delete card;
			}
		}

		void choose() {
			int s;

			do {
				cout << "Choose a stack (1-4, 0 for undo): ";
				cin >> s;
			} while (s < 0 || s > 4);

			if (s == 0) {
				cur = mem;
			} else {
				// save gamestate before changes
				mem = cur;

				// next gamestate
				cur.stack[s-1].push_back(cur.top);
				cur.deck.pop_back();
				cur.deckSize--;
				cur.top = cur.deck.back();
			}
		}

		void update() {
			int sum = 0, val = 0;
			bool hasAce = false, hasWild = false;
			Card *card;

			for (int s=0; s < 4; s++) {
				sum = 0;
				hasAce = hasWild = false;

				for (int c=0; c < cur.stack[s].size(); c++) {
					card = cur.stack[s].at(c);
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

				if (results(sum, cur.stack[s].size(), hasAce, hasWild))
					clearStack(cur.stack[s]);
			}

			time(&currentTime);

			if (cur.busts == 3 || currentTime - startTime >= 3*60)
				GameOver = true;
		}

		bool gameOver() const {
			return GameOver;
		}

		void record(ofstream &outfile) const {
			time_t len = currentTime - startTime;

			int min = len / 60;
			int sec = len % 60;

			outfile << cur.points << ", "
				<< min<<":";
			if (sec < 10) outfile << "0";
			outfile << sec << ", "
				<< cur.busts << ", "
				<< cur.deckSize << endl;
		}

		friend ostream &operator<<(ostream &lhs, Game &rhs) {
			char suite, display[13] = {'A','2','3','4','5','6','7','8','9','T','J','Q','K'};
			int value;
			
			lhs << "Busts: " << rhs.cur.busts << endl;
			lhs << "POINTS: " << rhs.cur.points << endl;
			lhs << "S1   S2   S3   S4" << endl;

			for (int c=0; c < 5; c++) {
				for (int s=0; s < 4; s++) {
					try {
						lhs << setw(2);
						suite = rhs.cur.stack[s].at(c)->suite();
						value = rhs.cur.stack[s].at(c)->value();
						lhs << display[value-1];
						lhs << suite << "  ";
					} catch (out_of_range e) {
						lhs << "--   ";
					}
				}
				lhs << endl << endl;
			}

			lhs << "Current Card: " 
				<< display[rhs.cur.top->value()-1] << rhs.cur.top->suite()
				<< endl;
			lhs << "Cards left: " << rhs.cur.deckSize << endl;

			return lhs;
		}
};

#endif //GAME_H