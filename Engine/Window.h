#ifndef WINDOW_
#define WINDOW_

#include <thread>
#include "SDL.H"
#include "System.h"

#define WINDOW_INIT_ERROR		1

namespace core {

	class Window : public System {

	private:
		Window();
		~Window();

		// Static means public everywhere, so theres is just one m_instance
		// Unique_ptr is a smart pointer that destroys the object it points to when the unique_ptr goes out of scope
		static std::unique_ptr<Window> m_instance;
		
		// Because the destructor method is also private, it is necessary to call a default destructor for the unique_ptr
		friend std::default_delete<Window>;

		//The window we'll be rendering to
		SDL_Window* window = NULL;

		//The surface contained by the window
		//SDL_Surface* screenSurface = NULL;

	public:		

		int Init() override;
		SDL_Window* GetWindow();

		static Window* GetInstance() {
			if (m_instance.get() == nullptr) m_instance.reset(new Window());
			return m_instance.get();
		}

	};
}
#endif // !WINDOW_

