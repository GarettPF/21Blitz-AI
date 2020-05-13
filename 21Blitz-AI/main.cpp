#include "Game/Game.h"

int main() {
	// Before Game
	srand((unsigned)time(NULL));
	ofstream stats("Game/stats.csv", ios_base::app);
	if (!stats.is_open()) {
		system("dir");
		cout << "File couldn't open :(" << endl;
		system("pause");
	}

	// During Game
	Game game;
	while (!game.gameOver()) {
		cout << game;
		game.choose();
		game.update();
		system("cls");
	}

	// After Game
	game.record(stats);
	cout << "Game Over" << endl;

	return 0;
}