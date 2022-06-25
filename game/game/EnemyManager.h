#pragma once
#include <vector>

class EnemyManager final
{
private:
	EnemyManager();
	~EnemyManager();

public:
	/// <summary>
	/// エネミーマネージャーの初期化処理
	/// </summary>
	static void Initialize();

	/// <summary>
	/// エネミーマネージャーの更新処理
	/// </summary>
	/// <param name="deltaTime"></param>
	static void Update(float deltaTime);

	/// <summary>
	/// エネミーを登録
	/// </summary>
	/// <param name="entryEnemy">登録するエネミーのポインタ</param>
	static void Entry(class EnemyActor* entryEnemy);

	/// <summary>
	/// エネミーの削除
	/// </summary>
	/// <param name="releaseEnemy">削除するエネミーのポインタ</param>
	static void Release(class EnemyActor* releaseEnemy);

	/// <summary>
	/// 全エネミーの削除
	/// </summary>
	static void ReleaseAllEnemy();

	/// <summary>
	/// エネミーマネージャーの後始末処理
	/// アプリケーション終了前に呼び出す必要がある
	/// </summary>
	static void Finalize();

private:
	void ChangeEnemyState();

	// エネミーマネージャーのインスタンス
	static EnemyManager* mInstance;

	// エネミーのリスト
	std::vector<class EnemyActor*> mEnemyList;

	class PlayerActor* player;
};