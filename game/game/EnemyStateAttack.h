#pragma once
#include "EnemyStateBase.h"

class EnemyStateAttack : public EnemyStateBase
{
public:
	EnemyStateAttack();
	~EnemyStateAttack();

	EnemyState Update(class EnemyActor* owner, float deltaTime)override;
	void Enter(class EnemyActor* owner, float deltaTime)override;

private:
	void Attack(class EnemyActor* owner, float deltaTime);

	int mRandomNum;

	const float retrackingRange = 250.0f;      // �U��������ǐՂɕς�鋗��
	const float attackOffsetTime = 0.5f;       // �U���A�j���J�n���Ă���U�����肪��������܂ł̒�������

	SkeletalMeshComponent* mSkelMeshComp;
};