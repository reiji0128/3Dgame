#pragma once
#include "Actor.h"

class ButtonSprite;
class PlayerActor;
class SwitchActor;


class PlaySceneUI : public Actor
{
public:
	PlaySceneUI(PlayerActor* player,SwitchActor* switchActor);
	~PlaySceneUI();

	void UpdateActor(float deltaTime) override;

private:
	ButtonSprite* mButtonSprite;

	PlayerActor* mPlayer;

	SwitchActor* mSwitch;
};