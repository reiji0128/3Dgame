#pragma once
#include "CameraActor.h"

class ThirdPersonCameraActor : public CameraActor
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	ThirdPersonCameraActor(Actor* targetActor);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~ThirdPersonCameraActor();

	/// <summary>
	/// �A�N�^�[�̍X�V����
	/// </summary>
	/// <param name="deltaTime">1�t���[���̌o�ߎ���</param>
	void UpdateActor(float deltaTime) override;

// �Z�b�^�[ //
	void SetRotateZAngle(float angle) { mRotateZAngle = angle; }
	void SetLookDownAngle(float angle) { mLookDownAngle = angle; }
	void SetCameraLength(float length) { mCameraLength = length; }
	void SetCameraPos(Vector3& vec) { mCameraPos = vec; }

// �Q�b�^�[ //
	Vector3& GetCameraForwardVec() { return mCameraForwardVec; }
	Vector3& GetCameraPos() { return mCameraPos; }

private:
	// �v���C���[����̋���
	float mCameraLength;

	// �J�������͉�]������]�p
	float mRotateZAngle;

	// �J���������낵������]�p
	float mLookDownAngle;

	// �O���x�N�g��
	Vector3 mCameraForwardVec;

	// �J�����ʒu
	Vector3 mCameraPos;
};