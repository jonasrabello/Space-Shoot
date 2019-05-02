#ifndef SYSTEM_
#define SYSTEM_

namespace core {

	enum class SystemType : unsigned __int8 {    // unsigne  integer 1 byte
		WINDOW,   // this starts in 0, however WINDOW = 10 starts then in 10
		INPUT,
		TOTAL_SYSTEMS
	};

	class System {

	protected:
		

	public:
		const SystemType type;
		System(SystemType type_);
		virtual ~System();

		virtual int Init();
		virtual void Update();
		virtual void Draw() const;
		virtual bool Shutdown();
		virtual SystemType GetType();
	};
}
#endif // !SYSTEM_
