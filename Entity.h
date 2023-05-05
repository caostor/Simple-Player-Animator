#pragma once
#include <SDL.h>
#include <string>
#include <vector>

class Entity
{
public:
	Entity(SDL_Renderer* rrenderer);
	int Move(SDL_Point move);
	int Update();
	int SetAnimator(std::string sprite_sheet_path, int total_frame, int row_total, float speed);
	int SetAnimationSpeed(float speed);
	int SwitchRow(int row);
	SDL_Texture* sprite_sheet;
	SDL_Renderer* renderer = NULL;
	int FRAME_MAXIMUM = 0;
	int CURRENT_FRAME = 0;
	SDL_Point Position = { 0, 0 };
	
private:
	float animationSpeed = 1;
	SDL_Point move = { 0, 0 };
	int CURRENT_ROW = 0;
	int ROW_MAXIMUM = 0;
	int SPRITE_WIDTH = 48;
	int SPRITE_HEIGHT = 48;
	bool hasAnimation = false;
};

