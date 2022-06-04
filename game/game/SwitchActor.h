#pragma once

#include "Actor.h"
#include "Math.h"
#include "ShaderTag.h"

class SwitchActor : public Actor
{
public:
	SwitchActor(const Vector3& position, const char* gpmeshFileName);

	~SwitchActor();

// �Q�b�^�[ //
	bool GetSwitchFlag() { return mSwitchFlag; }

private:
	// �X�C�b�`�t���O
	bool mSwitchFlag;

	// �K�p����V�F�[�_�[�̃^�O
	ShaderTag mShaderTag;

	// �{�b�N�X�R���C�_�[�̃|�C���^
	class BoxCollider* mBoxCollider;
};