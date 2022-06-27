#include "EnemyManager.h"
#include "EnemyActor.h"
#include "PlayerActor.h"

EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
	ReleaseAllEnemy();
}

void EnemyManager::Update(float deltaTime)
{
	// プレイヤーがライトに当たっていたらエネミーのステートを変更
	if(player->GetHitLight())
	{
		ChangeEnemyState();
	}
}

void EnemyManager::Entry(EnemyActor* entryEnemy)
{
}

void EnemyManager::Release(EnemyActor* releaseEnemy)
{

}

void EnemyManager::ReleaseAllEnemy()
{
}

/// <summary>
/// エネミーのステートの変更処理
/// </summary>
void EnemyManager::ChangeEnemyState()
{
	for (auto enemy : mEnemyList)
	{
		enemy->SetNextState(EnemyState::STATE_MOVE_LIGHT);
	}
}
