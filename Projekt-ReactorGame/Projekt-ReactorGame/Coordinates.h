#pragma once
///Nieużywana struktura - pozostawiona jako przypomnienie, że używanie sf::Vector2i jest lepsze
struct Coordinates {
	//top left is 00, bottom right is xx
	int x;
	int y;
	Coordinates() { x = 0, y = 0; };
	Coordinates(int x_, int y_) { x = x_, y = y_; };
};
