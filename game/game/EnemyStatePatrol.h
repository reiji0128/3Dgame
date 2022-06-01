#pragma once
#include "EnemyStateBase.h"

class EnemyStatePatrol : public EnemyStateBase
{
public:
	EnemyStatePatrol();

	~EnemyStatePatrol();

	EnemyState Update(class EnemyActor* owner, float deltaTime) override;

	void Enter(class EnemyActor* owner, float deltaTime) override;

private:
	const float patrolSpeed = 100.0f;   //�p�g���[�����̃X�s�[�h
	const float rotateSpeed = 45.0f;    // ��]�X�s�[�h

	Vector3 enemyToPlayerVec;			// �G�l�~�[����v���C���[�Ɍ������x�N�g��
	Vector3 mAimVec;                    // �ڕW��]����
	bool mRotateNow;                    // ��]�����H

	SkeletalMeshComponent* mSkelMeshComp;
};