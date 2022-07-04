#include "ButtonSprite.h"
#include "SpriteComponent.h"
#include "Texture.h"
#include "Renderer.h"
#include "Game.h"

ButtonSprite::ButtonSprite()
	:Actor(Tag::UI)
{
	// ポジション・スケールのセット
	SetPosition(Vector3(0.0f, 100.0f, 0.0f));
	SetScale(1.0);
	mSprite = new SpriteComponent(this);
	Texture* tex = RENDERER->GetTexture("Assets/UI/Health.png");
	mSprite->SetTexture(tex);

	mState = State::EInactive;
}

ButtonSprite::~ButtonSprite()
{
}
