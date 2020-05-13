#include "Game/Game.h"

int main() {
	srand((unsigned)time(NULL));

	Game game;

	while (true) {
		cout << game;
		game.choose();
		game.update();
		system("cls");
	}

	return 0;
}