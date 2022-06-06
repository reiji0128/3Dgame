#pragma once

#include "Receiver.h"
#include "Math.h"
#include "ShaderTag.h"

class ChangeBGActor : public Receiver
{
public:
	ChangeBGActor(const Vector3& position, const char* gpmeshFileName);

	~ChangeBGActor();

	void UpdateActor(float deltaTime) override;

private:
	// 適用するシェーダーのタグ
	ShaderTag mShaderTag;
};