#include "PreCompile.h"
#include "MetaTextureRenderer.h"

MetaTextureRenderer::MetaTextureRenderer() {}

MetaTextureRenderer::~MetaTextureRenderer() {}


void MetaTextureRenderer::Start()
{
    GameEngineTextureRenderer::Start();

    GetClonePipeLine(GetPipeLine());
}

void MetaTextureRenderer::Update(float _Delta)
{
    GameEngineTextureRenderer::Update(_Delta);

    if (nullptr != CurAni)
    {
        MetaSetPivot();
    }
}

void MetaTextureRenderer::End() { GameEngineTextureRenderer::End();}

void MetaTextureRenderer::MetaSetPivot()
{
    int Index_ = GetCurAniInfo().Frames[GetCurAniInfo().CurFrame];

    float X = CurData_[Index_].PivotX - 0.5f;
    float Y = (1 - CurData_[Index_].PivotY) - 0.5f;

    float Width  = abs(X * CurData_[Index_].Width);
    float Height = abs(Y * CurData_[Index_].Height);

    // 1사분면일 때
    if (0.f < X && 0.f > Y)
    {
        GetTransform().SetLocalPosition({-(Width), -(Height)});
    }

    // 2사분면일 때
    else if (0.f > X && 0.0f > Y)
    {
        GetTransform().SetLocalPosition({(Width), -(Height)});
    }

    // 3사분면일 때
    else if (0.f > X && 0.f < Y)
    {
        GetTransform().SetLocalPosition({(Width), (Height)});
    }

    // 4사분면일 때
    else if (0.f < X && 0.f < Y)
    {
        GetTransform().SetLocalPosition({-(Width), (Height)});
    }

    ScaleToCutTexture(Index_);
}

void MetaTextureRenderer::CreateMetaAnimation(const std::string&           _AnimationName,
                                              const FrameAnimation_DESC&   _Desc,
                                              std::vector<MetaData>& _MetaDatas)
{
    GameEngineTextureRenderer::CreateFrameAnimationCutTexture(_AnimationName, _Desc);
    SetCurData(_MetaDatas);

    std::string Key = GameEngineString::ToUpperReturn(_AnimationName);
    AllMetaData_.insert(std::make_pair(Key, _MetaDatas));
}

void MetaTextureRenderer::ChangeMetaAnimation(const std::string& _AnimationName)
{
    GameEngineTextureRenderer::ChangeFrameAnimation(_AnimationName);

    std::string Key = GameEngineString::ToUpperReturn(_AnimationName);

    std::map<std::string, std::vector<MetaData>>::iterator FindIter = AllMetaData_.find(Key);

    if (FindIter == AllMetaData_.end())
    {
        MsgBoxAssert("해당 메타 애니메이션의 정보가 존재하지 않습니다.");
        return;
    }

    CurData_ = FindIter->second;

    MetaSetPivot();
}


//
// void MetaTextureRenderer::MetaSetPivot()
//{
//    float X = Pivot_.x - 0.5f;
//    float Y = (1 - Pivot_.y) - 0.5f;
//
//    float Width  = abs(X * SizeX_);
//    float Height = abs(Y * SizeY_);
//
//    // 1사분면일 때
//    if (0.f < X && 0.f > Y)
//    {
//        GetTransform().SetLocalPosition({-(Width), -(Height)});
//    }
//
//    // 2사분면일 때
//    else if (0.f > X && 0.0f > Y)
//    {
//        GetTransform().SetLocalPosition({(Width), -(Height)});
//    }
//
//    // 3사분면일 때
//    else if (0.f > X && 0.f < Y)
//    {
//        GetTransform().SetLocalPosition({(Width), (Height)});
//    }
//
//    // 4사분면일 때
//    else if (0.f < X && 0.f < Y)
//    {
//        GetTransform().SetLocalPosition({-(Width), (Height)});
//    }
//}
//
