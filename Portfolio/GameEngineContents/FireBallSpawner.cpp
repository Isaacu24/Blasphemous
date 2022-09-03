#include "PreCompile.h"
#include "FireBallSpawner.h"
#include "FireBall.h"

FireBallSpawner::FireBallSpawner() {}

FireBallSpawner::~FireBallSpawner() {}


//스포너 자체도 회전해야함
void FireBallSpawner::Start()
{
    Renderer_ = CreateComponent<GameEngineTextureRenderer>();
    Renderer_->CreateFrameAnimationCutTexture("pope_fireBallVortex", {"pope_fireBallVortex.png", 0, 44, 0.03f, true});
    Renderer_->ChangeFrameAnimation("pope_fireBallVortex");
    Renderer_->SetPivot(PIVOTMODE::CENTER);
    Renderer_->GetTransform().SetWorldScale({300, 300});

    Renderer_->AnimationBindFrame("pope_fireBallVortex",
                                  std::bind(&FireBallSpawner::CreateFireBall, this, std::placeholders::_1));
}

void FireBallSpawner::Update(float _DeltaTime)
{
    switch (SpawnerType_)
    {
        case SPAWNERTYPE::SP_LOWLEVLE:
            if (10 == BallCount_)
            {
                Off();
                SpawnerEnd_ = true;
                BallCount_  = 0;
            }
            break;

        case SPAWNERTYPE::SP_HIGHLEVLE:
            if (5 == BallCount_)
            {
                Off();
                SpawnerEnd_ = true;
                BallCount_  = 0;
            }
            break;
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

        float4 Dir = Target_->GetTransform().GetWorldPosition() - GetTransform().GetWorldPosition();
        Dir.Normalize();

        Clone->SetDirection(Dir);

        ++BallCount_;
    }
}
