#include "PreCompile.h"
#include "CherubPopUp.h"

CherubPopUp::CherubPopUp() {}

CherubPopUp::~CherubPopUp() {}


void CherubPopUp::Start()
{
    GetTransform().SetWorldScale({2, 2, 1});

    PopUp_ = CreateComponent<GameEngineUIRenderer>();
    PopUp_->SetTexture("CherubPopUp.png");
    PopUp_->ScaleToTexture();
    PopUp_->GetTransform().SetWorldMove({0.f, 150.f, static_cast<int>(UIORDER::PlayerUI)});
    PopUp_->GetColorData().MulColor.a = 0.f;

    MaxFont_ = CreateComponent<GameEngineFontRenderer>();
    MaxFont_->SetColor({0.72f, 0.64f, 0.3f, 0.0f});
    MaxFont_->SetScreenPostion({650, 200, static_cast<int>(UIORDER::PlayerUI)});
    MaxFont_->SetSize(25);
    MaxFont_->SetLeftAndRightSort(LeftAndRightSort::LEFT);
    MaxFont_->SetText("  /40", "NeoµÕ±Ù¸ð");
    MaxFont_->ChangeCamera(CAMERAORDER::UICAMERA);

    CountFont_ = CreateComponent<GameEngineFontRenderer>();
    CountFont_->SetColor({0.72f, 0.64f, 0.3f, 0.0f});
    CountFont_->SetScreenPostion({650, 200, static_cast<int>(UIORDER::PlayerUI)});
    CountFont_->SetSize(25);
    CountFont_->SetLeftAndRightSort(LeftAndRightSort::LEFT);
    CountFont_->ChangeCamera(CAMERAORDER::UICAMERA);

    IsOn_ = true;
}

void CherubPopUp::Update(float _DeltaTime)
{
    if (true == IsOn_)
    {
        PopUp_->GetColorData().MulColor.a += _DeltaTime * 2;

        Alpha_ += _DeltaTime * 2;

        MaxFont_->SetColor({0.72f, 0.64f, 0.3f, Alpha_});
        CountFont_->SetColor({0.72f, 0.64f, 0.3f, Alpha_});

        if (1.f <= Alpha_)
        {
            IsOn_  = false;
            Alpha_ = 1;

            MaxFont_->SetColor({0.72f, 0.64f, 0.3f, 1.f});
            CountFont_->SetColor({0.72f, 0.64f, 0.3f, 1.f});

            PopUp_->GetColorData().MulColor.a = 1.f;
        }
    }

    if (false == IsOn_ && false == IsOff_)
    {
        ShowTime_ += _DeltaTime;

        if (1.5f < ShowTime_)
        {
            IsOff_ = true;
        }
    }

    if (true == IsOff_)
    {
        PopUp_->GetColorData().MulColor.a -= _DeltaTime * 2;

        Alpha_ -= _DeltaTime * 2;

        MaxFont_->SetColor({0.72f, 0.64f, 0.3f, Alpha_});
        CountFont_->SetColor({0.72f, 0.64f, 0.3f, Alpha_});

        if (0.f >= Alpha_)
        {
            Death();
        }
    }
}

void CherubPopUp::End() {}


void CherubPopUp::LevelEndEvent()
{
    PopUp_->Death();
    MaxFont_->Death();
    CountFont_->Death();
    Death();
}
