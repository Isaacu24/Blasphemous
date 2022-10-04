#include "PreCompile.h"
#include "CutScenePlayer.h"

CutScenePlayer::CutScenePlayer()
    : CutRenderer_(nullptr)
    , PlayTime_(0.01f)
    , CurrentFrame_(0)
{}

CutScenePlayer::~CutScenePlayer() {}


void CutScenePlayer::Start() { CutRenderer_ = CreateComponent<GameEngineUIRenderer>(); }

void CutScenePlayer::Update(float _DeltaTime)
{
    if (true == IsPlay_)
    {
        Speed_ += _DeltaTime;

        if (PlayTime_ <= Speed_)
        {
            Speed_ = 0.f;

            CutRenderer_->SetTexture(SceneFrameList_[CurrentFrame_] + ".png");
            CutRenderer_->ScaleToTexture();
            CutRenderer_->GetTransform().SetWorldScale(CutRenderer_->GetTransform().GetWorldScale() * 2.f);

            ++CurrentFrame_;

            if (MaxFrame_ - 1 == CurrentFrame_ && nullptr != EndFunc_)
            {
                EndFunc_();
            }

            if (MaxFrame_ == CurrentFrame_)
            {
                CurrentFrame_ = 0;
                IsPlay_       = false;

                CutRenderer_->Off();
                Off();
            }
        }
        // GetTransform().SetWorldPosition(GetLevel()->GetMainCamera()->GetMouseWorldPosition());
    }
}

void CutScenePlayer::End() {}
