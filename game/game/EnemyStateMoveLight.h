#pragma once
#include "EnemyStateBase.h"
#include "SkeletalMeshComponent.h"

class EnemyStateMoveLight : public EnemyStateBase
{
public:
	EnemyStateMoveLight();
	~EnemyStateMoveLight();

	EnemyState Update(class EnemyActor* owner, float deltaTime) override;
	void Enter(class EnemyActor* owner, float deltaTime) override;

private:
	void MoveCalc(EnemyActor* owner, float deltaTime);

	// �X�P���^�����b�V���R���|�[�l���g�̃|�C���^
	SkeletalMeshComponent* mSkelMeshComp;

	// �G�l�~�[���烉�C�g�Ɍ������x�N�g��
	Vector3 enemyToLightVec;


	float runSpeed;
};