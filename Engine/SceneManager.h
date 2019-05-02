#ifndef SCENEMANAGER_
#define SCENEMANAGER_

#include <vector>
#include "Manager.h"

namespace scene {
	class Scene;
}

namespace core {

	class SceneManager : public Manager  {

	private:
		std::vector<scene::Scene*> scenes;

	public:
		SceneManager();
		~SceneManager();
	};
}
#endif // !SCENEMANAGER_

