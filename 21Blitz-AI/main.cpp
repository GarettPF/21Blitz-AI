#include "Game/Game.h"

int main() {
	srand((unsigned)time(NULL));

	Game game;

	while (!game.done()) {
		cout << game;
		game.choose();
		game.update();
		system("cls");
	}

	cout << "Game Over" << endl;
	system("pause");

	return 0;
}