#pragma once
#include <vector>

class EnemyManager final
{
public:
	EnemyManager();

	~EnemyManager();

	/// <summary>
	/// エネミーマネージャーの更新処理
	/// </summary>
	/// <param name="deltaTime"></param>
	void Update(float deltaTime);

	/// <summary>
	/// エネミーを登録
	/// </summary>
	/// <param name="entryEnemy">登録するエネミーのポインタ</param>
	void Entry(class EnemyActor* entryEnemy);

	/// <summary>
	/// エネミーの削除
	/// </summary>
	/// <param name="releaseEnemy">削除するエネミーのポインタ</param>
	void Release(class EnemyActor* releaseEnemy);

	/// <summary>
	/// 全エネミーの削除
	/// </summary>
	void ReleaseAllEnemy();

private:
	/// <summary>
	/// エネミーのステートを変更
	/// </summary>
	void ChangeEnemyState();

	// エネミーの動的配列
	std::vector<class EnemyActor*> mEnemyList;

	// プレイヤーのポインタ
	class PlayerActor* player;
};