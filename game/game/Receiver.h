#pragma once
#include "Actor.h"
class Receiver : public Actor
{
public:
	Receiver();

	virtual ~Receiver();

	/// <summary>
	/// �X�C�b�`�̏��
	/// </summary>
	enum SwitchState
	{
		ON,
		OFF
	};

// �Z�b�^�[ //
	void SetSwitchState(SwitchState state) { mNowState = state; }

// �Q�b�^�[ //
	SwitchState GetSwitchState() { return mNowState; }

protected:

	// �X�C�b�`�̌��݂̏��
	SwitchState mNowState;

	// �X�C�b�`�̑O�t���[���̏��
	SwitchState mPrevState;

};

