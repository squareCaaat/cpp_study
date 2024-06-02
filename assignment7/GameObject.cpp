#include "GameObject.h"
using namespace std;

//GameObject
GameObject::GameObject(int x, int y, int d) : x(x), y(y), distance(d) {}

bool GameObject::collide(GameObject* p) {
	if (this->x == p->get_x() && this->y == p->get_y())
		return true;
	else
		return false;
}

// Human
Human::Human(int x, int y, int d = 1) : GameObject(x, y, d) {}

void Human::move(char cmd) {
	if (cmd == 'a' && this->x > 0 && this->x <= 20) {
		this->x -= this->distance;
	}
	else if (cmd == 'w' && this->y >= 0 && this->y < 20) {
		this->y += this->distance;
	}
	else if (cmd == 'd' && this->x >= 0 && this->x < 20) {
		this->x += this->distance;
	}
	else if (cmd == 's' && this->y > 0 && this->y <= 20) {
		this->y -= this->distance;
	}
	else
		return;
}

char Human::get_shape() { return shape; }

//Monster
Monster::Monster(int x, int y, int d = 2) : GameObject(x, y, d) {}

void Monster::move() {
	return;
}

char Monster::get_shape() { return shape; }

//Food
Food::Food(int x, int y, int d = 1) : GameObject(x, y, d) {}
void Food::move(){

}

char Food::get_shape() { return shape; }
