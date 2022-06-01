#pragma once
#include "PlayerActor.h"

class PlayerStateBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	PlayerStateBase() {};

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~PlayerStateBase() {};

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="owner">�v���C���[�̃|�C���^</param>
	/// <param name="deltaTime">1�t���[���̌o�ߎ���</param>
	/// <returns>�v���C���[�̏��</returns>
	virtual PlayerState Update(class PlayerActor* owner, float deltaTime) = 0;

	/// <summary>
	/// ��Ԃ��ڍs�����Ƃ���1�x�������鏈��
	/// </summary>
	/// <param name="owner">�v���C���[�̃|�C���^</param>
	/// <param name="deltaTime">1�t���[���̌o�ߎ���</param>
	virtual void Enter(class PlayerActor* owner, float deltaTime) {};

protected:

};