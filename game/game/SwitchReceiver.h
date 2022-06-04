#pragma once
#include "SwitchActor.h"
#include <vector>

class SwitchReceiver
{
public:
	SwitchReceiver();

	~SwitchReceiver();

	/// <summary>
	///  スイッチを可変長配列に追加
	/// </summary>
	/// <param name="switchActor">スイッチのポインタ</param>
	void AddSwitch(SwitchActor* switchActor);

	/// <summary>
	/// スイッチを可変長配列から削除
	/// </summary>
	/// <param name="switchActor"></param>
	void RemoveSwitch(SwitchActor* switchActor);

private:
	std::vector<SwitchActor*> mSwitchReceiver;
};