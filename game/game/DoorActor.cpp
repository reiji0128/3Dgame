#include "DoorActor.h"
#include "BoxCollider.h"
#include "Mesh.h"
#include "Game.h"
#include "Renderer.h"
#include "SkeletalMeshComponent.h"

DoorActor::DoorActor(const Vector3& pos, const float& scale, const float addAngle, const char* gpmeshFileName)
	:Actor(Tag::BackGround)
	,mAddAngle(addAngle)
	,mIsOpen(false)
{
	mPosition = pos;
	SetScale(scale);

	// メッシュの読み込み・セット
	Mesh* mesh = RENDERER->GetMesh(gpmeshFileName);
	mSkeltalMeshComp = new SkeletalMeshComponent(this, mShaderTag);
	mSkeltalMeshComp->SetMesh(mesh);

	// 当たり判定のセット
	AABB box = mesh->GetCollisionBox();
	box.Scaling(1.0f, 1.0f, 1.0f);
	box.OffsetPos(0.0f, 0.0f, 80.0f);
	mBoxCollider = new BoxCollider(this);
	mBoxCollider->SetObjectBox(box);
}

DoorActor::~DoorActor()
{
}

void DoorActor::UpdateActor(float deltaTime)
{
	if (mIsOpen)
	{
		Rotation(Vector3::UnitZ, mAddAngle);
	}
}

void DoorActor::Rotation(const Vector3& axis, const float& angle)
{
	float radian = Math::ToRadians(angle);
	Quaternion rot = mRotation;
	Quaternion inc(axis, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	mRotation = target;
}
