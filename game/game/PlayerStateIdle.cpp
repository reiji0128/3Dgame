#include "PlayerStateIdle.h"
#include "Input.h"

PlayerStateIdle::PlayerStateIdle()
{
}

PlayerStateIdle::~PlayerStateIdle()
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="owner">プレイヤーのポインタ</param>
/// <param name="deltaTime">1フレームの経過時間</param>
/// <returns></returns>
PlayerState PlayerStateIdle::Update(PlayerActor* owner, float deltaTime)
{
    // コントローラ入力されたか
    bool isControllerInputoff = !(INPUT_INSTANCE.IsLStickMove());

    // 方向キーが入力されたか
    bool IsIdle = INPUT_INSTANCE.IsKeyOff(KEY_W) &
                  INPUT_INSTANCE.IsKeyOff(KEY_S) &
                  INPUT_INSTANCE.IsKeyOff(KEY_A) &
                  INPUT_INSTANCE.IsKeyOff(KEY_D) &
                  isControllerInputoff;

    bool IsJump = INPUT_INSTANCE.IsKeyOff(KEY_SPACE);

    // 移動入力がされたか
    if (!IsIdle)
    {
        return PlayerState::STATE_RUN;
    }

    if (!IsJump && owner->GetIsOnGround())
    {
        return PlayerState::STATE_JUMPSTART;
    }

    return PlayerState::STATE_IDLE;
}

/// <summary>
/// 状態が移行したときに1度だけ処理
/// </summary>
/// <param name="owner">プレイヤーのポインタ</param>
/// <param name="deltaTime">1フレームの経過時間</param>
void PlayerStateIdle::Enter(PlayerActor* owner, float deltaTime)
{
    // アイドル状態のアニメーションを再生
    mSkelComp = owner->GetSkeltalMeshComp();
    mSkelComp->PlayAnimation(owner->GetAnim(PlayerState::STATE_IDLE));
}
