#include "PreCompile.h"
#include "MonsterBase.h"
#include "MetaTextureRenderer.h"

MonsterBase::MonsterBase() 
    : State_{}
    , Renderer_(nullptr)
    , ColMap_(nullptr)
    , Gravity_(nullptr)
    , DetectCollider_(nullptr)
    , BodyCollider_(nullptr)
    , AttackCollider_(nullptr)
    , HP_(100)
    , Att_(100)
    , Speed_(100.f)
    , Tear_(100)
    , IsGround_(false)
{}

MonsterBase::~MonsterBase() {}

void MonsterBase::SetGround(GameEngineTextureRenderer* _Ground) { ColMap_ = _Ground; }

bool MonsterBase::GroundCheck(int _X, int _Y)
{
    float4 Color = ColMap_->GetCurTexture()->GetPixelToFloat4(_X, _Y);

    if (Color.CompareInt4D(float4::BLACK))
    {
        IsGround_ = true;
        return true;
    }

    else if (Color.CompareInt4D(float4::MAGENTA))
    {
        IsGround_ = true;
        return true;
    }

    IsGround_ = false;
    return false;
}

bool MonsterBase::UphillRoadCheck(int _X, int _Y)
{
    while (true)
    {
        float4 Color = ColMap_->GetCurTexture()->GetPixelToFloat4(_X, _Y);

        if (true == Color.CompareInt4D(float4::BLACK))
        {
            return true;
        }

        else
        {
            return false;
        }
    }
}

