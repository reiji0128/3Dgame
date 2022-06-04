#include "SwitchActor.h"
#include "Game.h"
#include "Renderer.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "BoxCollider.h"

SwitchActor::SwitchActor(const Vector3& position, const char* gpmeshFileName)
	:Actor(Tag::Switch)
	,mShaderTag(ShaderTag::DepthmapAndShadowMap)
	,mBoxCollider(nullptr)
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