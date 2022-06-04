#pragma once
#include "MeshComponent.h"
#include "Math.h"
#include "ShaderTag.h"

class ChangeMeshComponent : public MeshComponent
{
public:
	ChangeMeshComponent(class Actor* owner,ShaderTag shaderTag);

	~ChangeMeshComponent();

	void Draw(class Shader* shader) override;
};