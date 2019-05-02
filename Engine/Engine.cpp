#include "Engine.h"
#include <iostream>
#include "SystemManager.h"
#include "Timer.h"
#include "Manager.h"
#include <SDL_ttf.h>
#include "Scene.h"


namespace core {

	Engine::Engine(scene::Scene *scene_) : mainScene(scene_),	// Second type of initialization (better)						
	isRunning(false), frameRate(30), gameOverTimer(60)			// because initialize once
	{
		//mainScene = scene_;									// Third type of initialization

		managers.push_back(SystemManager::GetInstance());

	}

	Engine::~Engine() {
	}

	int Engine::Init() {

		// Get singleton of input and window
		input  = static_cast<Input*>(core::SystemManager::GetInstance()->GetSystem(core::SystemType::INPUT));
		window = static_cast<Window*>(core::SystemManager::GetInstance()->GetSystem(core::SystemType::WINDOW));

		if (input != nullptr && window != nullptr) {	

			if (!SdlInit()) {

				if (!window->Init()) {

					// Initialize main scene
					mainScene->Init();
					
					// Run the game
					Run();
				}
				else { 
					return ENGINE_INIT_ERROR; 
				}			
			}
			else {
				return ENGINE_INIT_ERROR;
			}
		}
		else {
			return ENGINE_INIT_ERROR;
		}

		return 0;
	}

	int Engine::Run() {

		Timer timer;
		timer.Start();

		while (!input->QuitRequested()) {

			// Check if Game Over
			if (mainScene->GetGameOver()) {
				gameOverTimer--;
				if (gameOverTimer <= 0) break;
			}
			else {

				// Check if the user has pressed a keyboard
				input->Update();

				// Update
				Update();

				// Render
				Draw();
			}

			// Keep the event loop running at a sane rate
			SDL_Delay(timer.GetSleepTime(frameRate));			
		}

		// ShutDown
		ShutDown();

		return 0;
	}

	void Engine::Update() {

		// Call main scene 
		mainScene->Update();
	}

	void Engine::Draw() const {

		// Draw the objects in scene
		mainScene->Draw();
	}

	int Engine::ShutDown() {

		if (!mainScene->Shutdown()) {
			return ENGINE_SHUTDOWN_ERROR;
		}

		//Destroy window
		//SDL_DestroyWindow(window->GetWindow());

		//Quit SDL subsystems
		SDL_Quit();
		TTF_Quit();

		return 0;
	}

	int Engine::SdlInit() {

		// Initialize SDL
		if (SDL_Init(SDL_INIT_EVERYTHING | SDL_INIT_EVENTS | SDL_INIT_AUDIO) < 0) {
			printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());

			return ENGINE_INIT_ERROR;
		}

		// Initialize TTF
		if(TTF_Init() == -1) return ENGINE_INIT_ERROR;

		return 0;
	}
}