#include "Game.h"

#include "GameStates.h"
#include "GameInits.h"
#include "GameActions.h"
#include "GameUtils.h"

int main()
{
	std::srand(time(NULL));
	Game app = Game(WINDOW_WIDTH, WINDOW_HEIGHT, "ALTENRUDE");
	app.runLoop();
	return 0;
}