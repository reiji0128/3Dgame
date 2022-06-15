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
	// �R���g���[�����͂��ꂽ��
	bool isControllerInputoff = !(INPUT_INSTANCE.IsLStickMove());

	// �����L�[�����͂��ꂽ��
    bool IsIdle = INPUT_INSTANCE.IsKeyOff(KEY_W) &
        INPUT_INSTANCE.IsKeyOff(KEY_S) &
        INPUT_INSTANCE.IsKeyOff(KEY_A) &
        INPUT_INSTANCE.IsKeyOff(KEY_D) &
        isControllerInputoff;

    // �ړ����͂����ꂽ��
    if (!IsIdle)
    {
        return PlayerState::STATE_RUN;
    }

    return PlayerState::STATE_JUMPSTART;
}

void PlayerStateJump::Enter(PlayerActor* owner, float deltaTime)
{
    // �W�����v�n�߂̃A�j���[�V�������Đ�
    mSkelComp = owner->GetSkeltalMeshComp();
    mSkelComp->PlayAnimation(owner->GetAnim(PlayerState::STATE_JUMPSTART));
}
