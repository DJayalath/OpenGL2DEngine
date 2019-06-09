#include "GameLevel.h"

#include <fstream>
#include <sstream>
#include <iostream>

// Colours
#define C1 glm::vec3(0.2f, 0.6f, 1.0f)
#define C2 glm::vec3(0.0f, 0.7f, 0.0f)
#define C3 glm::vec3(0.8f, 0.8f, 0.4f)
#define C4 glm::vec3(1.0f, 0.5f, 0.0f)

void GameLevel::Load(const GLchar* file, GLuint levelWidth, GLuint levelHeight)
{
	// Clear old data
	this->tileObjects.clear();
	// Load from file
	GLuint tileCode;
	GameLevel level;
	std::string line;
	std::ifstream fstream(file);
	std::vector<std::vector<GLuint>> tileData;
	if (fstream)
	{
		while (std::getline(fstream, line)) // Read each line from level file
		{
			std::istringstream sstream(line);
			std::vector<GLuint> row;
			while (sstream >> tileCode) // Read each word seperated by spaces
				row.push_back(tileCode);
			tileData.push_back(row);
		}
		if (tileData.size() > 0)
			this->init(tileData, levelWidth, levelHeight);
	}
}

void GameLevel::Draw(SpriteRenderer& renderer)
{
	for (GameObject& tile : this->tileObjects)
		if (!tile.Destroyed)
			tile.Draw(renderer);
}

GLboolean GameLevel::IsCompleted()
{
	for (GameObject& tile : this->tileObjects)
		if (!tile.IsSolid && !tile.Destroyed)
			return GL_FALSE;
	return GL_TRUE;
}

void GameLevel::init(std::vector<std::vector<GLuint>> tileData, GLuint levelWidth, GLuint levelHeight)
{
	// Calculate dimensions
	GLuint height = tileData.size();
	GLuint width = tileData[0].size(); // Note we can index vector at [0] since this function is only called if height > 0
	GLfloat unit_width = levelWidth / static_cast<GLfloat>(width), unit_height = levelHeight / static_cast<GLfloat>(height);
	// Initialize level tiles based on tileData		
	for (GLuint y = 0; y < height; ++y)
	{
		std::cout << std::endl;
		for (GLuint x = 0; x < width; ++x)
		{
			std::cout << tileData[y][x];
			if (tileData[y][x] >= 1)	// Non-solid; now determine its color based on level data
			{
				Texture2D texture;
				glm::vec3 color = glm::vec3(1.0f); // original: white

				if (tileData[y][x] == 1)
					texture = ResourceManager::GetTexture("grass");
				else if (tileData[y][x] == 2)
					texture = ResourceManager::GetTexture("water");
				else if (tileData[y][x] == 3)
					texture = ResourceManager::GetTexture("sand");
				else if (tileData[y][x] == 4)
					texture = ResourceManager::GetTexture("gravel");
				else if (tileData[y][x] == 5)
					texture = ResourceManager::GetTexture("water");

				glm::vec2 pos(unit_width * x, unit_height * y);
				glm::vec2 size(unit_width, unit_height);
				this->tileObjects.push_back(GameObject(pos, size, texture, color));
			}
		}
	}
}