#pragma once
#include "Actor.h"

class SpriteComponent;

class ButtonSprite : public Actor
{
public:
	ButtonSprite();
	~ButtonSprite();

private:
	// �X�v���C�g�R���|�[�l���g
	SpriteComponent* mSprite;
};