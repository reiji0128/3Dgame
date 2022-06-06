#include "SwitchActor.h"
#include "Game.h"
#include "Renderer.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "BoxCollider.h"
#include "Input.h"

SwitchActor::SwitchActor(const Vector3& position, const char* gpmeshFileName,bool switchFlag)
	:Actor(Tag::Switch)
	,mShaderTag(ShaderTag::DepthmapAndShadowMap)
	,mBoxCollider(nullptr)
	,mChangeBackGroundFlag(switchFlag)
{
	mPosition = position;

	// メッシュの読み込み・セット
	Mesh* mesh = RENDERER->GetMesh(gpmeshFileName);
	MeshComponent* mc = new MeshComponent(this, mShaderTag);

	// 当たり判定のセット
	AABB box = mesh->GetCollisionBox();
	box.Scaling(1.0f);
	mBoxCollider = new BoxCollider(this);
	mBoxCollider->SetObjectBox(box);
}

SwitchActor::~SwitchActor()
{
}

void SwitchActor::UpdateActor(float deltaTime)
{
	if (mChangeBackGroundFlag)
	{
		ChangeState();
	}
	else
	{
		Receiver::OFF;
	}
}

void SwitchActor::OnCollisionEnter(ColliderComponent* ownCollider, ColliderComponent* otherCollider)
{
	Tag colliderTag = otherCollider->GetTag();

	// 衝突情報
	CollisionInfo info;

	if (colliderTag == Tag::Player)
	{
		if (INPUT_INSTANCE.IsKeyOff(KEY_START))
		{
			mChangeBackGroundFlag = true;
		}
	}
}

void SwitchActor::ChangeState()
{
	for (auto receiver : mReceiverManager)
	{
		receiver->SetSwitchState(Receiver::ON);
	}
}
