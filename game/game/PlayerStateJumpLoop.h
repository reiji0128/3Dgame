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

	// �d��
	const float mGravity = -10.0f;
	const float mMaxFallVelocity = -1000.0f;
	const float mMoveSpeed = 100.0f;
	const float mMaxMoveSpeed = 200.0f;

	// �v���C���[�̑O���x�N�g��
	Vector3 mCharaForwardVec;

	// �ڕW��]����
	Vector3 mRotationTargetDir;

	// ��]����
	bool mRotateNow;

	SkeletalMeshComponent* mSkelComp;
};