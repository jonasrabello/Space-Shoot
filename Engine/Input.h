#ifndef INPUT_
#define INPUT_

#include <thread>
#include "SDL.h"
#include "System.h"

namespace core {
	class Input : public System {

	private:
		Input();
		~Input();

		//Event handler
		SDL_Event e;

		// Static means public everywhere, so theres is just one m_instance
		// Unique_ptr is a smart pointer that destroys the object it points to when the unique_ptr goes out of scope
		static std::unique_ptr<Input> m_instance;

		// Because the destructor method is also private, it is necessary to call a default destructor for the unique_ptr
		friend std::default_delete<Input>;

		bool quitRequested;

		bool leftKeyPressed;
		bool rightKeyPressed;		
		bool ctrlKeyPressed;
		bool upKeyPressed;
		bool downKeyPressed;		

	public:	

		void Update() override;

		int Init() override;

		// Reset() sets the new address
		static Input* GetInstance() {
			if (m_instance.get() == nullptr) m_instance.reset(new Input());
			return m_instance.get();
		}

		//inline bool QuitRequested(return quitRequested;) // with inline the implementantion is iserted here
		bool QuitRequested();

		SDL_Event GetHandler();

		// const here means this method does not change anything in this class
		inline bool IsLeftPressed() const { return leftKeyPressed; };
		inline bool IsRightKeyPressed() const { return rightKeyPressed; };
		inline bool IsUpKeyPressed() const { return upKeyPressed; };
		inline bool IsDownKeyPressed() const { return downKeyPressed; };
		inline bool IsCtrlKeyPressed() const { return ctrlKeyPressed; };
	};

}
#endif // !INPUT_
