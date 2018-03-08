#pragma once
#include "stdafx.h"

class Point {
public:
	int x;
	int y;
	Point(int x = 0, int y = 0) : x(x), y(y) {}

	Point operator+ (const Point& p) {
		return Point(p.x + x, p.y + y);
	}
	Point operator- (const Point& p) {
		return Point(p.x - x, p.y - y);
	}
	Point& operator= (const Point& p) {
		x = p.x;
		y = p.y;
		return *this;
	}
	Point& operator+= (const Point& p) {
		return *this = *this + p;
	}
	Point& operator-= (const Point& p) {
		return *this = *this - p;
	}
	~Point() = default;
};

const int WIDTH = 10;
const int HEIGHT = 19;
const int DELTA = 30;
const int FIGURE_SIZE = 4;
const int NUMOFFIG = 4;

bool inBounds(Point& p) {
	return (p.x < WIDTH) && (p.x >= 0);
}

COLORREF toColorRef(int c) {
	COLORREF color;
	switch(c) {
	case 0:
		color = RGB(0, 0, 0);
		break;
	case 1:
		color = RGB(255, 255, 154);
		break;
	case 2:
		color = RGB(154, 205, 50);
		break;
	case 3:
		color = RGB(0, 191, 255);
		break;
	case 4:
		color = RGB(255, 193, 193);
		break;
	case 5:
		color = RGB(255, 255, 255);
		break;
	}
	return color;
}

namespace random {
	short Color() {
		short res = rand() % NUMOFFIG + 1 + 1;
		return res;
	}
}