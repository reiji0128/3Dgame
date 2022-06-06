#include "ChangeBGActor.h"
#include "Game.h"
#include "Renderer.h"
#include "Mesh.h"
#include "MeshComponent.h"

ChangeBGActor::ChangeBGActor(const Vector3& position, const char* gpmeshFileName)
	:mShaderTag(ShaderTag::DepthmapAndShadowMap)
{
	mTag = Tag::ChangeBackGround;

	mPosition = position;
	Mesh* mesh = RENDERER->GetMesh(gpmeshFileName);
	MeshComponent* mc = new MeshComponent(this, mShaderTag);
	mc->SetMesh(mesh);

	mState = State::EInactive;
}

ChangeBGActor::~ChangeBGActor()
{
}

void ChangeBGActor::UpdateActor(float deltaTime)
{
	if (GetSwitchState() == ON)
	{

	}
	else
	{

	}
}
