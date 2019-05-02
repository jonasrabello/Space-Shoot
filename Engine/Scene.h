#ifndef SCENE_
#define SCENE_

#include <vector>
#include "GameObject.h"

namespace scene {

	class Scene {

	private:
		bool gameOver;
		std::vector<GameObject*> gameObjects;

	public:
		Scene();
		virtual ~Scene();

		virtual void Init();
		virtual void Update();
		virtual void Draw();
		virtual bool Shutdown();
		virtual bool GetGameOver();
	};

}
#endif // !SCENE_
