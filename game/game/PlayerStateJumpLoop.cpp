#include "PlayerStateJumpLoop.h"
#include "Input.h"

PlayerStateJumpLoop::PlayerStateJumpLoop()
{
}

PlayerStateJumpLoop::~PlayerStateJumpLoop()
{
}

PlayerState PlayerStateJumpLoop::Update(PlayerActor* owner, float deltaTime)
{
	if (owner->GetIsOnGround())
	{
		return PlayerState::STATE_JUMPEND;
	}

	JumpMoveCalc(owner, deltaTime);

    return PlayerState::STATE_JUMPLOOP;
}

void PlayerStateJumpLoop::Enter(PlayerActor* owner, float deltaTime)
{
    mSkelComp = owner->GetSkeltalMeshComp();
    mSkelComp->PlayAnimation(owner->GetAnim(PlayerState::STATE_JUMPLOOP));
}

void PlayerStateJumpLoop::JumpMoveCalc(PlayerActor* owner, float deltaTime)
{
	// �J�������猩���O���x�N�g�����擾
	Vector3 playerPos = GAMEINSTANCE.GetViewTarget();
	Vector3 cameraPos = GAMEINSTANCE.GetViewPos();
	Vector3 forwardVec = playerPos - cameraPos;
	forwardVec.z = 0.0f;
	forwardVec = Vector3::Normalize(forwardVec);

	// �O���x�N�g����z������E�����x�N�g�����Z�o
	Vector3 rightVec = Vector3::Cross(Vector3::UnitZ, forwardVec);

	// �E���������]�p���Z�o
	float forwardAngle = 0.0f;
	float angleSign;
	Vector3 tmpVec;
	forwardAngle = acosf(Vector3::Dot(Vector3::UnitX, rightVec));

	// �E��]������]���H
	tmpVec = Vector3::Cross(Vector3::UnitX, rightVec);
	angleSign = (tmpVec.z > 0.0) ? 1.0f : -1.0f;
	forwardAngle *= angleSign;

	// �v���C���[�̑O���x�N�g��
	mCharaForwardVec = owner->GetForward();

	// �L�[����
	Vector3 DirVec(0.0f, 0.0f, 0.0f);
	if (INPUT_INSTANCE.IsKeyPressed(KEY_W))
	{
		DirVec += forwardVec;
	}

	if (INPUT_INSTANCE.IsKeyPressed(KEY_S))
	{
		DirVec -= forwardVec;
	}

	if (INPUT_INSTANCE.IsKeyPressed(KEY_D))
	{
		DirVec += rightVec;
	}

	if (INPUT_INSTANCE.IsKeyPressed(KEY_A))
	{
		DirVec -= rightVec;
	}

	// �Q�[���p�b�h
	Vector2 stickL = INPUT_INSTANCE.GetLStick();
	Matrix3 rot = Matrix3::CreateRotation(forwardAngle);
	stickL = Vector2::Transform(stickL, rot);
	DirVec.x += stickL.x;
	DirVec.y += stickL.y;

	Vector3 velosity = owner->GetVelocity();

	if (DirVec.Length() > 0.5)
	{

		DirVec.Normalize();
		
		// �󒆈ړ�����
		velosity += DirVec * mMoveSpeed * deltaTime;
		
		// �ō����x�𒴂��Ă����璲��
		Vector3 horizonSpeed = velosity;
		if (horizonSpeed.Length() > mMaxMoveSpeed * deltaTime)
		{
			horizonSpeed = DirVec * mMaxMoveSpeed * deltaTime;
			velosity.x = horizonSpeed.x;
			velosity.y = horizonSpeed.y;
		}

		// ��]�����H
		if (mRotateNow)
		{
			RotateActor();
		}

		// ���͂ƃv���C���[�̑O���x�N�g�����قړ����Ȃ�
		if (isNearAngle(DirVec, mCharaForwardVec))
		{
			mCharaForwardVec = DirVec;
		}
		else
		{
			mRotateNow = true;
			mRotationTargetDir = DirVec;
		}
	}
	else
	{
		velosity.x *= 0.1f;
		velosity.y *= 0.1f;
	}

	// �d��
	velosity.z += mGravity * deltaTime;
	if (velosity.z < mMaxFallVelocity)
	{
		velosity.z = mMaxFallVelocity;
	}


	// �ړ�����
	playerPos += velosity;

	owner->SetPosition(playerPos);
	owner->SetVelocity(velosity);
}

void PlayerStateJumpLoop::RotateActor()
{
	// �O���x�N�g�����ڕW�����ɋ߂���Ή�]�I��
	if (isNearAngle(mRotationTargetDir, mCharaForwardVec))
	{
		mCharaForwardVec = mRotationTargetDir;
		mRotateNow = false;
	}
	else
	{
		// ��]������
		Vector3 calcVec;
		calcVec = zRotateToAimVec(mCharaForwardVec, mRotationTargetDir, 10.0f);

		// �O���x�N�g�����ڕW�����𒴂��Ă��Ȃ���
		Vector3 cross1, cross2;
		cross1 = Vector3::Cross(mCharaForwardVec, mRotationTargetDir);
		cross2 = Vector3::Cross(calcVec, mRotationTargetDir);

		// �ڕW�����𒴂�����I��
		if (cross1.z * cross2.z < 0.0f)
		{
			calcVec = mRotationTargetDir;
			mRotateNow = false;
		}
		mCharaForwardVec = calcVec;
	}
}
