#include "Game.h"
#include "GameObject.h"
using namespace std;

void Game::init_board()
{
}

void Game::print_board()
{
}

bool Game::game_set(){
	if (objs.at(0)->collide(objs.at(2))) {
		return true;
	}
	return false;
}
