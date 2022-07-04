#pragma once
#include "PlayerStateBase.h"

class PlayerActor;

class PlayerStateJumpEnd : public PlayerStateBase
{
public:
	PlayerStateJumpEnd();
	~PlayerStateJumpEnd();

	PlayerState Update(class PlayerActor* owner, float deltaTime) override;
	void Enter(class PlayerActor* owner, float deltaTime) override;

private:
	// スケルタルメッシュクラスのポインタ
	SkeletalMeshComponent* mSkelComp;
};