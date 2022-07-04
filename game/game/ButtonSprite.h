#pragma once
#include "Actor.h"

class SpriteComponent;

class ButtonSprite : public Actor
{
public:
	ButtonSprite();
	~ButtonSprite();

private:
	// スプライトコンポーネント
	SpriteComponent* mSprite;
};