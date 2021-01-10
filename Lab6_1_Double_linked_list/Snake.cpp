#pragma once
#include "Snake.h"

Food::Food(SDL_Renderer* renderer, Point2D mapSize, int scale)
	:renderer(renderer), mapSize(mapSize), size(scale), pos((mapSize.x / 2), (mapSize.y / 2)) {}

//changes position of food
void Food::replace()
{
	render(0, 0, 0);
	pos.x = (rand() % mapSize.x / size) * size;
	pos.y = (rand() % mapSize.y / size) * size;
	render();
}

void Food::render(int r, int g, int b)
{
	Circle food(pos, r, g, b, 255, size/2,size/2);
	Triangle food1(pos, r, g, b, 255, size, size);
	Rectangle food2(pos, r, g, b, 255, size, size);
	food.render(renderer);
	food1.render(renderer);
	food2.render(renderer);
}

Snake::Snake(SDL_Renderer* renderer, Food* food, Point2D boundary, int size, Point2D startPos,int startLenght)
	:direction(Point2D(1, 0)), renderer(renderer),food(food),boundary(boundary),
	size(size),startPos(startPos), r(0), g(255), b(50),alive(true),enemy(nullptr),startLenght(startLenght),playerNo(1)
{
	//determines starting direction
	if (startPos.x*size > boundary.x-size)
		direction.x = -1;
	grow(startLenght);
}

void Snake::setDirection(int dir)
{
	//checks so the snake doesn´t turn back on itself
		if (dir == 0 && direction.y != 1)
			direction = Point2D(0, -1);
		if (dir == 1 && direction.y != -1)
			direction = Point2D(0, 1);
		if (dir == 2 && direction.x != 1)
			direction = Point2D(-1, 0);
		if (dir == 3 && direction.x != -1)
			direction = Point2D(1, 0);
}

//moves the snake one step in its current direction
//by removing last node, and adding a new node in the front
void Snake::move()
{
	//remove back
	BodyPart* last = dynamic_cast<BodyPart*>(body.last());
	last->color(0, 0, 0);
	last->render(renderer);
	body.remove(body.size() - 1);
	//add front
	grow();
}

//grows the snake by adding another section to it´s front
void Snake::grow(int amount)
{
	BodyPart* newHead = new BodyPart(size,r,g,b);
	BodyPart* oldHead = dynamic_cast<BodyPart*>(body.nodeAt(0));
	if (body.size() == 0)
	{
		newHead->pos = startPos;
	}
	if (body.size() != 0)
	{
		//set new front position
		newHead->pos.x = oldHead->pos.x + direction.x*size;
		newHead->pos.y = oldHead->pos.y + direction.y*size;
		//keep the snake within the boundaries
		if (newHead->pos.x>=boundary.x)
			newHead->pos.x = 0;
		if (newHead->pos.x < 0)
			newHead->pos.x = boundary.x - size;
		if (newHead->pos.y >= boundary.y)
			newHead->pos.y = 0;
		if (newHead->pos.y < 0)
			newHead->pos.y = boundary.y - size;
	}
	//add new front
	body.add(newHead, 0);

	//collision, head - food
	if (newHead->pos==food->pos)
	{
		grow();
		printScore();
	}

	//collision with other snake
	if (enemy)
	{
		//collision, head - other head
		if (newHead->pos == dynamic_cast<BodyPart*>(enemy->body.nodeAt(0))->pos)
		{
			if (playerNo != enemy->playerNo)
				std::cout << "HEADBUT!!!\n";
			//win
			if (body.size() > enemy->body.size())
			{
				std::cout <<"Player "<<playerNo<<" is bigger!\n";
				enemy->die();
			}
			//lose
			else if (body.size() < enemy->body.size())
			{
				std::cout << "Player " << enemy->playerNo << " is bigger!\n";
				die();
			}
			//draw,	each snake will make a left turn
			else if(body.size() == enemy->body.size())
			{
				if (direction == Point2D(1, 0))
				{
					newHead->pos.y -= 1 * size;
					setDirection(0);
					enemy->setDirection(1);
				}
				else if (direction == Point2D(-1, 0))
				{
					newHead->pos.y += 1 * size;
					setDirection(1);
					enemy->setDirection(0);
				}
				else if (direction == Point2D(0, 1))
				{
					newHead->pos.x += 1 * size;
					setDirection(3);
					enemy->setDirection(2);
				}
				else if (direction == Point2D(0, -1))
				{
					newHead->pos.x -= 1 * size;
					setDirection(2);
					enemy->setDirection(3);
				}
			}
		}
		//collision, head - other body
		else
		{
			for (int i = 1; i < enemy->body.size(); i++)
			{
				if (newHead->pos == dynamic_cast<BodyPart*>(enemy->body.nodeAt(i))->pos)
					die();
			}
		}
	}

	//collision self
	if (alive)
	{
		for (int i = 1; i < body.size(); i++)
		{
			BodyPart* currentBP = dynamic_cast<BodyPart*>(body.nodeAt(i));
			//collision head - self body
			if (dynamic_cast<BodyPart*>(body.nodeAt(0))->pos == currentBP->pos)
			{
				die();
			}
			//collision food - self body
			if (alive && food->pos == currentBP->pos)
			{
				food->replace();
				currentBP->render(renderer);
			}
		}
	}
	//render new front
	if (alive)
		newHead->render(renderer);
	//recursive growth
	if (1 < amount)
		grow(amount - 1);
}

void Snake::color(int r, int g, int b)
{
	this->r = r;
	this->g = g;
	this->b = b;
}

//kills snake and prints a console messege
void Snake::die()
{
	if (alive)
	{
		//print console messege
		if (enemy)
			std::cout << "Player " << enemy->getPlayer() << "Won!\n";
		else
			std::cout << "You died!\nFinal score:" << (body.size() - startLenght) * 10 << std::endl;
		std::cout << "PRESS SPACE TO RESTART!\n";

		//render body white
		for (int i = 0; i < body.size(); i++)
		{
			dynamic_cast<BodyPart*>(body.nodeAt(i))->color(255, 255, 255);
			dynamic_cast<BodyPart*>(body.nodeAt(i))->render(renderer);
		}
		alive = false;
		//kills enemy, for the sake of justice
		if (enemy)
			enemy->alive = false;
	}
}


void Snake::setPlayer(int playerNo)
{
	this->playerNo = playerNo;
}

int Snake::getPlayer()
{
	return playerNo;
}

void Snake::setOpponent(Snake* other)
{
	enemy = other;
}

//print scores in the console
void Snake::printScore()
{
	if (enemy)
	{
		if (playerNo == 1)
		{
			std::cout << "Player " << playerNo << " Score: " << (body.size() - startLenght) * 10;
			std::cout << " || ";
			std::cout << "Player " << enemy->getPlayer() << " Score: " << (enemy->body.size() - startLenght) * 10 << std::endl;
		}
		else
		{
			std::cout << "Player " << enemy->getPlayer() << " Score: " << (enemy->body.size() - startLenght) * 10;
			std::cout << " || ";
			std::cout << "Player " << playerNo << " Score: " << (body.size() - startLenght) * 10 << std::endl;
		}
	}
	else
	{
		std::cout << "Score: " << (body.size() - startLenght) * 10 << std::endl;
	}
}

void BodyPart::render(SDL_Renderer* renderer)
{
	Circle body(pos, r, g, b, 255,size/2);
	body.render(renderer);
}

void BodyPart::color(int r, int g, int b)
{
	this->r = r;
	this->g = g;
	this->b = b;
}

