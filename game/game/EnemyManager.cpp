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
	// �v���C���[�����C�g�ɓ������Ă�����G�l�~�[�̃X�e�[�g��ύX
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
/// �G�l�~�[�̃X�e�[�g�̕ύX����
/// </summary>
void EnemyManager::ChangeEnemyState()
{
	for (auto enemy : mEnemyList)
	{
		enemy->SetNextState(EnemyState::STATE_MOVE_LIGHT);
	}
}
