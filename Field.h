#pragma once
#include "stdafx.h"
#include "Figure.h"

class Field {
private:
	short layout[HEIGHT][WIDTH];
	Figure* figure = 0;
	bool gameover = 0;
public:
	Field(){
		for (int i = 0; i < HEIGHT; ++i){
			memset(layout[i], 0, WIDTH * sizeof(short));
		}
		spawn();
	}
	Field(const Field&) = delete;
	Figure* getFigure() {
		return figure;
	}
	void spawn() {
		int percent = rand() % NUMOFFIG;
		switch (percent) {
		case 0:
			figure = new Line();
			break;
		case 1:
			figure = new Square();
			break;
		case 2:
			figure = new ZigZag();
			break;
		case 3:
			figure = new TBone();
			break;
		}
	}

	void displayFigure(){
		for (int i = 0; i < FIGURE_SIZE; ++i){
			for (int j = 0; j < FIGURE_SIZE; ++j){
				if (figure->layout[i][j] != 0){
					layout[figure->pos.y + i][figure->pos.x + j] = figure->layout[i][j];
				}
			}
		}
	}

	bool checkRows(){
		bool flag;
		int button = figure->pos.y + FIGURE_SIZE;
		for (int i = figure->pos.y; i < button && i < HEIGHT; ++i){
			flag = true;
			for (int j = 0; j < WIDTH; ++j){
				if (layout[i][j] == 0) {
					flag = false;
					break;
				}
			}
			if (flag){
				for (int _i = i; _i > 0; --_i){
					memcpy(layout[_i], layout[_i - 1], WIDTH * sizeof(short));
				}
			}
		}
		return flag;
	}

	bool update(){
		bool toContinue = true;
		std::vector<Point>& points = figure->checkPoints;
		for (std::vector<Point>::iterator it = points.begin(); it != points.end(); ++it){
			if (layout[figure->pos.y + it->y][figure->pos.x + it->x] != 0){
				toContinue = false;
				break;
			}
		}
		for (int i = 0; i < FIGURE_SIZE; ++i){
			if (layout[figure->button_bound + figure->pos.y + 1][figure->pos.x + i] != 0 && figure->layout[FIGURE_SIZE - 1][i] != 0){
				toContinue = false;
				break;
			}
		}
		if (figure->button_bound + figure->pos.y + 1 >= HEIGHT){
			toContinue = false;
		}
		if (!toContinue){
			displayFigure();
			checkRows();
			if (figure->pos.y <= 1){
				gameover = true;
			}
			delete figure;
			figure = 0;
			spawn();

		}
		else if (figure){
			figure->fall();
		}
		return !gameover;
	}

	void draw(CDC* cdc) {
		for (int i = 0; i < HEIGHT; ++i){
			for (int j = 0; j < WIDTH; ++j){
				cdc->FillSolidRect(
					j*DELTA,
					i*DELTA,
					DELTA,
					DELTA,
					toColorRef(layout[i][j]));
			}
		}
		if (figure){
			for (int i = 0; i < FIGURE_SIZE; ++i){
				for (int j = 0; j < FIGURE_SIZE; ++j) {
					if (figure->layout[i][j] != 0)
						cdc->FillSolidRect(
						(j + figure->pos.x)*DELTA,
						(i + figure->pos.y)*DELTA,
						DELTA,
						DELTA,
						toColorRef(figure->layout[i][j])
						);
				}
			}
		}
	}
	~Field() {}
};

