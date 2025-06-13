#pragma once
#include <SFML/Graphics.hpp>
#include "Object.h"
#include "../../TinyXML/tinyxml.h"
#include <iostream> //for error messages

struct Layer// <layer> elements from tmx
{
	int opacity;
	std::vector<sf::Sprite> tiles; //collection of tiles
};

class Level
{
public:
	Level(std::string pathToMapFile); //load from file
	
	void draw(sf::RenderWindow& window);// Draw all the tiles (objects do not draw!)
	sf::Vector2i getTileSize();//get tile size (initial information from the map document)

	Object getObjectByValue(std::string name);
	std::vector<Object> getObjectsByValue(std::string name);// get the first object with given name
	std::vector<Object> getAllObjectsByValue();// get all the objects with given name

	Object* getObjectByReference(std::string name);
	std::vector<Object*> getAllObjectsByReference();
	std::vector<Object*> getObjectsByReference(std::string name);

private:
	int width, height, tileWidth, tileHeight; // In the TMX file, width and height come first, followed by the tile size
	int firstTileID;
	sf::FloatRect drawingBounds;// The size of the map section to be drawn
	sf::Texture tilesetImage;
	std::vector<Object> objects;//all the objects on the map
	std::vector<Object*> objectsRefs; // all the references on objects on the map
	std::vector<Layer> layers;

	bool loadFromFile(std::string filename); // Returns false if loading failed
};