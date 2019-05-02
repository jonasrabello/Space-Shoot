#ifndef RESOURCES_
#define RESOURCES_
#include <map>
#include <SDL.H>
#include "SDL_mixer.h"

namespace scene {

	enum class GameObjectType : unsigned __int8 {    // unsigne  integer 1 byte
		PLAYER,
		PLAYER_BULLET,
		NPC,
		NPC_BULLET,
		GAME_OVER,
		POW
	};

	class Resources {
	private:
		std::map<GameObjectType, SDL_Surface*> image;
		std::map<GameObjectType, SDL_Texture*> texture;
		std::map<GameObjectType, Mix_Chunk*> sound;
	public:
		Resources();
		~Resources();
		void Init(SDL_Renderer* renderer);
		SDL_Surface* GetImage(GameObjectType type);
		SDL_Texture* GetTexture(GameObjectType type);
		void PlaySound(GameObjectType type);
	};
}
#endif // !RESOURCES_



