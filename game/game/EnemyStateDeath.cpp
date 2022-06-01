#include "EnemyStateDeath.h"

EnemyStateDeath::EnemyStateDeath()
{
}

EnemyStateDeath::~EnemyStateDeath()
{
}

EnemyState EnemyStateDeath::Update(EnemyActor* owner, float deltaTime)
{
	if (!mSkelMeshComp->IsPlaying())
	{
		owner->SetState(owner->EDead);
	}

	return EnemyState::STATE_DEATH;
}

void EnemyStateDeath::Enter(EnemyActor* owner, float deltaTime)
{
	owner->SetVelosity(Vector3::Zero);

	//���S��Ԃ̃A�j���[�V�����Đ�
	mSkelMeshComp = owner->GetSkeltalMeshComp();
	mSkelMeshComp->PlayAnimation(owner->GetAnim(EnemyState::STATE_DEATH));
}
