#ifndef GAMEOBJECT_
#define GAMEOBJECT_

#include "SDL.H"
#include "Resources.h"
#include <string>
#include <vector>
#include "Vector.h"

namespace scene {

	class GameObject {

	private:
		GameObjectType type;
		Resources* resources;
		SDL_Renderer* renderer;
		Vec3 pos;
		SDL_Rect rect;
		std::vector<GameObject*> bullets;
		std::vector<GameObject*> pows;
		int limitBegin;
		float scale;
		float speed;
		bool npc;
		bool back;
		int range;
		float speedBulletNpc;
		float speedBulletPlayer;
		int health;
		int timer;
		std::string healtText;
		SDL_Color color;
		int x;
		int y;

	public:
		GameObject(float scale, GameObjectType type, SDL_Renderer* renderer, Resources* resources);
		~GameObject();

		void Init();
		void Update(const Vec3 pos_);
		void Draw();
		bool Shutdown();

		void SetPosition(Vec3 pos_);		
		SDL_Rect GetRect();
		void SetScale(float scale_);
		float GetSpeed();
		void SetSpeed(float speed_);
		int GetLimitBegin();
		void SetStartLimit(int limitBegin_);
		bool GetNpc();
		void SetNpc(float npc_);
		bool GetBack();
		void SetBack(bool back_);
		int GetRange();
		bool IsDead();
		void SetRange(int range_);
		void SpawnBullet(float scale, GameObjectType type, SDL_Renderer* renderer, Resources* resources);
		void SpawnPow(float scale, GameObjectType type, SDL_Renderer* renderer, Resources* resources);
		void DrawBullets();
		void UpdateBullets(int windowHeight, std::vector<GameObject*> gameObjects);
		GameObject* CheckCollision(bool npc, std::vector<GameObject*> objects, GameObject* bullet);
		void UpdateHealth();
		void SetHealtText(std::string healtText_, SDL_Color color_, int x_, int y_);
		void DisplayHealth();
		void DrawPow();
		int UpdatePow();
		void UpdatePows();
	};
}
#endif // GAMEOBJECT_
