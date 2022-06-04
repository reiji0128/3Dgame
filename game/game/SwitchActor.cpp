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

	// ���b�V���̓ǂݍ��݁E�Z�b�g
	Mesh* mesh = RENDERER->GetMesh(gpmeshFileName);
	MeshComponent* mc = new MeshComponent(this, mShaderTag);

	// �����蔻��̃Z�b�g
	AABB box = mesh->GetCollisionBox();
	box.Scaling(1.0f);
	mBoxCollider = new BoxCollider(this);
	mBoxCollider->SetObjectBox(box);
}

SwitchActor::~SwitchActor()
{
}