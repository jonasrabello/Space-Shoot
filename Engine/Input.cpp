#include <iostream>

#include "Input.h"

namespace core {

	// Initialize the m_instance
	//Input* Input::m_instance = nullptr;
	std::unique_ptr<Input> Input::m_instance = nullptr;

	// initialize System because it needs ads base class
	Input::Input() : System(SystemType::INPUT),
		quitRequested(false), leftKeyPressed(false), rightKeyPressed(false),
		upKeyPressed(false), downKeyPressed(false), ctrlKeyPressed(false)
	{   
		// Get event handler
		SDL_PollEvent(&e);
	}

	Input::~Input() {
	}

	void Input::Update() {

		//Handle events on queue
		while (SDL_PollEvent(&e) != 0) {

			//User requests quit
			switch (e.type) {
			case SDL_QUIT:
				quitRequested = true;
				break;
			case SDL_KEYDOWN:
				switch (e.key.keysym.sym) {
				case SDLK_ESCAPE:
					quitRequested = true;
					break;
				case SDLK_LEFT:
					leftKeyPressed = true;
					break;
				case SDLK_RIGHT:
					rightKeyPressed = true;
					break;
				case SDLK_UP:
					upKeyPressed = true;
					break;
				case SDLK_LCTRL:
					ctrlKeyPressed = true;
					break;
				case SDLK_DOWN:
					downKeyPressed = true;
					break;
				}
				break;
			case SDL_KEYUP:
				switch (e.key.keysym.sym) {
				case SDLK_LEFT:
					leftKeyPressed = false;
					break;
				case SDLK_RIGHT:
					rightKeyPressed = false;
					break;
				case SDLK_UP:
					upKeyPressed = false;
					break;
				case SDLK_LCTRL:
					ctrlKeyPressed = false;
					break;
				case SDLK_DOWN:
					downKeyPressed = false;
					break;
				}
				break;
			}
		}
	}

	int Input::Init() {
		return 0;
	}

	bool Input::QuitRequested() {
		return quitRequested;
	}

	SDL_Event Input::GetHandler() {
		return e;
	}
}