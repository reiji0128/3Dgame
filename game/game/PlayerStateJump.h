#pragma once
#include "PlayerStateBase.h"

class PlayerStateJump : public PlayerStateBase
{
public:
	PlayerStateJump();

	~PlayerStateJump();

	PlayerState Update(class PlayerActor* owner, float deltaTime) override;

	/// <summary>
	/// 状態が移行したときに1度だけする処理
	/// </summary>
	/// <param name="owner">プレイヤーのポインタ</param>
	/// <param name="deltaTime">1フレームの経過時間</param>
	void Enter(class PlayerActor* owner, float deltaTime) override;

private:
	SkeletalMeshComponent* mSkelComp;
};