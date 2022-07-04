#pragma once
#include "PlayerStateBase.h"

class PlayerActor;

class PlayerStateJumpLoop : public PlayerStateBase
{
public:
	PlayerStateJumpLoop();
	~PlayerStateJumpLoop();

	PlayerState Update(PlayerActor* owner, float deltaTime) override;
	void Enter(PlayerActor* owner, float deltaTime) override;

private:
	void JumpMoveCalc(PlayerActor* owner, float deltaTime);

	void RotateActor();

	// 重力
	const float mGravity = -10.0f;
	const float mMaxFallVelocity = -1000.0f;
	const float mMoveSpeed = 100.0f;
	const float mMaxMoveSpeed = 200.0f;

	// プレイヤーの前方ベクトル
	Vector3 mCharaForwardVec;

	// 目標回転方向
	Vector3 mRotationTargetDir;

	// 回転中か
	bool mRotateNow;

	SkeletalMeshComponent* mSkelComp;
};