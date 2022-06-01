#include "EnemyStatePatrol.h"
#include "Game.h"

EnemyStatePatrol::EnemyStatePatrol()
	:mAimVec(0, 0, 0)
	, mRotateNow(false)
{
}

EnemyStatePatrol::~EnemyStatePatrol()
{
}

EnemyState EnemyStatePatrol::Update(EnemyActor* owner, float deltaTime)
{
	Vector3 dir = owner->GetDirection();

	//��]����?
	if (mRotateNow)
	{
		// �ڕW�p�x�ɋ߂Â������ړ]�I���E���i��
		if (isNearAngle(dir, mAimVec))
		{
			dir = mAimVec;
			mRotateNow = false;
			owner->SetDirection(dir);
			owner->SetVelosity(dir * patrolSpeed * deltaTime);
			return EnemyState::STATE_PATROL;
		}
		// ��]
		dir = (zRotateToAimVec(dir, mAimVec, rotateSpeed * deltaTime));
		owner->SetDirection(dir);
		owner->RotateToNewForward();
	}

	// �G�L�����̎��E&�͈͂ɓ�������ǔ����[�h��
	Vector3 playerPos = GAMEINSTANCE.GetFirstActor(Tag::Altar)->GetPosition();
	enemyToPlayerVec = playerPos - owner->GetPosition();
	float dot = Vector3::Dot(enemyToPlayerVec, dir);

	if (dot > 0 && enemyToPlayerVec.Length() < trackingRange)
	{
		return EnemyState::STATE_RUN;
	}

	//�v���C���[�̍U�����󂯂���
	if (owner->GetIsHitTrig())
	{
		return EnemyState::STATE_DEATH;
	}

	// BGTrigger���w�i�ɐG�ꂽ���]���[�h�ɕύX
	if (owner->GetIsBGTrig())
	{
		// 90�x���v���ɕ����]��&��]���[�h�Ɉڍs
		mRotateNow = true;
		mAimVec = Vector3::Cross(Vector3::UnitZ, dir);
		owner->SetVelosity(Vector3::Zero);
	}

	owner->SetDirection(dir);

	// �O�i
	owner->SetVelosity(dir * patrolSpeed * deltaTime);

	return EnemyState::STATE_PATROL;
}

void EnemyStatePatrol::Enter(EnemyActor* owner, float deltaTime)
{
	//�p�g���[����Ԃ̃A�j���[�V�����Đ�
	mSkelMeshComp = owner->GetSkeltalMeshComp();
	mSkelMeshComp->PlayAnimation(owner->GetAnim(EnemyState::STATE_PATROL));

	mRotateNow = false;
}