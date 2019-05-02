#include <iostream>
#include <thread>
#include <SDL_image.h>
#include "SystemManager.h"
#include "MainScene.h"

MainScene::MainScene() :
	obj(0),
	gameOver(false)
{
}

MainScene::~MainScene() {
}

void MainScene::Init() {

	// Get singleton of input and window
	input = static_cast<Input*>(core::SystemManager::GetInstance()->GetSystem(core::SystemType::INPUT));
	window = static_cast<Window*>(core::SystemManager::GetInstance()->GetSystem(core::SystemType::WINDOW));

	// Get window and get its width and height
	SDL_GetWindowSize(window->GetWindow(), &windowWidth, &windowHeight); // Get Window size in pixels

	//Create renderer for window
	renderer = SDL_CreateRenderer(window->GetWindow(), -1, SDL_RENDERER_ACCELERATED);

	if (renderer) {
		//Initialize renderer color black
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
	}

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
	}

	// Initialize resources
	resources = new scene::Resources();
	resources->Init(renderer);

	// Insert one game object in the scene
	gameObjects.push_back(new scene::GameObject(0.5f, scene::GameObjectType::PLAYER, renderer, resources));
	gameObjects.push_back(new scene::GameObject(0.5f, scene::GameObjectType::NPC, renderer, resources));
	gameObjects.push_back(new scene::GameObject(0.5f, scene::GameObjectType::NPC, renderer, resources));

	//SetGameObject(obj, pos, speed, npc, back, limitBegin)

	// Set initial settings for friend ship
	obj = 0;
	size = gameObjects[obj]->GetRect();
	pos = Vec3(static_cast<float>((windowWidth - size.h)/2), static_cast<float>(windowHeight - size.h), 0.0f);
	SetGameObject(obj, pos, 15.0f, false, false, windowWidth, 0, "Player Health", {0,255,0,255}, 10, 60);
	timer.push_back(0);
	
	// Set initial settings for enemy ship
	obj++;
	pos = Vec3(0.0f, 0.0f, 0.0f);
	SetGameObject(obj, pos, 10.0f, true, false, (windowWidth / 2), 0, "Enemy 1 Health", { 255,0,0,255 }, 10, 90);
	timer.push_back(0);

	// Set initial settings for enemy ship
	obj++;
	size = gameObjects[obj]->GetRect();
	pos = Vec3(static_cast<float>(windowWidth - size.w - 1), 0.0f, 0.0f);
	SetGameObject(obj, pos, 10.0f, true, true, windowWidth, (windowWidth / 2), "Enemy 2 Health", { 0,0,255,255 }, 10, 120);
	timer.push_back(11);

	// Break gameObjects in two groups
	for (scene::GameObject* o : gameObjects) {
		if (o->GetNpc())
			npcObjects.push_back(o);		
		else 
			playerObjects.push_back(o);		
	}
}

void MainScene::Update() {

	for (int i = 0; i < gameObjects.size(); i++) {

		// Initialize the axis position
		x = 0;
		y = 0;
		z = 0;

		// To controle bullets spawn
		timer[i]++;

		// Get size of the object and current position
		SDL_Rect rect = gameObjects[i]->GetRect();

		// It is a NPC game object make its movement by random position
		if (gameObjects[i]->GetNpc()) {

			x = SetNpcPosition(rect, i);

			// Update bullets position		
			gameObjects[i]->UpdateBullets(windowHeight, playerObjects);

		}
		else {	// It is a Player the position is controlled by keyboard

			x = SetPlayerPosition(rect, i);

			// Update bullets position		
			gameObjects[i]->UpdateBullets(windowHeight, npcObjects);
		}

		// Update game object position
		gameObjects[i]->Update(Vec3(x, y, z));

		// Update pows
		gameObjects[i]->UpdatePows();
	}

	// Check if the game object is dead remove from screen
	for (int i = 0; i < gameObjects.size(); i++) {
		if (gameObjects[i]->IsDead()) {
			// If it is NPC remove from screen
			if (gameObjects[i]->GetNpc()) {
				gameObjects.erase(gameObjects.begin() + i);
				// Update npcObjects
				npcObjects.clear();
				for (scene::GameObject* o : gameObjects) {
					if (o->GetNpc())
						npcObjects.push_back(o);
				}
			}
			else {	// If it player set game over
				gameOver = true;
			}				
		}
	}

	// If just the player is on screen - Game Over
	if (gameObjects.size() == 1) gameOver = true;

	if (gameOver) {
		// Insert Game Over image
		gameObjects.push_back(new scene::GameObject(1.0f, scene::GameObjectType::GAME_OVER, renderer, resources));
		obj = gameObjects.size() - 1;
		size = gameObjects[obj]->GetRect();
		pos = Vec3(static_cast<float>((windowWidth - size.w) / 2), static_cast<float>((windowHeight - size.h) / 2), 0.0f);
		SetGameObject(obj, pos, 0.0f, false, false, windowWidth, 0, "", {0,0,0,0 }, 0, 0);
	}
}

int MainScene::SetNpcPosition(SDL_Rect rect, int obj) {
	
	int x = 0;

	if (!gameObjects[obj]->GetBack()) {
		// Check right border
		if ((rect.w + rect.x) < (gameObjects[obj]->GetRange() - gameObjects[obj]->GetSpeed())) {
			x = gameObjects[obj]->GetSpeed();
		}
		else {	// Set new range to movement		
			gameObjects[obj]->SetRange(rand() % (windowWidth / 2) + gameObjects[obj]->GetLimitBegin());
			gameObjects[obj]->SetBack(true);
		}
	}
	else {
		// Check left border
		if (rect.x > gameObjects[obj]->GetRange()) {
			x = gameObjects[obj]->GetSpeed() * -1.0f;
		}
		else {	// Set new range to movement
			gameObjects[obj]->SetRange(rand() % (windowWidth / 2) + gameObjects[obj]->GetLimitBegin());
			gameObjects[obj]->SetBack(false);
		}
	}

	// Spawn npc's ship bullet
	if (timer[obj] > 10.0f) {
		gameObjects[obj]->SpawnBullet(0.2f, scene::GameObjectType::NPC_BULLET, renderer, resources);
		timer[obj] = 0.0f;
	}

	return x;
}

int MainScene::SetPlayerPosition(SDL_Rect rect, int obj) {

	int x = 0;

	if (input->IsLeftPressed()) {
		// Check left border 
		if (rect.x > 0) {
			x = gameObjects[obj]->GetSpeed() * -1.0f;
		}
	}	 // Check right border
	else if (input->IsRightKeyPressed()) {
		if ((rect.w + rect.x) < (windowWidth - gameObjects[obj]->GetSpeed())) {
			x = gameObjects[obj]->GetSpeed();
		}
	}

	// Spaws player's ship bullet
	if (input->IsCtrlKeyPressed() && timer[obj] > 5.0f) {
		gameObjects[obj]->SpawnBullet(0.1f, scene::GameObjectType::PLAYER_BULLET, renderer, resources);
		timer[obj] = 0.0f;
	}

	return x;
}

void MainScene::Draw() {

	//Clear screen
	SDL_RenderClear(renderer);

	for (int i = 0; i < gameObjects.size(); i++) {

		// Draw the space ship
		gameObjects[i]->Draw();

		// Draw all bullets
		gameObjects[i]->DrawBullets();

		// Draw all pows
		gameObjects[i]->DrawPow();
	}

	//Update screen
	SDL_RenderPresent(renderer);
}

bool MainScene::Shutdown() {

	// Destroy Renderer
	SDL_DestroyRenderer(renderer);

	// Destroy resources
	delete resources;
	resources = nullptr;

	// Destroy game objects
	for (int i = 0; i < gameObjects.size(); i++) {
		delete gameObjects[i];
		gameObjects[i] = nullptr;			
		gameObjects.erase(gameObjects.begin() + i);
	}

	for (int i = 0; i < npcObjects.size(); i++) {
		npcObjects.erase(npcObjects.begin() + i);
	}

	for (int i = 0; i < playerObjects.size(); i++) {
		playerObjects.erase(playerObjects.begin() + i);
	}

	//Destroy window
	SDL_DestroyWindow(window->GetWindow());

	return true;
}

bool MainScene::GetGameOver() {
	return gameOver;
}

void MainScene::SetGameObject(int obj, Vec3 pos, float speed, bool npc, bool back, int range, 
	                          int limitBegin, std::string healtText, SDL_Color color, int x, int y) {
	gameObjects[obj]->SetPosition(pos);
	gameObjects[obj]->SetSpeed(speed);
	gameObjects[obj]->SetNpc(npc);					// Holds if the game object is a npc
	gameObjects[obj]->SetBack(back);				// Define if the game object start back to the begin position
	gameObjects[obj]->SetRange(range);				// Holds the range in the screen to movement
	gameObjects[obj]->SetStartLimit(limitBegin);	// Limit of any ship to start movement
	gameObjects[obj]->SetHealtText(healtText, color, x, y);	// Set text to display health of the game object
}
