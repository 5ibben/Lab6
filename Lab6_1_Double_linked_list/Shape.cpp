#include "Shape.h"
#include <math.h>

Shape::Shape(Point2D _pos, int r, int g, int b, int a)
{
	pos = _pos;
	color(r, g, b, a);
}

void Shape::color(int r, int g, int b, int a)
{
	if (0 <= r && r <= 255)
		col[0] = r;
	if (0 <= g && g <= 255)
		col[1] = g;
	if (0 <= b && b <= 255)
		col[2] = b;
	if (0 <= a && a <= 255)
		col[3] = a;
}

std::string Shape::info()
{
	std::string infostring = "Position: " + pos.toString() + " Color: (";
	for (int i = 0; i < 4; i++)
	{
		infostring += std::to_string(col[i]);
		if (i<3)
			infostring += ",";
	}
	infostring += ")";
	return infostring;
}

Rectangle::Rectangle(Point2D _pos, int r, int g, int b, int a, int _width, int _height)
	:Shape(_pos,r,g,b,a),width(_width),height(_height){}

void Rectangle::render(SDL_Renderer* rend)
{
	//set color
	SDL_SetRenderDrawColor(rend, col[0], col[1], col[2], col[3]);
	//defines corners
	Point2D cornerUL = Point2D(pos.x, pos.y);
	Point2D cornerUR = Point2D(pos.x+width, pos.y);
	Point2D cornerLR = Point2D(pos.x+width, pos.y+height);
	Point2D cornerLL = Point2D(pos.x, pos.y+height);
	//draw lines between corners
	SDL_RenderDrawLine(rend, cornerUL.x, cornerUL.y, cornerUR.x, cornerUR.y);
	SDL_RenderDrawLine(rend, cornerUR.x, cornerUR.y, cornerLR.x, cornerLR.y);
	SDL_RenderDrawLine(rend, cornerLR.x, cornerLR.y, cornerLL.x, cornerLL.y);
	SDL_RenderDrawLine(rend, cornerLL.x, cornerLL.y, cornerUL.x, cornerUL.y);
}

Triangle::Triangle(Point2D _pos, int r, int g, int b, int a, int _width, int _height)
	:Shape(_pos, r, g, b, a), base(_width), height(_height) {}

void Triangle::render(SDL_Renderer* rend)
{
	//set color
	SDL_SetRenderDrawColor(rend, col[0], col[1], col[2], col[3]);
	//defines corners
	Point2D cornerU = Point2D(pos.x+base/2, pos.y);
	Point2D cornerRR = Point2D(pos.x + base, pos.y+height);
	Point2D cornerLR = Point2D(pos.x, pos.y + height);
	//draw lines between corners
	SDL_RenderDrawLine(rend, cornerU.x, cornerU.y, cornerRR.x, cornerRR.y);
	SDL_RenderDrawLine(rend, cornerRR.x, cornerRR.y, cornerLR.x, cornerLR.y);
	SDL_RenderDrawLine(rend, cornerLR.x, cornerLR.y, cornerU.x, cornerU.y);
}

Circle::Circle(Point2D _pos, int r, int g, int b, int a, float _radius,int res)
	:Shape(_pos, r, g, b, a), radius(_radius),resolution(res){}

void Circle::render(SDL_Renderer* rend)
{
	//set color
	SDL_SetRenderDrawColor(rend, col[0], col[1], col[2], col[3]);
	//set starting points
	Point2D center = Point2D(pos.x + radius, pos.y + radius);
	Point2D current= Point2D(pos.x +2* radius, pos.y + radius);;
	Point2D next;
	//set points & draw lines between them for a full revolution
	//the condition: 2 times pi for a complete revolution, the increment to i is added to fill the gap. 
	for (float i = 0; i < 2 * M_PI + 1. / resolution; i+= 1. / resolution)
	{
		next.x = center.x + radius * cos(i);
		next.y = center.y + radius * sin(i);
		SDL_RenderDrawLine(rend, current.x, current.y, next.x, next.y);
		current = next;
	}
	

}
