#include "PlayerStateJump.h"
#include "Input.h"

PlayerStateJump::PlayerStateJump()
{
}

PlayerStateJump::~PlayerStateJump()
{
}

PlayerState PlayerStateJump::Update(PlayerActor* owner, float deltaTime)
{
	// コントローラ入力されたか
	bool isControllerInputoff = !(INPUT_INSTANCE.IsLStickMove());

	// 方向キーが入力されたか
    bool IsIdle = INPUT_INSTANCE.IsKeyOff(KEY_W) &
        INPUT_INSTANCE.IsKeyOff(KEY_S) &
        INPUT_INSTANCE.IsKeyOff(KEY_A) &
        INPUT_INSTANCE.IsKeyOff(KEY_D) &
        isControllerInputoff;

    // 移動入力がされたか
    if (!IsIdle)
    {
        return PlayerState::STATE_RUN;
    }

    return PlayerState::STATE_JUMPSTART;
}

void PlayerStateJump::Enter(PlayerActor* owner, float deltaTime)
{
    // ジャンプ始めのアニメーションを再生
    mSkelComp = owner->GetSkeltalMeshComp();
    mSkelComp->PlayAnimation(owner->GetAnim(PlayerState::STATE_JUMPSTART));
}
