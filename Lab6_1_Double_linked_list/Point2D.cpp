#include "Point2D.h"
#include <math.h>

Point2D::Point2D()
	:x(0), y(0) {}

Point2D::Point2D(int _x, int _y)
	: x(_x), y(_y) {}

Point2D::Point2D(const Point2D& other)
	: x(other.x), y(other.y) {}

Point2D Point2D::operator+(const Point2D& other) const
{
	return Point2D(x + other.x, y + other.y);
}

bool Point2D::operator==(const Point2D& other) const
{
	return (x == other.x && y == other.y);
}

const Point2D& Point2D::operator=(const Point2D& other)
{
	if (this != &other)
	{
		x = other.x;
		y = other.y;
	}
	return *this;
}

float Point2D::distance(Point2D other)
{
	return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
}

std::string Point2D::toString()
{// returns in format "[x, y]"
	return  "[" + std::to_string(x) + ", " + std::to_string(y) + "]";
}