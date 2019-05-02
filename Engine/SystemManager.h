#ifndef SYSTEMMANAGER_
#define SYSTEMMANAGER_

#include <vector>
#include <thread>
#include "Manager.h"
#include "System.h"

namespace core {

	//template<class T>
	//class  Singleton {
	//public:
	//	 static 

	//private:

	//};

	class SystemManager : public Manager {

	private:
		SystemManager();
		~SystemManager();

		std::vector<System*> systems;

		// Static means public everywhere, so theres is just one m_instance
		// Unique_ptr is a smart pointer that destroys the object it points to when the unique_ptr goes out of scope
		static std::unique_ptr<SystemManager> m_instance;

		// Because the destructor method is also private, it is necessary to call a default destructor for the unique_ptr
		friend std::default_delete<SystemManager>;

	public:

		System* GetSystem(SystemType type);

		bool Init() override; 
		bool Update() override;
		void Draw() const  override;
		bool Shutdown() override;
		
		static SystemManager* GetInstance() {

			// Reset() sets the new address
			if (m_instance.get() == nullptr) m_instance.reset(new SystemManager());
			return m_instance.get();
		}
	};
}
#endif // !SYSTEMMANAGER_
