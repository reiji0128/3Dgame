#include "SwitchActor.h"
#include "Game.h"
#include "Renderer.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "SphereCollider.h"
#include "Input.h"

SwitchActor::SwitchActor(const Vector3& pos, const char* gpmeshFileName,bool switchFlag)
	:Actor(Tag::Light)
	,mShaderTag(ShaderTag::HDRBloomBlend)
	,mSphereCollider(nullptr)
	,mSwitchFlag(switchFlag)
{
	mPosition = pos;
	SetScale(0.5);

	// メッシュの読み込み・セット
	Mesh* mesh = RENDERER->GetMesh(gpmeshFileName);
	mMeshComp = new MeshComponent(this, mShaderTag);
	mMeshComp->SetChangeLuminance(false);
	mMeshComp->SetMesh(mesh);

	// トリガー用のスフィアを作成
	Sphere sphere(mPosition, mesh->GetRadius());
	mSphereCollider = new SphereCollider(this);
	mSphereCollider->SetSphere(sphere);
}

SwitchActor::~SwitchActor()
{
}

void SwitchActor::UpdateActor(float deltaTime)
{
	if (mSwitchFlag)
	{
		ChangeState();
		mMeshComp->SetChangeLuminance(true);
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
		mSwitchFlag = true;
	}
}

void SwitchActor::ChangeState()
{
	for (auto receiver : mReceiverManager)
	{
		receiver->SetSwitchState(Receiver::ON);
	}
}
