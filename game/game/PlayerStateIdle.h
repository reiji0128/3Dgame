#pragma once
#include "PlayerStateBase.h"

class PlayerStateIdle : public PlayerStateBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	PlayerStateIdle();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~PlayerStateIdle();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="owner">�v���C���[�̃|�C���^</param>
	/// <param name="deltaTime">1�t���[���̌o�ߎ���</param>
	/// <returns></returns>
	PlayerState Update(class PlayerActor* owner, float deltaTime) override;

	/// <summary>
	/// ��Ԃ��ڍs�����Ƃ���1�x�������鏈��
	/// </summary>
	/// <param name="owner">�v���C���[�̃|�C���^</param>
	/// <param name="deltaTime">1�t���[���̌o�ߎ���</param>
	void Enter(class PlayerActor* owner, float deltaTime) override;

private:
	void Fire(class PlayerActor* owner, float deltaTime);

	SkeletalMeshComponent* mSkelComp;
};