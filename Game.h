#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "GameLevel.h"

#include <vector>

enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

class SpriteRenderer;
class Game
{
public:

	GameState State;
	GLboolean Keys[1024];
	GLuint Width, Height;

	Game(GLuint width, GLuint height);
	~Game();

	void Init();

	void ProcessInput(GLfloat dt);
	void Update(GLfloat dt);
	void Render();

private:

	SpriteRenderer* Renderer = nullptr;
	std::vector<GameLevel> Levels;
	GLuint                 Level;
};
