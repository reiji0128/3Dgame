#include "EnemyStateMoveLight.h"
#include "Game.h"

EnemyStateMoveLight::EnemyStateMoveLight()
{
}

EnemyStateMoveLight::~EnemyStateMoveLight()
{
}

EnemyState EnemyStateMoveLight::Update(EnemyActor* owner, float deltaTime)
{
	Vector3 LightPos = GAMEINSTANCE.GetFirstActor(Tag::Light)->GetPosition();
	Vector3 mPosition = owner->GetPosition();
	enemyToLightVec = LightPos - mPosition;

	float length = enemyToLightVec.Length();

	MoveCalc(owner, deltaTime);

	if (owner->GetHitLight())
	{
		return EnemyState::STATE_PATROL;
	}

	return EnemyState::STATE_MOVE_LIGHT;
}

void EnemyStateMoveLight::Enter(EnemyActor* owner, float deltaTime)
{
	//アイドル状態のアニメーション再生
	mSkelMeshComp = owner->GetSkeltalMeshComp();
	mSkelMeshComp->PlayAnimation(owner->GetAnim(EnemyState::STATE_MOVE_LIGHT));

	mStateTimer = waitTime;
	owner->SetVelosity(Vector3::Zero);
}

void EnemyStateMoveLight::MoveCalc(EnemyActor* owner, float deltaTime)
{
	// 水平方向の向きを取得
	Vector3 dir = enemyToLightVec;
	dir.z = 0.0f;
	dir.Normalize();

	Vector3 velocity = dir * runSpeed * deltaTime;
	owner->SetVelosity(velocity);

	owner->SetDirection(dir);
	owner->SetComputeWorldTransform();
}
