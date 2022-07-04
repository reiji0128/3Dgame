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
	// カメラから見た前方ベクトルを取得
	Vector3 playerPos = GAMEINSTANCE.GetViewTarget();
	Vector3 cameraPos = GAMEINSTANCE.GetViewPos();
	Vector3 forwardVec = playerPos - cameraPos;
	forwardVec.z = 0.0f;
	forwardVec = Vector3::Normalize(forwardVec);

	// 前方ベクトルとz軸から右方向ベクトルを算出
	Vector3 rightVec = Vector3::Cross(Vector3::UnitZ, forwardVec);

	// 右方向から回転角を算出
	float forwardAngle = 0.0f;
	float angleSign;
	Vector3 tmpVec;
	forwardAngle = acosf(Vector3::Dot(Vector3::UnitX, rightVec));

	// 右回転か左回転か？
	tmpVec = Vector3::Cross(Vector3::UnitX, rightVec);
	angleSign = (tmpVec.z > 0.0) ? 1.0f : -1.0f;
	forwardAngle *= angleSign;

	// プレイヤーの前方ベクトル
	mCharaForwardVec = owner->GetForward();

	// キー入力
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

	// ゲームパッド
	Vector2 stickL = INPUT_INSTANCE.GetLStick();
	Matrix3 rot = Matrix3::CreateRotation(forwardAngle);
	stickL = Vector2::Transform(stickL, rot);
	DirVec.x += stickL.x;
	DirVec.y += stickL.y;

	Vector3 velosity = owner->GetVelocity();

	if (DirVec.Length() > 0.5)
	{

		DirVec.Normalize();
		
		// 空中移動処理
		velosity += DirVec * mMoveSpeed * deltaTime;
		
		// 最高速度を超えていたら調整
		Vector3 horizonSpeed = velosity;
		if (horizonSpeed.Length() > mMaxMoveSpeed * deltaTime)
		{
			horizonSpeed = DirVec * mMaxMoveSpeed * deltaTime;
			velosity.x = horizonSpeed.x;
			velosity.y = horizonSpeed.y;
		}

		// 回転中か？
		if (mRotateNow)
		{
			RotateActor();
		}

		// 入力とプレイヤーの前方ベクトルがほぼ同じなら
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

	// 重力
	velosity.z += mGravity * deltaTime;
	if (velosity.z < mMaxFallVelocity)
	{
		velosity.z = mMaxFallVelocity;
	}


	// 移動処理
	playerPos += velosity;

	owner->SetPosition(playerPos);
	owner->SetVelocity(velosity);
}

void PlayerStateJumpLoop::RotateActor()
{
	// 前方ベクトルが目標方向に近ければ回転終了
	if (isNearAngle(mRotationTargetDir, mCharaForwardVec))
	{
		mCharaForwardVec = mRotationTargetDir;
		mRotateNow = false;
	}
	else
	{
		// 回転させる
		Vector3 calcVec;
		calcVec = zRotateToAimVec(mCharaForwardVec, mRotationTargetDir, 10.0f);

		// 前方ベクトルが目標方向を超えていないか
		Vector3 cross1, cross2;
		cross1 = Vector3::Cross(mCharaForwardVec, mRotationTargetDir);
		cross2 = Vector3::Cross(calcVec, mRotationTargetDir);

		// 目標方向を超えたら終了
		if (cross1.z * cross2.z < 0.0f)
		{
			calcVec = mRotationTargetDir;
			mRotateNow = false;
		}
		mCharaForwardVec = calcVec;
	}
}
