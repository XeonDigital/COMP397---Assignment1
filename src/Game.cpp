#include "Game.h"
#include <ctime>
#include "GLM/gtx/string_cast.hpp"
#include <algorithm>
#include <iomanip>


Game* Game::s_pInstance = 0;

// Game functions - DO NOT REMOVE ***********************************************

Game::Game() :
	m_pWindow(nullptr), m_pRenderer(nullptr), m_currentFrame(0), m_bRunning(true), m_frames(0), m_deltaTime(0), m_currentScene(nullptr), m_currentSceneState(NO_SCENE)
{
	srand(unsigned(time(nullptr)));  // random seed

	
}

Game::~Game()
= default;


bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	// initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{
		std::cout << "SDL Init success" << std::endl;

		// if succeeded create our window
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		// if window creation successful create our renderer
		if (m_pWindow != nullptr)
		{
			std::cout << "window creation success" << std::endl;
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);


			if (m_pRenderer != nullptr) // render init success
			{
				std::cout << "renderer creation success" << std::endl;
				SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
			}
			else
			{
				std::cout << "renderer init failure" << std::endl;
				return false; // render int fail
			}

			// IMGUI 
			ImGui::CreateContext();
			ImGuiSDL::Initialize(m_pRenderer, width, height);

			// Initialize Font Support
			if (TTF_Init() == -1)
			{
				printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
				return false;
			}

			

			//TheTextureManager::Instance()->load("../../Assets/textures/animate-alpha.png", "animate", m_pRenderer);
			start();

		}
		else 
		{
			std::cout << "window init failure" << std::endl;
			return false; // window init fail
		}
	}
	else
	{
		std::cout << "SDL init failure" << std::endl;
		return false; //SDL could not intialize
	}

	std::cout << "init success" << std::endl;
	m_bRunning = true; // everything initialized successfully - start the main loop

	return true;
}

void Game::start()
{
	m_currentSceneState = SceneState::NO_SCENE;

	changeSceneState(SceneState::START_SCENE);
}

SDL_Renderer * Game::getRenderer()
{
	return m_pRenderer;
}

glm::vec2 Game::getMousePosition()
{
	return m_mousePosition;
}

void Game::setFrames(Uint32 frames)
{
	m_frames = frames;
}

Uint32 Game::getFrames()
{
	return m_frames;
}

void Game::setDeltaTime(float time)
{
	m_deltaTime = time;
}

float Game::getDeltaTime()
{
	return m_deltaTime;
}

void Game::changeSceneState(SceneState newState)
{
	if (newState != m_currentSceneState) {

		// if this is not the first time we're rendering a new scene
		if (m_currentSceneState != SceneState::NO_SCENE) 
		{
			m_currentScene->clean();
			std::cout << "cleaning previous scene" << std::endl;
			FontManager::Instance()->clean();
			std::cout << "cleaning FontManager" << std::endl;
			TextureManager::Instance()->clean();
			std::cout << "cleaning TextureManager" << std::endl;
		}

		m_currentSceneState = newState;
		
		switch (m_currentSceneState)
		{
		case START_SCENE:
			m_currentScene = new StartScene();
			std::cout << "start scene activated" << std::endl;
			break;
		default:
			std::cout << "default case activated" << std::endl;
			break;
		}
	}
	
}

void Game::quit()
{
	m_bRunning = false;
}

void Game::render()
{
	SDL_RenderClear(m_pRenderer); // clear the renderer to the draw colour

	m_currentScene->draw();

	SDL_RenderPresent(m_pRenderer); // draw to the screen
}

void Game::update()
{
	m_currentScene->update();
}

void Game::clean()
{
	std::cout << "cleaning game" << std::endl;

	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);

	// Clean Up for ImGui
	ImGui::DestroyContext();

	TTF_Quit();

	SDL_Quit();

	
}

void Game::handleEvents()
{
	m_currentScene->handleEvents();

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_bRunning = false;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) 
			{
				case SDLK_ESCAPE:
					m_bRunning = false;
					break;
			}
			break;
		default:
			break;
		}
	}
}