#include "EnemyStateIdle.h"
#include "Game.h"

EnemyStateIdle::EnemyStateIdle()
{
}

EnemyStateIdle::~EnemyStateIdle()
{
}

EnemyState EnemyStateIdle::Update(EnemyActor* owner, float deltaTime)
{
	mStateTimer -= deltaTime;

	// �v���C���[�ʒu���
	Vector3 playerPos = GAMEINSTANCE.GetFirstActor(Tag::Player)->GetPosition();
	Vector3 mPosition = owner->GetPosition();
	Vector3 enemyToPlayerVec = playerPos - mPosition;

	float length = enemyToPlayerVec.Length();

	//�ǐՂ��Ȃ������܂ŋ߂Â����Ƃ��ɍU���Ɉڍs
	if (length < nearLength)
	{
		return EnemyState::STATE_ATTACK;
	}

	if (mStateTimer < 0.0f)
	{
		return EnemyState::STATE_PATROL;
	}

	if (owner->GetIsHitTrig())
	{
		return EnemyState::STATE_DEATH;
	}

	return EnemyState::STATE_IDLE;
}

void EnemyStateIdle::Enter(EnemyActor* owner, float deltaTime)
{
	//�A�C�h����Ԃ̃A�j���[�V�����Đ�
	mSkelMeshComp = owner->GetSkeltalMeshComp();
	mSkelMeshComp->PlayAnimation(owner->GetAnim(EnemyState::STATE_IDLE));

	mStateTimer = waitTime;
	owner->SetVelosity(Vector3::Zero);
}
