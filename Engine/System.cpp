#include "System.h"

namespace core {

	System::System(SystemType type_) : type (type_)  {

	}
	
	System::~System() {
	}

	int System::Init() {
		return 0;
	}
	void System::Update() {

	}
	void System::Draw() const {

	}
	bool System::Shutdown() {
		return true;
	}

	SystemType System::GetType() {
		return type;
	}

}
