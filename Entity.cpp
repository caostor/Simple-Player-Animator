#include "Entity.h"
#include <SDL_image.h>

Entity::Entity(SDL_Renderer* rrenderer)
{
	renderer = rrenderer;
}

int Entity::Move(SDL_Point movew)
{
	move.x += movew.x;
	move.y += movew.y;

	return 0;
}

Uint32 Update_Animation(Uint32 interval, void* param)
{
    Entity* entity = static_cast<Entity*>(param);

    entity->CURRENT_FRAME = (entity->CURRENT_FRAME + 1) % entity->FRAME_MAXIMUM;

    return interval;
}

int Entity::Update()
{
    Position.x += move.x;
    Position.y += move.y;

    if (hasAnimation)
    {
        static Uint32 timer_id = SDL_AddTimer(100 / animationSpeed, Update_Animation, this);

        SDL_Rect srcRect = { CURRENT_FRAME * SPRITE_WIDTH, CURRENT_ROW * SPRITE_HEIGHT, SPRITE_WIDTH, SPRITE_HEIGHT};
        SDL_Rect destRect = { Position.x, Position.y, SPRITE_WIDTH, SPRITE_HEIGHT };

        SDL_RenderCopy(renderer, sprite_sheet, &srcRect, &destRect);
    }
    else
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_Rect body = {Position.x, Position.y, 50, 50};
        SDL_RenderFillRect(renderer, &body);
    }

    move.x = 0;
    move.y = 0;

    return 0;
}

int Entity::SetAnimation(std::string path, int total_frame, int row_total, float speed)
{
	SDL_Surface* surface = IMG_Load(&path[0]);
	sprite_sheet = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
    FRAME_MAXIMUM = total_frame;
	hasAnimation = true;
    ROW_MAXIMUM = row_total;
    animationSpeed = speed;

	return 0;
}

int Entity::SetAnimationSpeed(float speed)
{
    animationSpeed = speed;

    return 0;
}

int Entity::SwitchRow(int row)
{
    if (row <= ROW_MAXIMUM)
        CURRENT_ROW = row;

    return 0;
}
