#include "PreCompile.h"
#include "DeadZone.h"

DeadZone::DeadZone() 
{
}

DeadZone::~DeadZone() 
{
}

void DeadZone::Start() 
{ 
	Collider_ = CreateComponent<GameEngineCollision>(); 
	
    Collider_ = CreateComponent<GameEngineCollision>();
    Collider_->GetTransform().SetWorldScale({5000.f, 500.f, 1.f});
    Collider_->ChangeOrder(COLLISIONORDER::DeadZone);
    Collider_->SetDebugSetting(CollisionType::CT_OBB2D, float4{1.f, 0.0f, 0.0f, 0.25f});
}

void DeadZone::Update(float _DeltaTime) 
{

}

void DeadZone::End() 
{
}
