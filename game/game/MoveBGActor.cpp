#include "MoveBGActor.h"
#include "Game.h"
#include "Renderer.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "BoxCollider.h"

MoveBGActor::MoveBGActor(const Vector3& startPos, const Vector3& endPos, const float mSpeed, const char* gpmeshFileName)
	:mShaderTag(ShaderTag::DepthmapAndShadowMap)
{
	mPosition  = startPos;
	mAimPos	   = endPos;
	mStartPos = startPos;
	mEndPos = endPos;

	//���b�V���̓ǂݍ���
	Mesh* mesh = RENDERER->GetMesh(gpmeshFileName);
	MeshComponent* mc = new MeshComponent(this,ShaderTag::DepthmapAndShadowMap);
	mc->SetMesh(mesh);

	//�����蔻��̃Z�b�g
	AABB box = mesh->GetCollisionBox();
	box.Scaling(1.0f, 1.0f, 1.0f);
	box.mIsRotatable = false;
	mBoxCollider = new BoxCollider(this);
	mBoxCollider->SetObjectBox(box);

	mTag = Tag::MoveFloor;
	mMoveFlag = false;

	mDirection = Vector3(1, 0, 0);

	mNowState = SwitchState::OFF;
}

MoveBGActor::~MoveBGActor()
{
}

void MoveBGActor::UpdateActor(float deltaTime)
{
	// �X�C�b�`��ON�ł���΃A�N�e�B�u��
	if (GetSwitchState() == ON)
	{
		mMoveFlag = true;
	}
	else
	{
		mMoveFlag = false;
	}

	if (mMoveFlag)
	{
		Vector3 aimDir;
		aimDir = mAimPos - mPosition;

		if (aimDir.LengthSq() < 0.5f)
		{
			mTempPos = mEndPos;
			mEndPos = mStartPos;
			mStartPos = mTempPos;

			mPosition = mStartPos;
			mAimPos = mEndPos;
			aimDir = mAimPos - mPosition;
		}

		aimDir.Normalize();
		mDirection = aimDir;
		mPosition += mSpeed * mDirection * deltaTime;
	}
}