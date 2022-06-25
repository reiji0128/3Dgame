#pragma once
#include <vector>

class EnemyManager final
{
private:
	EnemyManager();
	~EnemyManager();

public:
	/// <summary>
	/// �G�l�~�[�}�l�[�W���[�̏���������
	/// </summary>
	static void Initialize();

	/// <summary>
	/// �G�l�~�[�}�l�[�W���[�̍X�V����
	/// </summary>
	/// <param name="deltaTime"></param>
	static void Update(float deltaTime);

	/// <summary>
	/// �G�l�~�[��o�^
	/// </summary>
	/// <param name="entryEnemy">�o�^����G�l�~�[�̃|�C���^</param>
	static void Entry(class EnemyActor* entryEnemy);

	/// <summary>
	/// �G�l�~�[�̍폜
	/// </summary>
	/// <param name="releaseEnemy">�폜����G�l�~�[�̃|�C���^</param>
	static void Release(class EnemyActor* releaseEnemy);

	/// <summary>
	/// �S�G�l�~�[�̍폜
	/// </summary>
	static void ReleaseAllEnemy();

	/// <summary>
	/// �G�l�~�[�}�l�[�W���[�̌�n������
	/// �A�v���P�[�V�����I���O�ɌĂяo���K�v������
	/// </summary>
	static void Finalize();

private:
	void ChangeEnemyState();

	// �G�l�~�[�}�l�[�W���[�̃C���X�^���X
	static EnemyManager* mInstance;

	// �G�l�~�[�̃��X�g
	std::vector<class EnemyActor*> mEnemyList;

	class PlayerActor* player;
};