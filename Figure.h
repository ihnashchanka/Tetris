#pragma once
#include "Constants.h"
#include <cstdlib>
#include <algorithm>
#include <string.h>
#include <time.h>
#include <vector>

class Field;

class Figure {
	friend class Field;
protected:
	short left_bound;
	short right_bound;
	short button_bound;
	short layout[FIGURE_SIZE][FIGURE_SIZE];
	Point pos;
	std::vector<Point> checkPoints;
public:
	Figure(const Figure&) = delete;
	Figure() {
		for (int i = 0; i < FIGURE_SIZE; ++i){
			memset(layout[i], 0, FIGURE_SIZE);
		}
		pos.x = WIDTH / 2 - 2;
	}
	void rotare() {
		for (int i = 0; i < FIGURE_SIZE / 2; ++i){
			for (int j = i; j < FIGURE_SIZE - 1 - i; ++j){
				short tmp = layout[i][j];
				layout[i][j] = layout[FIGURE_SIZE - j - 1][i];
				layout[FIGURE_SIZE - j - 1][i] = layout[FIGURE_SIZE - i - 1][FIGURE_SIZE - j - 1];
				layout[FIGURE_SIZE - i - 1][FIGURE_SIZE - j - 1] = layout[j][FIGURE_SIZE - i - 1];
				layout[j][FIGURE_SIZE - i - 1] = tmp;
			}
		}
		getCheckPoints();
		getButton();
	}
	std::vector<Point>& getCheckPoints() {
		checkPoints.clear();
		for (int i = FIGURE_SIZE - 1; i >= 1; --i){
			for (int j = 0; j < FIGURE_SIZE; ++j){
				if (layout[i - 1][j] != 0 && layout[i][j] == 0) {
					checkPoints.push_back(Point(j, i));
				}
			}
		}
		return checkPoints;
	}
	void getSideBounds() {
		left_bound = FIGURE_SIZE;
		for (int i = 0; i < FIGURE_SIZE; ++i){
			for (int j = 0; j < FIGURE_SIZE; ++j){
				if (layout[i][j] != 0) {
					if (left_bound > j)
						left_bound = j;
					if (right_bound < j)
						right_bound = j;
				}
			}
		}
	}
	void move(bool right) {
		getSideBounds();
		if(right) {
			if ((right_bound + pos.x)+1 >= 0 && (right_bound + pos.x)+1 < WIDTH)
				pos.x++;
		} else {
			if ((left_bound + pos.x)-1 >= 0 && (left_bound + pos.x)-1 < WIDTH)
				pos.x--;
		}
	}
	void getButton(){
		button_bound = FIGURE_SIZE-1;
		bool found = false;
		for (int j = 0; j < FIGURE_SIZE; ++j)
			if (layout[FIGURE_SIZE - 1][j] != 0)
				found = true;
		for (int i = FIGURE_SIZE - 1; i >= 1 && !found; --i){
			for (int j = 0; j < FIGURE_SIZE; ++j)
				if (layout[i - 1][j] != 0 && layout[i][j] == 0){
					button_bound = i - 1;
					found = true;
					break;
				}
		}
	}
	bool fall() {
			pos.y++;
			return true;
	}
	virtual ~Figure() {}
};
class Line : public Figure {
public: 
	Line() {
		short color = random::Color();
		for(int i = 0; i < FIGURE_SIZE; ++i)
			layout[1][i] = color;
		getButton();
		getCheckPoints();
	}
};
class Square :public Figure {
public:
	Square() {
		short color = random::Color();
		layout[1][1] = color;
		layout[1][2] = color;
		layout[2][1] = color;
		layout[2][2] = color;
		getButton();
		getCheckPoints();
	}
};
class ZigZag :public Figure {
public:
	ZigZag() {
		short color = random::Color();
		layout[1][1] = color;
		layout[1][2] = color;
		layout[2][2] = color;
		layout[2][3] = color;
		getButton();
		getCheckPoints();
	}
};
class TBone :public Figure {
public:
	TBone() {
		short color = random::Color();
		layout[1][1] = color;
		layout[1][2] = color;
		layout[1][3] = color;
		layout[2][2] = color;
		getButton();
		getCheckPoints();
	}
};