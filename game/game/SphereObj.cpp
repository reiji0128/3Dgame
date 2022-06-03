#include "SphereObj.h"
#include "Game.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "SphereCollider.h"


SphereObj::SphereObj(const Vector3& pos)
	:Actor(Tag::Altar)
	,mShaderTag(ShaderTag::HDRBloomBlend)
	,mSphereCollider(nullptr)
{
	mPosition = pos;
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
