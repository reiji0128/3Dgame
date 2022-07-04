#include "PlayerStateJumpStart.h" 
#include "PlayerActor.h"

PlayerStateJumpStart::PlayerStateJumpStart()
{
}

PlayerStateJumpStart::~PlayerStateJumpStart()
{
}

PlayerState PlayerStateJumpStart::Update(PlayerActor* owner, float deltaTime)
{
    if (!mSkelComp->IsPlaying())
    {
        JumpCalc(owner,deltaTime);
        owner->SetIsGround(false);

        return PlayerState::STATE_JUMPLOOP;
    }
    return PlayerState::STATE_JUMPSTART;
}

void PlayerStateJumpStart::Enter(PlayerActor* owner, float deltaTime)
{
    mSkelComp = owner->GetSkeltalMeshComp();
    mSkelComp->PlayAnimation(owner->GetAnim(PlayerState::STATE_JUMPSTART));
}

void PlayerStateJumpStart::JumpCalc(PlayerActor* owner, float deltaTime)
{
    Vector3 playerPos = owner->GetPosition();
    Vector3 velosity = owner->GetVelocity();

    velosity.z = mJumpPower;
    playerPos += velosity;
    
    owner->SetPosition(playerPos);
    owner->SetVelocity(velosity);
}
