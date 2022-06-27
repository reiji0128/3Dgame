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

	// スケルタルメッシュコンポーネントのポインタ
	SkeletalMeshComponent* mSkelMeshComp;

	// エネミーからライトに向かうベクトル
	Vector3 enemyToLightVec;


	float runSpeed;
};