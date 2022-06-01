#pragma once
#include "EnemyActor.h"

const float nearLength = 250.0f;   //�ǐՒ��~��(�U���Ɉڍs)
const float trackingRange = 500.0f; // �ǐՋ���
const float waitTime = 2.0f;       // �ҋ@����

class EnemyStateBase
{
public:
	EnemyStateBase()
		:mStateTimer(0.0f) {};

	virtual ~EnemyStateBase() {};

	virtual EnemyState Update(class EnemyActor* owner, float deltaTime) = 0;

	virtual void Enter(class EnemyActor* owner, float deltaTime) {};

protected:
	// �X�e�[�g���̌o�ߎ����𑪂�^�C�}�[
	float mStateTimer;
};