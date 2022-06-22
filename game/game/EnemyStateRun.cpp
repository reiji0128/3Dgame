#include "EnemyStateRun.h"
#include "Game.h"

EnemyStateRun::EnemyStateRun()
{
}

EnemyStateRun::~EnemyStateRun()
{
}

EnemyState EnemyStateRun::Update(EnemyActor* owner, float deltaTime)
{
	// �v���C���[�ʒu���
	Vector3 playerPos = GAMEINSTANCE.GetFirstActor(Tag::Player)->GetPosition();
	Vector3 pos = owner->GetPosition();
	enemyToPlayerVec = playerPos - pos;

	float length = enemyToPlayerVec.Length();
	enemyToPlayerVec.Normalize();

	//�ǐՂ��Ȃ������܂ŋ߂Â����Ƃ��ɍU���Ɉڍs
	if (length < nearLength)
	{
		return EnemyState::STATE_ATTACK;
	}

	// �ǐՉ\�����𒴂�����X�e�[�g���p�g���[���Ɉڍs
	if (length > trackingRange)
	{
		return EnemyState::STATE_PATROL;
	}

	//�v���C���[�̍U�����󂯂���
	if (owner->GetIsHitTrig())
	{
		return EnemyState::STATE_DEATH;
	}

	//�ړ�����
	MoveCalc(owner, deltaTime);
	return EnemyState::STATE_RUN;
}

void EnemyStateRun::Enter(EnemyActor* owner, float deltaTime)
{
	//Run��Ԃ̃A�j���[�V�����Đ�
	mSkelMeshComp = owner->GetSkeltalMeshComp();
	mSkelMeshComp->PlayAnimation(owner->GetAnim(EnemyState::STATE_RUN));
}

void EnemyStateRun::MoveCalc(EnemyActor* owner, float deltaTime)
{
	//���������̌������擾
	Vector3 dir = enemyToPlayerVec;
	dir.z = 0.0f;
	dir.Normalize();

	Vector3 velocity = dir * runSpeed * deltaTime;
	owner->SetVelosity(velocity);

	owner->SetDirection(dir);
	owner->SetComputeWorldTransform();
}
