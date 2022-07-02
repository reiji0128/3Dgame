#include "MoveBGActor.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "Renderer.h"

MoveBGActor::MoveBGActor(const Vector3& position, const char* gpmeshFileName)
	:Actor(Tag::BackGround)
{
	mPosition = position;
	Mesh* mesh = RENDERER->GetMesh(gpmeshFileName);
	MeshComponent* mc = new MeshComponent(this, mShaderTag);
	mc->SetMesh(mesh);
}

MoveBGActor::~MoveBGActor()
{
}
