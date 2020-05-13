#ifndef CARD_H
#define CARD_H

class Card {
	private:
		char Suite;
		int Value;
	
	public:
		Card(char s, int v) {
			Suite = s;
			Value = v;
		}

		char suite() const {
			return Suite;
		}

		int value() const {
			return Value;
		}

		bool isWild() const {
			bool isBlack = (Suite == 's' || Suite == 'c'),
				isJack = (Value == 11);
			return (isJack && isBlack);
		}
};

#endif //CARD_H