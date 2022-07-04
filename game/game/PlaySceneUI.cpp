#include "PlaySceneUI.h"
#include "ButtonSprite.h"
#include "PlayerActor.h"
#include "SwitchActor.h"

PlaySceneUI::PlaySceneUI(PlayerActor* player, SwitchActor* switchActor)
	:Actor(Tag::UI)
{
	mButtonSprite = new ButtonSprite;
	mPlayer = player;
	mSwitch = switchActor;
}

PlaySceneUI::~PlaySceneUI()
{
}

void PlaySceneUI::UpdateActor(float deltaTime)
{
	if (mPlayer->GetHitLight())
	{
		mButtonSprite->SetState(State::EActive);
	}
	mButtonSprite->SetState(State::EInactive);
}
