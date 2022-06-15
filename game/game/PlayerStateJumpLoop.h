#pragma once
#include "PlayerStateBase.h"

class PlayerStateJumpLoop : public PlayerStateBase
{
public:
	PlayerStateJumpLoop();
	~PlayerStateJumpLoop();

	PlayerState Update(class PlayerActor* owner, float deltaTime) override;

	/// <summary>
	/// ��Ԃ��ڍs�����Ƃ���1�x�������鏈��
	/// </summary>
	/// <param name="owner">�v���C���[�̃|�C���^</param>
	/// <param name="deltaTime">1�t���[���̌o�ߎ���</param>
	void Enter(class PlayerActor* owner, float deltaTime) override;

private:
	SkeletalMeshComponent* mSkelComp;
};