#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include "GameObject.h"

namespace scene {

	GameObject::GameObject(float scale, GameObjectType type, SDL_Renderer* renderer, Resources* resources) :
		scale(scale),
		renderer(renderer),
		resources(resources),
		type(type),
		speedBulletNpc(15.0f),
		speedBulletPlayer(25.0f),
		health(10)
	{
		
	}

	GameObject::~GameObject() {	

		for (int i = 0; i < bullets.size(); i++) {
			delete bullets[i];
			bullets[i] = nullptr;						
			bullets.erase(bullets.begin() + i);
		}

		for (int i = 0; i < pows.size(); i++) {
			delete pows[i];
			pows[i] = nullptr;
			pows.erase(pows.begin() + i);
		}
	}

	void GameObject::Init() {

	}

	void GameObject::Update(const Vec3 pos_) {
		// Update game object position
		pos += pos_;
	}

	void GameObject::Draw() {

		// Render health to screen		
		DisplayHealth();

		// Render texture to screen
		SDL_RenderCopy(renderer, resources->GetTexture(type), NULL, &GetRect());
	}

	bool GameObject::Shutdown() {
		return true;
	}

	void GameObject::SetPosition(Vec3 pos_) {
		// Set game object position
		pos = pos_;
	}

	SDL_Rect GameObject::GetRect() {
		// Set information to the rect of the game object and return to it
		rect.h = resources->GetImage(type)->h*scale;
		rect.w = resources->GetImage(type)->w*scale;
		rect.x = static_cast<int>(pos.x);
		rect.y = static_cast<int>(pos.y);

		return rect;
	}
	void GameObject::SetScale(float scale_) {
		scale = scale_;
	}
	float GameObject::GetSpeed() {
		return speed;
	}
	void GameObject::SetSpeed(float speed_) {
		speed = speed_;
	}
	int GameObject::GetLimitBegin() {
		return limitBegin;
	}
	void GameObject::SetStartLimit(int limitBegin_) {
		limitBegin = limitBegin_;
	}
	bool GameObject::GetNpc() {
		return npc;
	}
	void GameObject::SetNpc(float npc_) {
		npc = npc_;
	}
	bool GameObject::GetBack() {
		return back;
	}
	void GameObject::SetBack(bool back_) {
		back = back_;
	}
	int GameObject::GetRange() {
		return range;
	}
	bool GameObject::IsDead() {
		if (health <= 0) return true;
		return false;
	}
	void GameObject::SetRange(int range_) {
		range = range_;
	}

	void GameObject::SpawnBullet(float scale, GameObjectType type, SDL_Renderer* renderer, Resources* resources) {

		SDL_Rect r = GetRect();

		GameObject* bullet = new GameObject(scale, type, renderer, resources);
	
		// Set start position X of the bullet according to the ship (Center o the ship and the bullet)
		float x = r.x + (r.w / 2) - (bullet->GetRect().w / 2);
		
		float y = 0.0f;
		 
		// Set start position Y of the bullet according to the ship (Top of the ships)
		if(npc) {
			y = r.y + r.h - 5.0f; // 0.5f is just an adjustment	
		}
		else {
			y = r.y - bullet->GetRect().h;
		}
		
		// Insert a bullet on the vector
		bullet->SetPosition(Vec3(x, y, 0.0f));

		// Set bullet speed
		if (npc)
			bullet->SetSpeed(speedBulletNpc);
		else
			bullet->SetSpeed(speedBulletPlayer);

		// Insert a bullet 
		bullets.push_back(bullet);
	}

	void GameObject::SpawnPow(float scale, GameObjectType type, SDL_Renderer * renderer, Resources * resources) {
		
		SDL_Rect r = GetRect();

		GameObject* p = new GameObject(scale, type, renderer, resources);

		// Set start position X of the bullet according to the ship (Center o the ship and the bullet)
		float x = r.x + (r.w / 2) - (p->GetRect().w / 2);

		float y = 0.0f;

		// Set start position Y of the bullet according to the ship (Top of the ships)
		if (npc) {
			y = r.y + r.h - 5.0f; // 0.5f is just an adjustment	
		}
		else {
			y = r.y - p->GetRect().h;
		}

		// Insert a bullet on the vector
		p->SetPosition(Vec3(x, y, 0.0f));

		// Insert a bullet 
		pows.push_back(p);	
	}

	void GameObject::DrawBullets() {

		for (GameObject* b : bullets) {
			b->Draw();
		}
	}

	void GameObject::DrawPow() {

		for (GameObject* p : pows) {
			p->Draw();
		}
	}

	int GameObject::UpdatePow() {		
		return timer++;
	}

	void GameObject::UpdatePows() {
		for (int i = 0; i < pows.size(); i++) {
			if (pows[i]->UpdatePow() > 5) {
				// Remove pow from scene
				delete pows[i];
				pows[i] = nullptr;
				pows.erase(pows.begin() + i);
			}
		}
	}

	void GameObject::UpdateBullets(int windowHeight, std::vector<GameObject*> gameObjects) {

		// Declare game object coordenates
		float x;
		float y;
		float z;
		float m;
		bool erase;
		GameObject* obj = NULL;

		for (int i = 0; i < bullets.size(); i++) {

			// Initialize the axis position
			x = 0;
			y = 0;
			z = 0;

			erase = true;

			obj = CheckCollision(npc, gameObjects, bullets[i]);
			
			if(obj) {
				resources->PlaySound(type);
				obj->SpawnPow(0.8f, scene::GameObjectType::POW, renderer, resources);
			} else {

				if (npc) {

					// Check bottom border
					if ((bullets[i]->GetRect().h + bullets[i]->GetRect().y) <
						(windowHeight - bullets[i]->GetSpeed())) {

						// Multiplier of the direction velocity
						m = 1.0f;

						// Set not erase
						erase = false;
					}

				}
				else {

					// Check up border
					if ((bullets[i]->GetRect().y - bullets[i]->GetSpeed()) > 0) {

						// Multiplier of the direction velocity
						m = -1.0f;

						// Set not erase
						erase = false;
					}
				}
			}

			// Test if the bullet is out of bounds
			if (erase) {
				// Remove bullet from scene
				delete bullets[i];
				bullets[i] = nullptr;
				bullets.erase(bullets.begin() + i); 
			}
			else {

				// Set y to update position
				y = bullets[i]->GetSpeed() * m;

				// Update bullet position
				bullets[i]->Update(Vec3(x, y, z));
			}
		}
	}

	GameObject* GameObject::CheckCollision(bool npc, std::vector<GameObject*> gameObjects, GameObject * bullet) {

		SDL_Rect br = bullet->GetRect();

		for (GameObject* o : gameObjects) {

			SDL_Rect or = o->GetRect();
			
			if (npc) {
				if ((br.x >= or.x && br.x <= (or.x + or.w)) && ((br.y + br.h) >= or.y)) {
					o->UpdateHealth();
					return o;
				}
			}
			else if ((br.x >= or .x && br.x <= (or .x + or .w)) && (br.y <= (or.y + or.h))) {
				o->UpdateHealth();
				return o;
			}
		}
		return NULL;
	}

	void GameObject::UpdateHealth() {

		health--;
	}

	void GameObject::SetHealtText(std::string healtText_, SDL_Color color_, int x_, int y_) {
		healtText = healtText_;
		color = color_;
		x = x_;
		y = y_;
	}

	void GameObject::DisplayHealth() {

		SDL_Rect rect;

		if (x == 0) return;

		std::string hc = healtText + ": " + std::to_string(health);

		// Get font
		TTF_Font* font = TTF_OpenFont("Fonts/arial.ttf", 20);

		if (!font) return;

		// Create a surface
		SDL_Surface* image = TTF_RenderText_Solid(font, hc.c_str(), color);
		
		TTF_CloseFont(font);		

		if (!image) return;

		// Create texture;
		SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);

		SDL_FreeSurface(image);

		if (!texture) return;		

		// Assign width and hight
		SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);

		// Set text position
		rect.x = x;
		rect.y = y;

		// Render on screen
		SDL_RenderCopy(renderer, texture, NULL, &rect);

		// Clean the memory
		SDL_DestroyTexture(texture);	
	}
}
