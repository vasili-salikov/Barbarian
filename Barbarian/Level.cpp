#include "Level.h"

bool Level::LoadFromFile(std::string filename)
{
	//whole tmx document
	TiXmlDocument levelFile(filename.c_str()); //load file into TiXmlDocument (TinyXML library)

	//load XML-map
	if (!levelFile.LoadFile()) //in case of error
	{
		std::cout << "Loading level \"" << filename << "\" failed." << std::endl;
		return false;
	}

	//get <map> tag
	// map example: <map version="1.0" orientation="orthogonal"
	// width="10" height="10" tilewidth="34" tileheight="34">
	TiXmlElement* map;
	map = levelFile.FirstChildElement("map");

	//get map properties from tag attributes
	width = atoi(map->Attribute("width"));
	height = atoi(map->Attribute("height"));
	tileWidth = atoi(map->Attribute("tilewidth"));
	tileHeight = atoi(map->Attribute("tileheight"));

	//get <tileset> tag and its id from "firstgid" attribute
	TiXmlElement* tilesetElement;
	tilesetElement = map->FirstChildElement("tileset");
	firstTileID = atoi(tilesetElement->Attribute("firstgid"));

	// Get the <image> tag from tilesetElement (it's nested inside),
	// then get the path to the tileset image.
	TiXmlElement* image;
	image = tilesetElement->FirstChildElement("image");
	std::string imagepath = image->Attribute("source");

	//try to load the image from the source
	sf::Image img;

	if (!img.loadFromFile(imagepath)) //in case of error
	{
		std::cout << "Failed to load tile sheet." << std::endl;
		return false;
	}

	img.createMaskFromColor(sf::Color(255, 255, 255)); //Used for masking background color if needed (currently off)
	tilesetImage.loadFromImage(img);
	tilesetImage.setSmooth(false); //disable texture smoothing (for pixelated style)

	// Get the number of columns and rows by dividing the image resolution by the tile size
	int columns = tilesetImage.getSize().x / tileWidth;
	int rows = tilesetImage.getSize().y / tileHeight;

	// Vector of IntRects representing tile regions in the tileset texture
	std::vector<sf::IntRect> subRects;

	for (int y = 0; y < rows; y++)
		for (int x = 0; x < columns; x++)
		{
			sf::IntRect rect;

			rect.position.y = y * tileHeight; //rect.top 
			rect.position.x = x * tileWidth; //rect.left
			rect.size.y = tileHeight; //rect.height
			rect.size.x = tileWidth; // rect.width
			
			/*rect.top = y * tileHeight;
			rect.left = x * tileWidth;
			rect.height = tileHeight;
			rect.width = tileWidth;*/

			subRects.push_back(rect);
		}

	//Work with layers
	//Get the first <layer> element from the map document
	TiXmlElement* layerElement;
	layerElement = map->FirstChildElement("layer");
	while (layerElement)
	{
		Layer layer;

		// If the opacity attribute is present, set the layer's transparency - otherwise, it's fully opaque
		if (layerElement->Attribute("opacity") != NULL)
		{
			float opacity = strtod(layerElement->Attribute("opacity"), NULL);
			layer.opacity = 255 * opacity;
		}
		else
		{
			layer.opacity = 255;
		}

		// Get the <data> element (a child of <layer> that contains all the tile definitions)
		TiXmlElement* layerDataElement;
		layerDataElement = layerElement->FirstChildElement("data");

		if (layerDataElement == NULL) //No layer
		{
			std::cout << "Bad map. No layer information found." << std::endl;
		}

		// <tile> elements – contain tile definitions for the current layer
		TiXmlElement* tileElement;
		tileElement = layerDataElement->FirstChildElement("tile");

		if (tileElement == NULL) //no tile
		{
			std::cout << "Bad map. No tile information found." << std::endl;
			return false;
		}

		int x = 0;
		int y = 0;

		while (tileElement)
		{
			// IMPORTANT FIX:
			// If a <tile> tag doesn't have a "gid" attribute, set tileGID = 0
			const char* attr = tileElement->Attribute("gid");
			int tileGID = attr ? atoi(attr) : 0;
			//int tileGID = atoi(tileElement->Attribute("gid")); // unsafe version (removed)
			int subRectToUse = tileGID - firstTileID;

			// Set the texture rectangle for each tile
			if (subRectToUse >= 0)
			{
				sf::Sprite sprite(tilesetImage);
				sprite.setTextureRect(subRects[subRectToUse]);
				sprite.setPosition(sf::Vector2f(x * tileWidth, y * tileHeight));
				sprite.setColor(sf::Color(255, 255, 255, layer.opacity));

				layer.tiles.push_back(sprite);//закидываем в слой спрайты тайлов

				//sf::Sprite sprite;
				//sprite.setTexture(tilesetImage);
				//sprite.setTextureRect(subRects[subRectToUse]);
				//sprite.setPosition(x * tileWidth, y * tileHeight);
				//sprite.setColor(sf::Color(255, 255, 255, layer.opacity));

				//layer.tiles.push_back(sprite);//закидываем в слой спрайты тайлов
			}

			tileElement = tileElement->NextSiblingElement("tile");

			x++;
			if (x >= width)
			{
				x = 0;
				y++;
				if (y >= height)
					y = 0;
			}
		}

		layers.push_back(layer);

		layerElement = layerElement->NextSiblingElement("layer");
	}

	//Work with objects
	TiXmlElement* objectGroupElement;

	// If there are object layers
	if (map->FirstChildElement("objectgroup") != NULL)
	{
		objectGroupElement = map->FirstChildElement("objectgroup");
		while (objectGroupElement)
		{
			// <object> element container
			TiXmlElement* objectElement;
			objectElement = objectGroupElement->FirstChildElement("object");

			while (objectElement)
			{
				// Retrieve all object data – type, name, position, etc.
				std::string objectType;
				if (objectElement->Attribute("type") != NULL)
				{
					objectType = objectElement->Attribute("type");
				}
				std::string objectName;
				if (objectElement->Attribute("name") != NULL)
				{
					objectName = objectElement->Attribute("name");
				}
				int x = atoi(objectElement->Attribute("x"));
				int y = atoi(objectElement->Attribute("y"));

				int width, height;

				sf::Sprite sprite(tilesetImage);
				sprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(0, 0)));
				sprite.setPosition(sf::Vector2f(x, y));

				/*sf::Sprite sprite;
				sprite.setTexture(tilesetImage);
				sprite.setTextureRect(sf::Rect<int>(0, 0, 0, 0));
				sprite.setPosition(x, y);*/

				if (objectElement->Attribute("width") != NULL)
				{
					width = atoi(objectElement->Attribute("width"));
					height = atoi(objectElement->Attribute("height"));
				}
				else
				{
					width = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].size.x;
					height = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].size.y;

					sprite.setTextureRect(subRects[atoi(objectElement->Attribute("gid")) - firstTileID]);

					/*width = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].width;
					height = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].height;*/
					//sprite.setTextureRect(subRects[atoi(objectElement->Attribute("gid")) - firstTileID]);
				}

				// Object instance
				//Object object;
				//object.name = objectName;
				//object.type = objectType;
				//object.sprite = sprite;

				//Object instance
				sf::FloatRect objectRect;
				objectRect.position.y = y;
				objectRect.position.x = x;
				objectRect.size.y = height;
				objectRect.size.x = width;				

				Object object(sprite, objectName, objectType, objectRect);

				// "variables" of object
				TiXmlElement* properties;
				properties = objectElement->FirstChildElement("properties");
				if (properties != NULL)
				{
					TiXmlElement* prop;
					prop = properties->FirstChildElement("property");
					if (prop != NULL)
					{
						while (prop)
						{
							std::string propertyName = prop->Attribute("name");
							std::string propertyValue = prop->Attribute("value");

							object.properties[propertyName] = propertyValue;

							prop = prop->NextSiblingElement("property");
						}
					}
				}


				objects.push_back(object);

				objectElement = objectElement->NextSiblingElement("object");
			}
			objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
		}
	}
	else
	{
		std::cout << "No object layers found..." << std::endl;
	}

	return true;
}

Object Level::GetObject(std::string name)
{
	// get the first object with given name
	for (int i = 0; i < objects.size(); i++)
		if (objects[i].name == name)
			return objects[i];
}

std::vector<Object> Level::GetObjects(std::string name)
{
	// get all the objects with given name
	std::vector<Object> vec;
	for (int i = 0; i < objects.size(); i++)
		if (objects[i].name == name)
			vec.push_back(objects[i]);

	return vec;
}

std::vector<Object> Level::GetAllObjects()
{
	return objects;
};


sf::Vector2i Level::GetTileSize() //get tile size (initial information from the map document)
{
	return sf::Vector2i(tileWidth, tileHeight);
}

void Level::Draw(sf::RenderWindow& window)
{
	// Draw all the tiles (objects do not draw!)
	for (int layer = 0; layer < layers.size(); layer++)
		for (int tile = 0; tile < layers[layer].tiles.size(); tile++)
			window.draw(layers[layer].tiles[tile]);
}


