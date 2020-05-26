#pragma once
struct Coordinates {
	int x;
	int y;
	Coordinates() { x = 0, y = 0; };
	Coordinates(int x_, int y_) { x = x_, y = y_; };
};
