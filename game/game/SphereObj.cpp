#include "SphereObj.h"
#include "Game.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "SphereCollider.h"


SphereObj::SphereObj(const Vector3& pos)
	:Actor(Tag::Light)
	,mShaderTag(ShaderTag::HDRBloomBlend)
	,mSphereCollider(nullptr)
{
	mPosition = pos;
	SetScale(0.5f);

	Mesh* mesh = RENDERER->GetMesh("Assets/Sphere/Sphere.gpmesh");
	MeshComponent* mc = new MeshComponent(this, mShaderTag);
	mc->SetMesh(mesh);

	// トリガー用のスフィアを作成
	Sphere sphere(mPosition, mesh->GetRadius());
	mSphereCollider = new SphereCollider(this);
	mSphereCollider->SetSphere(sphere);
}

SphereObj::~SphereObj()
{
}