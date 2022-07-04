#pragma once
#include "PlayerStateBase.h"

class PlayerActor;

class PlayerStateJumpStart : public PlayerStateBase
{
public:
	PlayerStateJumpStart();
	~PlayerStateJumpStart();

	PlayerState Update(PlayerActor* owner, float deltaTime) override;
	void Enter(PlayerActor* owner, float deltaTime) override;

private:
	void JumpCalc(PlayerActor* owner, float deltaTime);

	const float mJumpPower = 13;

	SkeletalMeshComponent* mSkelComp;
};