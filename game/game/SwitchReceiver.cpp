#include "SwitchReceiver.h"

SwitchReceiver::SwitchReceiver()
{
}

SwitchReceiver::~SwitchReceiver()
{
}

void SwitchReceiver::AddSwitch(SwitchActor* switchActor)
{
	mSwitchReceiver.emplace_back(switchActor);
}

void SwitchReceiver::RemoveSwitch(SwitchActor* switchActor)
{
	auto iter = std::find(mSwitchReceiver.begin(), mSwitchReceiver.end(), switchActor);
	mSwitchReceiver.erase(iter);
}
