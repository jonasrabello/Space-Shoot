#include "SystemManager.h"
#include "Input.h"
#include "Window.h"

namespace core {

	// Initialize the m_instance
	std::unique_ptr<SystemManager> SystemManager::m_instance(nullptr);

	SystemManager::SystemManager() {

		systems.push_back(core::Input::GetInstance());
		systems.push_back(core::Window::GetInstance());

	}

	SystemManager::~SystemManager() {

		// Cleaning
		for (System* s : systems) {
			s = nullptr;
			delete s;
		}
	}

	// TODO: Another template GetSystem
	System * SystemManager::GetSystem(SystemType type) {

		for (System* s : systems) {
			if (s->GetType() == type) return s;
		}

		return nullptr;
	}

	bool SystemManager::Init() {

		//for (int i = 0; i < (int) SystemType::TOTAL_SYSTEMS; i++) {

		//}

		for (System* s : systems) {
			if (s->Init()) {
				return false;
			}
		}

		return true;
	}

	bool SystemManager::Update() {

		return true;
	}

	void SystemManager::Draw() const {

	}

    bool SystemManager::Shutdown() {

		for (System* s : systems) {
			if (s->Shutdown()) {
				return false;
			}
		}

		return true;
	}
}