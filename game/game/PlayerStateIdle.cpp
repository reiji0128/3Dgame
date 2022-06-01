#include "PlayerStateIdle.h"
#include "Input.h"
#include "Bullet.h"

PlayerStateIdle::PlayerStateIdle()
{
}

PlayerStateIdle::~PlayerStateIdle()
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="owner">�v���C���[�̃|�C���^</param>
/// <param name="deltaTime">1�t���[���̌o�ߎ���</param>
/// <returns></returns>
PlayerState PlayerStateIdle::Update(PlayerActor* owner, float deltaTime)
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

    Fire(owner, deltaTime);

    return PlayerState::STATE_IDLE;
}

/// <summary>
/// ��Ԃ��ڍs�����Ƃ���1�x��������
/// </summary>
/// <param name="owner">�v���C���[�̃|�C���^</param>
/// <param name="deltaTime">1�t���[���̌o�ߎ���</param>
void PlayerStateIdle::Enter(PlayerActor* owner, float deltaTime)
{
    // �A�C�h����Ԃ̃A�j���[�V�������Đ�
    mSkelComp = owner->GetSkeltalMeshComp();
    mSkelComp->PlayAnimation(owner->GetAnim(PlayerState::STATE_IDLE));
}

void PlayerStateIdle::Fire(class PlayerActor* owner, float deltaTime)
{
    // �e�𔭎�
    if (INPUT_INSTANCE.GetInput(KEY_SPACE) == KEY_STATE_PUSHDOWN)
    {
        //���ˈʒu���v�Z
        Vector3 firePos;
        firePos = owner->GetDirection() * 100.0f;
        firePos.z = 100.0f;

        //�v���C���[�e�𐶐�����Ƃ��� Tag::PlayerBullet���w�肵�����B�ǂ������炢�����낤�H
        BulletActor* ba = new BulletActor(firePos + owner->GetPosition(), owner->GetDirection(),
            Tag::PlayerBullet, 1000.0f, 10000.0f);
    }
}
