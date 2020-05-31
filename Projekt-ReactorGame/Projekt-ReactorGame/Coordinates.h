#pragma once
//function to delete, sf::Vector2i is just better
struct Coordinates {
	//top left is 00, bottom right is xx
	int x;
	int y;
	Coordinates() { x = 0, y = 0; };
	Coordinates(int x_, int y_) { x = x_, y = y_; };
};
