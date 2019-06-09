#include "Game.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"

Game::Game(GLuint width, GLuint height)
	: State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}

Game::~Game()
{
	delete Renderer;
}

void Game::Init()
{
	// Load shaders
	ResourceManager::LoadShader("./SpriteShader.vert", "./SpriteShader.frag", nullptr, "sprite");
	// Configure shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("sprite", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
	// Load textures
	ResourceManager::LoadTexture("./res/textures/tiles/gravel.jpg", GL_FALSE, "gravel");
	ResourceManager::LoadTexture("./res/textures/tiles/sand.png", GL_FALSE, "sand");
	ResourceManager::LoadTexture("./res/textures/tiles/water.jpg", GL_FALSE, "water");
	ResourceManager::LoadTexture("./res/textures/tiles/grass.png", GL_FALSE, "grass");
	// Set render-specific controls
	Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
	// Load levels
	GameLevel one; one.Load("./res/levels/one.level", this->Width, this->Height);
	this->Levels.push_back(one);
	this->Level = 0;
}

void Game::Update(GLfloat dt)
{

}


void Game::ProcessInput(GLfloat dt)
{

}

void Game::Render()
{
	if (this->State == GAME_ACTIVE)
	{
		// Draw level
		this->Levels[this->Level].Draw(*Renderer);
	}
}