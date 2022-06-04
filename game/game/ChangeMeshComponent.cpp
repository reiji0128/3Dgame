#include "ChangeMeshComponent.h"

ChangeMeshComponent::ChangeMeshComponent(class Actor* owner, ShaderTag shaderTag)
	:MeshComponent(owner,shaderTag)
{
	mOwner = owner;
}

ChangeMeshComponent::~ChangeMeshComponent()
{
}

void ChangeMeshComponent::Draw(Shader* shader)
{
}
