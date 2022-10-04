#include "PreCompile.h"
#include "GravityActor.h"
#include "AttackCorpseEffecter.h"

GravityActor::GravityActor()
    : Gravity_(nullptr)
    , IsMove_(false)
    , Speed_(100.f)
{}

GravityActor::~GravityActor() {}


void GravityActor::Start()
{
    Gravity_  = CreateComponent<GravityComponent>();
    //Renderer_ = CreateComponent<GameEngineTextureRenderer>();

    AttackEffecter_ = GetLevel()->CreateActor<AttackCorpseEffecter>();

    //Renderer_->GetTransform().SetWorldScale({100, 100});
    //Renderer_->SetPivot(PIVOTMODE::BOT);
}

void GravityActor::Update(float _DeltaTime)
{
    if (true == IsMove_)
    {
        Alpha_ += _DeltaTime;

        CreateAttackEffect(Alpha_);

        float4 CurPos = float4::Lerp(StartPos_, EndPos_, Alpha_);
        GetTransform().SetWorldPosition({CurPos.x, CurPos.y, 0});

        if (0 > Dir_.x)
        {
            if (EndPos_.x > GetTransform().GetWorldPosition().x)
            {
                IsMove_ = false;
            }
        }

        else
        {
            if (EndPos_.x < GetTransform().GetWorldPosition().x)
            {
                IsMove_ = false;
            }
        }
    }

    GroundCheck();
    UphillRoadCheck();
    Gravity_->SetActive(!IsGround_);
}

void GravityActor::End() {}

void GravityActor::GroundCheck()
{
    float4 Color;

    Color = ColMap_->GetCurTexture()->GetPixelToFloat4(GetTransform().GetWorldPosition().x,
                                                       -(GetTransform().GetWorldPosition().y));

    if (true == Color.CompareInt4D(float4::BLACK) || true == Color.CompareInt4D(float4::MAGENTA))  //¶¥ÀÌ¶ó¸é
    {
        IsGround_ = true;
    }

    else
    {
        IsGround_ = false;
    }
}


void GravityActor::UphillRoadCheck()
{
    while (true)
    {
        float4 Color = ColMap_->GetCurTexture()->GetPixelToFloat4(GetTransform().GetWorldPosition().x,
                                                                  -(GetTransform().GetWorldPosition().y - 1));

        if (true == Color.CompareInt4D(float4::BLACK) || true == Color.CompareInt4D(float4::MAGENTA))
        {
            GetTransform().SetWorldMove(float4::UP);
            continue;
        }

        else
        {
            break;
        }
    }
}


void GravityActor::CreateAttackEffect(float _Alpha)     
{
    if (0.3f <= Alpha_ && 0 == CreateIndex_)
    {
        ++CreateIndex_;

        AttackEffecter_->SetCreatePos(GetTransform().GetWorldPosition() + float4{0, 0.f});
        AttackEffecter_->SetDir(Dir_.x);
        AttackEffecter_->CreateEffect();
    }

    if (0.4f <= Alpha_ && 1 == CreateIndex_)
    {
        ++CreateIndex_;

        AttackEffecter_->SetCreatePos(GetTransform().GetWorldPosition() + float4{0, 0.f});
        AttackEffecter_->SetDir(Dir_.x);
        AttackEffecter_->CreateEffect();
    }

    if (0.5f <= Alpha_ && 2 == CreateIndex_)
    {
        ++CreateIndex_;

        AttackEffecter_->SetCreatePos(GetTransform().GetWorldPosition() + float4{0, 0.f});
        AttackEffecter_->SetDir(Dir_.x);
        AttackEffecter_->CreateEffect();
    }

    if (0.6f <= Alpha_ && 3 == CreateIndex_)
    {
        ++CreateIndex_;

        AttackEffecter_->SetCreatePos(GetTransform().GetWorldPosition() + float4{0, 0.f});
        AttackEffecter_->SetDir(Dir_.x);
        AttackEffecter_->CreateEffect();
    }

    if (0.7f <= Alpha_ && 4 == CreateIndex_)
    {
        ++CreateIndex_;

        AttackEffecter_->SetCreatePos(GetTransform().GetWorldPosition() + float4{0, 0.f});
        AttackEffecter_->SetDir(Dir_.x);
        AttackEffecter_->CreateEffect();
    }


    if (0.8f <= Alpha_ && 5 == CreateIndex_)
    {
        ++CreateIndex_;

        AttackEffecter_->SetCreatePos(GetTransform().GetWorldPosition() + float4{0, 0.f});
        AttackEffecter_->SetDir(Dir_.x);
        AttackEffecter_->CreateEffect();
    }


    if (0.9f <= Alpha_ && 6 == CreateIndex_)
    {
        ++CreateIndex_;

        AttackEffecter_->SetCreatePos(GetTransform().GetWorldPosition() + float4{0, 0.f});
        AttackEffecter_->SetDir(Dir_.x);
        AttackEffecter_->CreateEffect();
    }


    if (1.0f <= Alpha_ && 7 == CreateIndex_)
    {
        ++CreateIndex_;

        AttackEffecter_->SetCreatePos(GetTransform().GetWorldPosition() + float4{0, 0.f});
        AttackEffecter_->SetDir(Dir_.x);
        AttackEffecter_->CreateEffect();
    }
}
