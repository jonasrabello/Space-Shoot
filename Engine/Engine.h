#ifndef ENGINE_
#define ENGINE_

#include "SDL.H"
#include "Window.h"
#include "Input.h"
#include <vector>

#define ENGINE_INIT_ERROR		1
#define ENGINE_SHUTDOWN_ERROR	2

namespace scene {
	class Scene;
}

namespace core {

	class Engine {

	private:
		bool isRunning;
		int gameOverTimer;

		unsigned int frameRate;		// Frames / second

		std::vector<class Manager*> managers;
		
		scene::Scene *mainScene;	// mainScene = nullptr first type of initialization	

		Window* window;				// Window to contain a surface and display the game objects

		Input* input;				// Input to control the keyboard input 

		void Update();
		void Draw() const;
		int Run();
		int ShutDown();	
		int SdlInit();

	public:
		Engine(scene::Scene *scene_);
		~Engine();

		int Init();		
	};
}
#endif // !ENGINE_