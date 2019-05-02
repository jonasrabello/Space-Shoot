#ifndef MANAGER_
#define MANAGER_

namespace core {

	class Manager {
	
	public:
		Manager();
		~Manager();

		virtual bool Init() = 0;
		virtual bool Update() = 0;
		virtual void Draw() const = 0;
		virtual bool Shutdown() = 0;
	};
}
#endif // !MANAGER_

