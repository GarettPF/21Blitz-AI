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
};

#endif //CARD_H