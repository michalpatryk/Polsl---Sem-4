#pragma once
#pragma warning (disable: 4244)
#include <iostream>
#include <SFML/Graphics.hpp>

class TileMap : public sf::Drawable, public sf::Transformable
{

	unsigned int tileSizeX = 0;
	unsigned int tileSizeY = 0;
	unsigned int tileMapWidth = 0;
	unsigned int tileMapHeight = 0;
	sf::Vector2i location{0,0};
	sf::VertexArray m_vertices;
	sf::Texture m_tileset;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// apply the transform
		states.transform *= getTransform();

		// apply the tileset texture
		states.texture = &m_tileset;

		// draw the vertex array
		target.draw(m_vertices, states);
	}

public:
	sf::FloatRect getBounds() {
		return m_vertices.getBounds();
	}
	//const int* tiles
	bool load(const std::string& tileset, sf::Vector2u tileSize,  std::vector<int> tiles, unsigned int width, unsigned int height, unsigned int offsetX,
		unsigned int offsetY)
	{
		// load the tileset texture
		if (!m_tileset.loadFromFile(tileset))
			return false;
		tileMapWidth = width;
		tileMapHeight = height;
		tileSizeX = tileSize.x;
		tileSizeY = tileSize.y;
		location.x = offsetX; location.y = offsetY;
		// resize the vertex array to fit the level size
		m_vertices.setPrimitiveType(sf::Quads);
		m_vertices.resize(width * height * 4);

		// populate the vertex array, with one quad per tile
		for (unsigned int i = 0; i < width; ++i)
			for (unsigned int j = 0; j < height; ++j)
			{
				// get the current tile number
				int tileNumber = tiles[i + j * width];

				// find its position in the tileset texture
				int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
				int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

			
				// get a pointer to the current tile's quad
				sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

				// define its 4 corners
				quad[0].position = sf::Vector2f(i * tileSize.x + offsetX, j * tileSize.y + offsetY);
				quad[1].position = sf::Vector2f((i + 1) * tileSize.x + offsetX, j * tileSize.y + offsetY);
				quad[2].position = sf::Vector2f((i + 1) * tileSize.x + offsetX, (j + 1) * tileSize.y + offsetY);
				quad[3].position = sf::Vector2f(i * tileSize.x + offsetX, (j + 1) * tileSize.y + offsetY);

				// define its 4 texture coordinates
				quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
				quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
				quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
				quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
			}

		return true;
	}
	void change(int x, int y, sf::Vector2u type) {
		int textureSizeX = 32;
		int textureSizeY = 32;
		sf::Vertex* quad = &m_vertices[(x + y * tileMapWidth)*4];
		quad[0].texCoords = sf::Vector2f((type.x) * tileSizeX, (type.y) * tileSizeY);
		quad[1].texCoords = sf::Vector2f((type.x + 1) * tileSizeX, (type.y) * tileSizeY);
		quad[2].texCoords = sf::Vector2f((type.x + 1) * tileSizeX, (type.y + 1) * tileSizeY);
		quad[3].texCoords = sf::Vector2f((type.x) * tileSizeX, (type.y + 1) * tileSizeY);
	}

	sf::Vector2i clickedCoordinates(sf::Vector2i mouseCoord) {
		mouseCoord -= location;
		mouseCoord.x = mouseCoord.x / tileSizeX;
		mouseCoord.y = mouseCoord.y / tileSizeY;
		return mouseCoord;
	}
	
};

