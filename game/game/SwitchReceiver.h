#pragma once
#include "SwitchActor.h"
#include <vector>

class SwitchReceiver
{
public:
	SwitchReceiver();

	~SwitchReceiver();

	/// <summary>
	///  �X�C�b�`���ϒ��z��ɒǉ�
	/// </summary>
	/// <param name="switchActor">�X�C�b�`�̃|�C���^</param>
	void AddSwitch(SwitchActor* switchActor);

	/// <summary>
	/// �X�C�b�`���ϒ��z�񂩂�폜
	/// </summary>
	/// <param name="switchActor"></param>
	void RemoveSwitch(SwitchActor* switchActor);

private:
	std::vector<SwitchActor*> mSwitchReceiver;
};