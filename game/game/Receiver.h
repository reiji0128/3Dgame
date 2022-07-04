#pragma once
#include "Actor.h"
class Receiver : public Actor
{
public:
	Receiver();

	virtual ~Receiver();

	/// <summary>
	/// スイッチの状態
	/// </summary>
	enum SwitchState
	{
		ON,
		OFF
	};

// セッター //
	void SetSwitchState(SwitchState state) { mNowState = state; }

// ゲッター //
	SwitchState GetSwitchState() { return mNowState; }

protected:

	// スイッチの現在の状態
	SwitchState mNowState;

	// スイッチの前フレームの状態
	SwitchState mPrevState;

};

