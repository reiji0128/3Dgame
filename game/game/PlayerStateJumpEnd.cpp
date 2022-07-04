#include "PlayerStateJumpEnd.h"
#include "PlayerActor.h"
#include "Input.h"

PlayerStateJumpEnd::PlayerStateJumpEnd()
{
}

PlayerStateJumpEnd::~PlayerStateJumpEnd()
{
}

PlayerState PlayerStateJumpEnd::Update(PlayerActor* owner, float deltaTime)
{
	if (!mSkelComp->IsPlaying())
	{
		return PlayerState::STATE_IDLE;
	}

	// コントローラ入力されたか
	Vector2 stickL = INPUT_INSTANCE.GetLStick();

	// 方向キーが入力されたか
	bool isContollerInputOff = !INPUT_INSTANCE.IsLStickMove();

	bool IsIdle = INPUT_INSTANCE.IsKeyOff(KEY_W) &
		          INPUT_INSTANCE.IsKeyOff(KEY_S) &
		          INPUT_INSTANCE.IsKeyOff(KEY_D) &
		          INPUT_INSTANCE.IsKeyOff(KEY_A) &
		          isContollerInputOff;

	if (!IsIdle)
	{
		return PlayerState::STATE_RUN;
	}

	return PlayerState::STATE_JUMPEND;
}

void PlayerStateJumpEnd::Enter(PlayerActor* owner, float deltaTime)
{
	mSkelComp = owner->GetSkeltalMeshComp();
	mSkelComp->PlayAnimation(owner->GetAnim(PlayerState::STATE_JUMPEND));

	owner->SetIsGround(true);
	owner->SetVelocity(Vector3(0, 0, 0));
}
