#include "EnemyStateHit.h"
#include "Game.h"

EnemyStateHit::EnemyStateHit()
{
}

EnemyStateHit::~EnemyStateHit()
{
}

EnemyState EnemyStateHit::Update(EnemyActor* owner, float delotaTime)
{
	// ����
	owner->SetVelosity(owner->GetVelosity() * knokBackBrake);

	if (!mSkelMeshComp->IsPlaying())
	{
		owner->SetVelosity(Vector3::Zero);
		owner->SetIsHitTrig(false);
		//���S����
		/*if (health->GetPre() <= health->GetMin())
		{
			return EnemyState::STATE_DEATH;
		}*/

		return EnemyState::STATE_PATROL;
	}

	return EnemyState::STATE_HIT;
}

void EnemyStateHit::Enter(EnemyActor* owner, float deltaTime)
{
	owner->SetVelosity(Vector3::Zero);

	//�q�b�g��Ԃ̃A�j���[�V�����Đ�
	mSkelMeshComp = owner->GetSkeltalMeshComp();
	mSkelMeshComp->PlayAnimation(owner->GetAnim(EnemyState::STATE_HIT));

	// �v���C���[�̈ʒu����m�b�N�o�b�N
	Vector3 knokBackDir = owner->GetPosition() - GAMEINSTANCE.GetPlayerActor()->GetPosition();
	knokBackDir.Normalize();

	//�m�b�N�o�b�N�̏����x�N�g��
	owner->SetVelosity(knokBackDir * knokBackSpeed * deltaTime);

	//�_���[�W����
	/*Health* health = owner->GetEnemyHealth();
	health->SetPre(health->GetPre() - 5.0f);*/
}
