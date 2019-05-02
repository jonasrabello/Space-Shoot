#include <SDL_image.h>
#include "Resources.h"

namespace scene {

	Resources::Resources() {

	}

	Resources::~Resources() {

		SDL_FreeSurface(image[GameObjectType::PLAYER]);
		SDL_FreeSurface(image[GameObjectType::PLAYER_BULLET]);
		SDL_FreeSurface(image[GameObjectType::NPC]);
		SDL_FreeSurface(image[GameObjectType::NPC_BULLET]);
		SDL_FreeSurface(image[GameObjectType::GAME_OVER]);
		SDL_FreeSurface(image[GameObjectType::POW]);

		SDL_DestroyTexture(texture[GameObjectType::PLAYER]);
		SDL_DestroyTexture(texture[GameObjectType::PLAYER_BULLET]);
		SDL_DestroyTexture(texture[GameObjectType::NPC]);
		SDL_DestroyTexture(texture[GameObjectType::NPC_BULLET]);
		SDL_DestroyTexture(texture[GameObjectType::GAME_OVER]);
		SDL_DestroyTexture(texture[GameObjectType::POW]);

		Mix_FreeChunk(sound[GameObjectType::PLAYER]);
		Mix_FreeChunk(sound[GameObjectType::NPC]);
		Mix_CloseAudio();
	}

	void Resources::Init(SDL_Renderer* renderer) {

		// Set image
		image[GameObjectType::PLAYER] = IMG_Load("Images/friendspaceship.png");
		image[GameObjectType::PLAYER_BULLET] = IMG_Load("Images/friendbullet.png");
		image[GameObjectType::NPC] = IMG_Load("Images/enemyspaceship.png");
		image[GameObjectType::NPC_BULLET] = IMG_Load("Images/enemybullet.png");
		image[GameObjectType::GAME_OVER] = IMG_Load("Images/gameover.png");
		image[GameObjectType::POW] = IMG_Load("Images/pow.png");

		// Set texture
		texture[GameObjectType::PLAYER] = SDL_CreateTextureFromSurface(renderer, image[GameObjectType::PLAYER]);
		texture[GameObjectType::PLAYER_BULLET] = SDL_CreateTextureFromSurface(renderer, image[GameObjectType::PLAYER_BULLET]);
		texture[GameObjectType::NPC] = SDL_CreateTextureFromSurface(renderer, image[GameObjectType::NPC]);
		texture[GameObjectType::NPC_BULLET] = SDL_CreateTextureFromSurface(renderer, image[GameObjectType::NPC_BULLET]);
		texture[GameObjectType::GAME_OVER] = SDL_CreateTextureFromSurface(renderer, image[GameObjectType::GAME_OVER]);
		texture[GameObjectType::POW] = SDL_CreateTextureFromSurface(renderer, image[GameObjectType::POW]);

		// Initiliaze audio mixer
		Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);

		// Set sound
		sound[GameObjectType::PLAYER] = Mix_LoadWAV("Sounds/friendsound.wav");
		sound[GameObjectType::NPC] = Mix_LoadWAV("Sounds/enemysound.wav");
	
	}

	SDL_Surface * Resources::GetImage(GameObjectType type) {

		return image[type];
	}

	SDL_Texture * Resources::GetTexture(GameObjectType type) {

		return texture[type];
	}

	void Resources::PlaySound(GameObjectType type) {
		int channel = -1;
		int loops = 0;
		Mix_PlayChannel(channel, sound[type], loops);
	}
}