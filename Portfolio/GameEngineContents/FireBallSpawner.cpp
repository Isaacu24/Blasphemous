#include "PreCompile.h"
#include "FireBallSpawner.h"
#include "FireBall.h"

FireBallSpawner::FireBallSpawner() {}

FireBallSpawner::~FireBallSpawner() {}


void FireBallSpawner::Start()
{
    Renderer_ = CreateComponent<GameEngineTextureRenderer>();
    Renderer_->CreateFrameAnimationCutTexture("pope_fireBallVortex", {"pope_fireBallVortex.png", 0, 44, 0.03f, true});
    Renderer_->ChangeFrameAnimation("pope_fireBallVortex");
    Renderer_->SetPivot(PIVOTMODE::CENTER);
    Renderer_->GetTransform().SetWorldScale({300, 300});

    Renderer_->AnimationBindFrame("pope_fireBallVortex",
                                std::bind(&FireBallSpawner::CreateFireBall, this, std::placeholders::_1));

    GetTransform().SetLocalRotate(Dir_);
}

void FireBallSpawner::Update(float _DeltaTime)
{
    if (10 == BallCount_)
    {
        Off();
        BallCount_ = 0;
    }
}

void FireBallSpawner::End() {}



void FireBallSpawner::CreateFireBall(const FrameAnimation_DESC& _Info)
{
    if (39 == _Info.CurFrame)
    {
        FireBall* Clone = GetLevel()->CreateActor<FireBall>();
        Clone->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
        Clone->SetGround(ColMap_);
        Clone->SetSpeed(600.f);
        Clone->SetDirection(Dir_);

        ++BallCount_;
    }
}
