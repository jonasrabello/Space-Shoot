#ifndef MAINSCENE_
#define MAINSCENE_

#include "Vector.h"
#include "Input.h"
#include "Window.h"
#include "Engine.h"
#include <Scene.h>
#include <Resources.h>

using namespace core;

namespace scene {
	class Scene;
}

class MainScene : public scene::Scene {

private:
	std::vector<scene::GameObject*> gameObjects;
	std::vector<scene::GameObject*> npcObjects;
	std::vector<scene::GameObject*> playerObjects;
	std::vector<int> timer;

	scene::Resources* resources;

	int windowWidth;
	int windowHeight;	
	int obj;	
	SDL_Rect size;
	Vec3 pos;
	Window* window;
	Input* input;
	float x;
	float y;
	float z;
	bool gameOver;

	//The window renderer
	SDL_Renderer* renderer = NULL;

public:
	MainScene();
	virtual ~MainScene();

	void Init() override;
	void Update() override;
	void Draw() override;
	bool Shutdown() override;
	bool GetGameOver();
	void SetGameObject(int obj,  Vec3 pos, float speed, bool npc, bool back, int range, int limitBegin,
					   std::string healtText, SDL_Color color, int x, int y);
	int SetNpcPosition(SDL_Rect rect, int obj);
	int SetPlayerPosition(SDL_Rect rect, int obj);
};
#endif // !MAINSCENE_




