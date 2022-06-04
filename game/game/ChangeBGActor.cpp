#include "ChangeBGActor.h"
#include "Game.h"
#include "Renderer.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "SwitchReceiver.h"

ChangeBGActor::ChangeBGActor(const Vector3& position, const char* gpmeshFileName, class SwitchReceiver* receiver)
	:Actor(Tag::BackGround)
	,mShaderTag(ShaderTag::DepthmapAndShadowMap)
	,mReceiver(receiver)
{
	mPosition = position;
	Mesh* mesh = RENDERER->GetMesh(gpmeshFileName);
	MeshComponent* mc = new MeshComponent(this, mShaderTag);
	mc->SetMesh(mesh);

	mReceiver->AddSwitch();
	mState = State::EInactive;
}

ChangeBGActor::~ChangeBGActor()
{
}