#pragma once

class PlayerActor;
class SphereObj;

class UIManager final
{
public:
	UIManager(PlayerActor* player,SphereObj* sphere);
	~UIManager();
};