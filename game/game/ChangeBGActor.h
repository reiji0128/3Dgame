#pragma once

#include "Actor.h"
#include "Math.h"
#include "ShaderTag.h"

class ChangeBGActor : public Actor
{
public:
	ChangeBGActor(const Vector3& position, const char* gpmeshFileName, class SwitchReceiver* receiver);

	~ChangeBGActor();

private:

	SwitchReceiver* mReceiver;

	// �K�p����V�F�[�_�[�̃^�O
	ShaderTag mShaderTag;
};