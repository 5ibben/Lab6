#pragma once
#include <string>
#include <iostream>

class Point2D
{
public:
	Point2D();//default constructor
	Point2D(int _x, int _y);//initialize constructor
	Point2D(const Point2D& other);//copy constructor

	Point2D operator+(const Point2D& other) const;//addition operator
	bool operator==(const Point2D& other) const;//bool operator
	const Point2D& operator=(const Point2D& other);//assignment operator

	float distance(Point2D other);
	std::string toString();
	int x, y;
protected:
};