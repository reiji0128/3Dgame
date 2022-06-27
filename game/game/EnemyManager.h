#pragma once
#include <vector>

class EnemyManager final
{
public:
	EnemyManager();

	~EnemyManager();

	/// <summary>
	/// �G�l�~�[�}�l�[�W���[�̍X�V����
	/// </summary>
	/// <param name="deltaTime"></param>
	void Update(float deltaTime);

	/// <summary>
	/// �G�l�~�[��o�^
	/// </summary>
	/// <param name="entryEnemy">�o�^����G�l�~�[�̃|�C���^</param>
	void Entry(class EnemyActor* entryEnemy);

	/// <summary>
	/// �G�l�~�[�̍폜
	/// </summary>
	/// <param name="releaseEnemy">�폜����G�l�~�[�̃|�C���^</param>
	void Release(class EnemyActor* releaseEnemy);

	/// <summary>
	/// �S�G�l�~�[�̍폜
	/// </summary>
	void ReleaseAllEnemy();

private:
	/// <summary>
	/// �G�l�~�[�̃X�e�[�g��ύX
	/// </summary>
	void ChangeEnemyState();

	// �G�l�~�[�̓��I�z��
	std::vector<class EnemyActor*> mEnemyList;

	// �v���C���[�̃|�C���^
	class PlayerActor* player;
};