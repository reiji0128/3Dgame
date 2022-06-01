#pragma once
#include "EnemyStateBase.h"

class EnemyStateHit : public EnemyStateBase
{
public:
	EnemyStateHit();

	~EnemyStateHit();

	EnemyState Update(class EnemyActor* owner, float delotaTime)override;

	void Enter(class EnemyActor* owner, float deltaTime)override;

	const float knokBackSpeed = 500.0f;     // �_���[�W�m�b�N�o�b�N���x
	const float knokBackBrake = 0.92f;      // �_���[�W�m�b�N�o�b�N������

	SkeletalMeshComponent* mSkelMeshComp;
};