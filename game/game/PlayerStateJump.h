#pragma once
#include "PlayerStateBase.h"

class PlayerStateJump : public PlayerStateBase
{
public:
	PlayerStateJump();

	~PlayerStateJump();

	PlayerState Update(class PlayerActor* owner, float deltaTime) override;
};