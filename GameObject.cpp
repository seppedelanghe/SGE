

#include "GameObject.hpp"
#include "ECS/A/TextureManager.hpp"

GameObject::GameObject(const char* texturesheet)
{
	objTexture = TextureManager::LoadTexture(texturesheet);	       
		
	xpos = 0;
	ypos = 0;

}

GameObject::GameObject(const char* texturesheet, int x = 0, int y = 0)
{
	objTexture = TextureManager::LoadTexture(texturesheet);

	xpos = x;
	ypos = y;
}

void GameObject::Update()
{
	xpos++;
	ypos++;

	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;


	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w * 2;
	destRect.h = srcRect.h * 2;
	
}

void GameObject::Render()
{
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}
