#include "EnemyManager.h"
#include "EnemyActor.h"
#include "PlayerActor.h"

// �G�l�~�[�}�l�[�W���[�̃C���X�^���X�ւ̃|�C���^���`
EnemyManager* EnemyManager::mInstance = nullptr;

EnemyManager::EnemyManager()
{
	mInstance = nullptr;
}

EnemyManager::~EnemyManager()
{
	ReleaseAllEnemy();
}

void EnemyManager::Initialize()
{
	if (!mInstance)
	{
		mInstance = new EnemyManager;
	}
}

void EnemyManager::Update(float deltaTime)
{
	player
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

void EnemyManager::Finalize()
{
	ReleaseAllEnemy();

	if (mInstance)
	{
		delete mInstance;
		mInstance = nullptr;
	}
}

/// <summary>
/// �G�l�~�[�̃X�e�[�g�̕ύX����
/// </summary>
void EnemyManager::ChangeEnemyState()
{
	for (auto enemy : mEnemyList)
	{
		enemy->SetNextState(EnemyState::STATE_RUN);
	}
}
