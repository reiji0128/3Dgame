#include "Lantern.h"
#include "Mesh.h"
#include "Game.h"
#include "Renderer.h"
#include "AttachMeshComponent.h"

Lantern::Lantern(const Vector3& pos, const Vector3& rot, 
	             const char* gpmeshFileName, SkeletalMeshComponent* skelComp,
	             const char* boneName)
	:Actor(Tag::Lantern)
	,mBoneName(boneName)
	,mSkelComp(skelComp)
	,mAttachComp(nullptr)
	,mShaderTag(ShaderTag::DepthmapAndShadowMap)
{
	//メッシュのセット
	Mesh* mesh = RENDERER->GetMesh(gpmeshFileName);
	mAttachComp = new AttachMeshComponent(this, mSkelComp, mBoneName, mShaderTag);
	mAttachComp->SetMesh(mesh);
	mAttachComp->SetOffsetPosition(pos);
	mAttachComp->SetOffsetRotation(rot);
}

Lantern::~Lantern()
{
}
