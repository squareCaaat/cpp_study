#pragma once
#include<iostream>
#include<vector>

class GameObject;

class Game{
private:
	vector<GameObject*> objs; // {Human, Monster, Food}
public:
	Game(GameObject* human, GameObject* monster, GameObject* food) {}
	
	void init_board();

	void print_board();

	bool game_set();
};

