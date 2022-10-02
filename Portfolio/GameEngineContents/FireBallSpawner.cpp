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
    // if (true == IsStop_)
    //{
    //     if (true == FireBall_->IsDeath())
    //     {

    //    }

    //    return;
    //}

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
            if (3 == BallCount_)
            {
                SpawnerEnd_ = true;
                BallCount_  = 0;
                Off();
            }
            break;
    }
}

void FireBallSpawner::End() {}


void FireBallSpawner::CreateFireBall(const FrameAnimation_DESC& _Info)
{
    if (39 == _Info.CurFrame)
    {
        SoundPlayer_ = GameEngineSound::SoundPlayControl("FIREBALL_FIRE.wav");

        FireBall* Clone = GetLevel()->CreateActor<FireBall>();
        Clone->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
        Clone->SetStartPosition(GetTransform().GetWorldPosition());
        Clone->SetGround(ColMap_);

        Clone->SetSpeed(350.f);
        Clone->SetWeight(500.f);

        float4 Dir = Target_->GetTransform().GetWorldPosition() - GetTransform().GetWorldPosition();
        Dir.Normalize();
        Clone->SetDirection(Dir);

        //float4 Pos = GetTransform().GetWorldPosition();
        //Pos.Normalize();
                
        //float UpVector  = sqrt(pow(Pos.x, 2) + pow(Pos.y, 2));
        //float DirVector = sqrt(pow(Dir.x, 2) + pow(Dir.y, 2));

        //float Inner = (Pos.x * Dir.x) + (Pos.y * Dir.y);
        //float theta = acos(Inner / (UpVector * DirVector));
        //theta = -theta * GameEngineMath::RadianToDegree;

        float Degree = atan2(Dir.y, Dir.x) * 180 / GameEngineMath::PI;

        if (Degree < 0)
        {
            Degree += 360;
        }

        GetTransform().SetWorldRotation({0, 0, Degree});
        Clone->GetTransform().SetWorldRotation({0, 0, Degree});

        ++BallCount_;
    }
}
