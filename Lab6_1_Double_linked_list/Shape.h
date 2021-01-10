#pragma once
#include "SDL.h"
#include "Point2D.h"
#include <string>
#include <iostream>
//using namespace std;

class Shape
{
public:
	Shape(Point2D _pos, int r=0, int g=0, int b=0, int a=255);//for assignment
	virtual void render(SDL_Renderer* rend) = 0;
	void color(int r=0, int g=0, int b=0, int a=255);
	std::string info();
protected:
	Point2D pos;
	int col[4];
};

class Rectangle :public Shape
{
public:
	Rectangle(Point2D _pos=Point2D(0,0), int r=0, int g=0, int b=0, int a=0, int _width=1, int _height=1);
	void render(SDL_Renderer* rend);
private:
	int width, height;
};

class Triangle :public Shape
{
public:
	Triangle(Point2D _pos = Point2D(0, 0), int r = 0, int g = 0, int b = 0, int a = 0, int _width = 1, int _height = 1);
	void render(SDL_Renderer* rend);
private:
	int base, height;
};

class Circle :public Shape
{
public:
	Circle(Point2D _pos = Point2D(0, 0), int r = 0, int g = 0, int b = 0, int a = 0, float _radius = 1, int res =10);
	void render(SDL_Renderer* rend);
private:
	float radius;
	int resolution;
};

