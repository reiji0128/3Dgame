#include "EnemyStateAttack.h"
#include "Game.h"
#include "AttackObj.h"

EnemyStateAttack::EnemyStateAttack()
{
}

EnemyStateAttack::~EnemyStateAttack()
{
}

EnemyState EnemyStateAttack::Update(EnemyActor* owner, float deltaTime)
{
	mStateTimer -= deltaTime;

	// �v���C���[���痣�ꂽ��ǐՃ��[�h��
	Vector3 playerPos = GAMEINSTANCE.GetFirstActor(Tag::Player)->GetPosition();
	Vector3 enemyToPlayerVec = playerPos - owner->GetPosition();

	float length = enemyToPlayerVec.Length();

	// �v���C���[�����ꂽ��ǐՃ��[�h�ֈڍs
	if (length > retrackingRange)
	{
		return EnemyState::STATE_RUN;
	}

	// �Đ��A�j��������������ǐՃ��[�h�ֈڍs
	if (!mSkelMeshComp->IsPlaying())
	{
		return EnemyState::STATE_RUN;
	}

	//�v���C���[�̍U�����󂯂���
	if (owner->GetIsHitTrig())
	{
		return EnemyState::STATE_DEATH;
	}

	//�U������
	Attack(owner, deltaTime);

	return EnemyState::STATE_ATTACK;
}

void EnemyStateAttack::Enter(EnemyActor* owner, float deltaTime)
{
	mStateTimer = attackOffsetTime;
	owner->SetVelosity(Vector3::Zero);

	//�U����Ԃ̃A�j���[�V�����Đ�
	mSkelMeshComp = owner->GetSkeltalMeshComp();
	mSkelMeshComp->PlayAnimation(owner->GetAnim(EnemyState::STATE_ATTACK));
}

void EnemyStateAttack::Attack(EnemyActor* owner, float deltaTime)
{
	//�U���\���ԂɂȂ�����U��
	if (mStateTimer < 0.0f)
	{
		new AttackObj(Tag::EnemyBullet, owner->GetPosition(), owner->GetDirection(), 150.0f, 0.3f);
		mStateTimer = FLT_MAX;		// �^�C�}�[�𖳌���Ƀ��Z�b�g���čU�����J��Ԃ��Ȃ��悤�ɂ���
	}
}
