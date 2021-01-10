#pragma once
#include "DoublyLinkedList.h"
#include "Shape.h"
#include <random>


class Food
{
public:
	Food(SDL_Renderer* renderer, Point2D mapSize, int scale=1);

	void replace();
	void render(int r=255, int g=255, int b=255);
	Point2D pos;
protected:
	int size;
	Point2D mapSize;
	SDL_Renderer* renderer;
};

class Snake
{
public:
	Snake(SDL_Renderer* renderer, Food* food, Point2D boundary,int size,Point2D startPos=Point2D(), int startLenght= 3);

	//0:up, 1:down, 2:left, 3:right
	void setDirection(int dir);
	void move();
	void grow(int amount = 1);
	void color(int r, int g, int b);
	void setOpponent(Snake* other);
	void setPlayer(int playerNo);
	int getPlayer();
	void die();
	bool alive;
protected:
	void printScore();
	int size;
	int startLenght;
	int playerNo;
	int r, g, b;
	Point2D boundary;
	Point2D startPos;
	Point2D direction; 
	DoublyLinkedList body;
	Food* food;
	Snake* enemy;
	SDL_Renderer* renderer;
};

class BodyPart :public Node
{
public:
	BodyPart() :size(1),r(0),g(255),b(50) {};
	BodyPart(int size, int r, int g, int b) :size(size), r(r), g(g), b(b) {};
	~BodyPart(){};
	void render(SDL_Renderer* renderer);
	void color(int r,int g,int b);
	Point2D pos;
private:
	int size;
	int r, g, b;
};


