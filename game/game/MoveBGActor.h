#pragma once
#include "Actor.h"
#include "ShaderTag.h"

// �ړ����������
enum DirectionMovement
{
	XAxis,
	YAxis,
	ZAxis,
};

class MoveBGActor :public Actor
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="position">�ʒu</param>
	/// <param name="gpmeshFileName">���b�V���̃t�@�C���p�X</param>
	MoveBGActor(const Vector3& position, const char* gpmeshFileName);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~MoveBGActor();

private:
	// �K�p����V�F�[�_�[�̃^�O
	ShaderTag mShaderTag;
};