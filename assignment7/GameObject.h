#pragma once
#include<iostream>

class GameObject{
protected:
	int distance;
	int x, y;
	int dx[4] = { -1, 0, 1, 0 };
	int dy[4] = { 0, 1, 0, -1 };
public:
	GameObject() = default;
	GameObject(int x, int y, int d) {}

	virtual ~GameObject() {};
	virtual void move() = 0;
	virtual char get_shape() = 0;

	int get_x() const { return x; }
	int get_y() const { return y; }

	bool collide(GameObject* p);
};

class Human : public GameObject{
private:
	char shape = 'H';
	char cmd;
public:
	Human(int x, int y, int d = 1) {}

	char get_shape() override;

	void move(char cmd);
};

class Monster : public GameObject {
private:
	char shape = 'M';
public:
	Monster(int x, int y, int d = 2) {}

	char get_shape() override;

	void move() override;
};

class Food : public GameObject {
private:
	char shape = '@';
public:
	Food(int x, int y, int d = 1) {}

	char get_shape() override {};

	void move() override {};
};