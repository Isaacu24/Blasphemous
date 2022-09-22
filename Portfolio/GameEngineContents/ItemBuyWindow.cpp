#include "PreCompile.h"
#include "Merchant.h"
#include "ItemBuyWindow.h"

ItemBuyWindow::ItemBuyWindow()
    : SelectIndex_(1)
{}

ItemBuyWindow::~ItemBuyWindow() {}


void ItemBuyWindow::Start()
{
    GetTransform().SetWorldScale({2, 2, 1});

    FrameRenderer_ = CreateComponent<GameEngineUIRenderer>();
    FrameRenderer_->GetTransform().SetWorldPosition({-300, 180});
    FrameRenderer_->SetTexture("items-icons-spritesheet.png", 1);
    FrameRenderer_->ScaleToCutTexture(1);
    FrameRenderer_->Off();

    IconRenderer_ = CreateComponent<GameEngineUIRenderer>();
    IconRenderer_->GetTransform().SetWorldPosition({-300, 180});
    IconRenderer_->Off();

    PointRenderer_ = CreateComponent<GameEngineUIRenderer>();
    PointRenderer_->SetTexture("purge_points.png");
    PointRenderer_->ScaleToTexture();
    PointRenderer_->GetTransform().SetWorldMove({227, -120});
    PointRenderer_->Off();

    BackgroundRenderer_ = CreateComponent<GameEngineUIRenderer>();
    BackgroundRenderer_->SetTexture("BlackBackground.png");
    BackgroundRenderer_->ScaleToTexture();
    BackgroundRenderer_->GetColorData().MulColor.a = 0.35f;
    BackgroundRenderer_->Off();

    SelectRenderer_ = CreateComponent<GameEngineUIRenderer>();
    SelectRenderer_->SetTexture("purge_points.png");
    SelectRenderer_->ScaleToTexture();
    SelectRenderer_->GetTransform().SetWorldMove({-45, -205});
    SelectRenderer_->Off();

    HighFrameRenderer_ = CreateComponent<GameEngineUIRenderer>();
    HighFrameRenderer_->SetTexture("pup-up-decoration.png");
    HighFrameRenderer_->GetTransform().SetWorldMove({0, 230.f});
    HighFrameRenderer_->ScaleToTexture();
    HighFrameRenderer_->Off();

    LowFrameRenderer_ = CreateComponent<GameEngineUIRenderer>();
    LowFrameRenderer_->SetTexture("pup-up-decoration.png");
    LowFrameRenderer_->GetTransform().SetWorldMove({0, -70.f});
    LowFrameRenderer_->ScaleToTexture();
    LowFrameRenderer_->Off();

    Font_ = CreateComponent<GameEngineFontRenderer>();
    Font_->SetColor({0.74f, 0.74f, 0.74f, 1.0f});
    Font_->SetScreenPostion({640, 470, static_cast<int>(UIORDER::PlayerUI)});
    Font_->SetSize(25);
    Font_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
    Font_->ChangeCamera(CAMERAORDER::UICAMERA);
    Font_->Off();

    BuyFont_ = CreateComponent<GameEngineFontRenderer>();
    BuyFont_->SetColor({0.74f, 0.74f, 0.74f, 1.0f});
    BuyFont_->SetScreenPostion({620, 550, static_cast<int>(UIORDER::PlayerUI)});
    BuyFont_->SetSize(25);
    BuyFont_->SetLeftAndRightSort(LeftAndRightSort::LEFT);
    BuyFont_->ChangeCamera(CAMERAORDER::UICAMERA);
    BuyFont_->SetText("Buy", "NeoµÕ±Ù¸ð");
    BuyFont_->Off();

    NoFont_ = CreateComponent<GameEngineFontRenderer>();
    NoFont_->SetColor({0.74f, 0.74f, 0.74f, 1.0f});
    NoFont_->SetScreenPostion({620, 600, static_cast<int>(UIORDER::PlayerUI)});
    NoFont_->SetSize(25);
    NoFont_->SetLeftAndRightSort(LeftAndRightSort::LEFT);
    NoFont_->ChangeCamera(CAMERAORDER::UICAMERA);
    NoFont_->SetText("No", "NeoµÕ±Ù¸ð");
    NoFont_->Off();

    ItemName_ = CreateComponent<GameEngineFontRenderer>();
    ItemName_->SetColor({0.59f, 0.41f, 0.06f, 1.0f});
    ItemName_->SetScreenPostion({400, 170, static_cast<int>(UIORDER::PlayerUI)});
    ItemName_->SetSize(27);
    ItemName_->SetLeftAndRightSort(LeftAndRightSort::LEFT);
    ItemName_->ChangeCamera(CAMERAORDER::UICAMERA);
    ItemName_->Off();

    ItemDecs_ = CreateComponent<GameEngineFontRenderer>();
    ItemDecs_->SetColor({0.74f, 0.74f, 0.73f, 1.0f});
    ItemDecs_->SetScreenPostion({330, 230, static_cast<int>(UIORDER::PlayerUI)});
    ItemDecs_->SetSize(25);
    ItemDecs_->SetLeftAndRightSort(LeftAndRightSort::LEFT);
    ItemDecs_->ChangeCamera(CAMERAORDER::UICAMERA);
    ItemDecs_->Off();

    AcquiredFont_ = CreateComponent<GameEngineFontRenderer>();
    AcquiredFont_->SetColor({0.74f, 0.74f, 0.73f, 1.0f});
    AcquiredFont_->SetScreenPostion({530, 600, static_cast<int>(UIORDER::PlayerUI)});
    AcquiredFont_->SetSize(25);
    AcquiredFont_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
    AcquiredFont_->ChangeCamera(CAMERAORDER::UICAMERA);
    AcquiredFont_->SetText("You have acquired: ", "NeoµÕ±Ù¸ð");
    AcquiredFont_->Off();

    AcquiredItemName_ = CreateComponent<GameEngineFontRenderer>();
    AcquiredItemName_->SetColor({0.59f, 0.41f, 0.06f, 1.0f});
    AcquiredItemName_->SetScreenPostion({720, 600, static_cast<int>(UIORDER::PlayerUI)});
    AcquiredItemName_->SetSize(25);
    AcquiredItemName_->SetLeftAndRightSort(LeftAndRightSort::LEFT);
    AcquiredItemName_->ChangeCamera(CAMERAORDER::UICAMERA);
    AcquiredItemName_->Off();

    AcquiredFrame_ = CreateComponent<GameEngineUIRenderer>();
    AcquiredFrame_->SetTexture("items-icons-spritesheet.png", 1);
    AcquiredFrame_->ScaleToCutTexture(1);
    AcquiredFrame_->GetTransform().SetWorldPosition({40, -250});
    AcquiredFrame_->Off();

    AcquiredIcon_ = CreateComponent<GameEngineUIRenderer>();
    AcquiredIcon_->GetTransform().SetWorldPosition({40, -250});
    AcquiredIcon_->Off();

    if (false == GameEngineInput::GetInst()->IsKey("ShopDown"))
    {
        GameEngineInput::GetInst()->CreateKey("ShopDown", VK_DOWN);
        GameEngineInput::GetInst()->CreateKey("ShopUp", VK_UP);
        GameEngineInput::GetInst()->CreateKey("ShopEnter", VK_RETURN);
    }

    BuyFont_->SetColor({0.65f, 0.62f, 0.47f, 1.0f});
    NoFont_->SetColor({0.74f, 0.74f, 0.74f, 1.0f});
}

void ItemBuyWindow::Update(float _DeltaTime)
{
    switch (Mode_)
    {
        case ItemBuyWindow::WindowMode::Buy:
            if (nullptr != SelectRenderer_ && false == IsBuy_)
            {
                if (false == SelectRenderer_->IsUpdate())
                {
                    return;
                }

                if (GameEngineInput::GetInst()->IsDownKey("ShopUp") && 2 == SelectIndex_)
                {
                    SelectRenderer_->GetTransform().SetWorldMove({0, 50});
                    --SelectIndex_;
                    BuyFont_->SetColor({0.65f, 0.62f, 0.47f, 1.0f});
                    NoFont_->SetColor({0.74f, 0.74f, 0.74f, 1.0f});
                }

                else if (GameEngineInput::GetInst()->IsDownKey("ShopDown") && 1 == SelectIndex_)
                {
                    SelectRenderer_->GetTransform().SetWorldMove({0, -50});
                    ++SelectIndex_;
                    BuyFont_->SetColor({0.74f, 0.74f, 0.74f, 1.0f});
                    NoFont_->SetColor({0.65f, 0.62f, 0.47f, 1.0f});
                }

                if (GameEngineInput::GetInst()->IsDownKey("ShopEnter"))
                {
                    if (1 == SelectIndex_)
                    {
                        if (Info_.ItemPrice_ > Penitent::GetMainPlayer()->GetTear())
                        {
                            return;
                        }

                        Penitent::GetMainPlayer()->GetPlayerUI()->PushBackItem(Info_);
                        IsBuy_ = true;
                    }

                    else if (2 == SelectIndex_)
                    {
                        IsBuy_ = false;
                        Off();
                    }
                }
            }

            if (true == IsBuy_)
            {
                if (nullptr != Merchant_)
                {
                    for (size_t i = 0; i < Merchant_->SellItemList_.size(); i++)
                    {
                        if (nullptr != Merchant_->SellItemList_[i]
                            && Merchant_->SellItemList_[i]->GetItemInfo() == Info_)
                        {
                            Penitent::GetMainPlayer()->MinusTear(Info_.ItemPrice_);

                            Merchant_->SellItemList_[i]->SetIsPlayerCollide(false);
                            Merchant_->SellItemList_[i]->Off();

                            BackgroundRenderer_->Off();
                            HighFrameRenderer_->Off();
                            LowFrameRenderer_->Off();
                            SelectRenderer_->Off();
                            FrameRenderer_->Off();
                            PointRenderer_->Off();
                            IconRenderer_->Off();

                            Font_->Off();
                            BuyFont_->Off();
                            NoFont_->Off();

                            ItemName_->Off();
                            ItemDecs_->Off();

                            AcquiredFont_->On();
                            AcquiredItemName_->On();
                            AcquiredItemName_->SetText(Info_.ItemName_, "NeoµÕ±Ù¸ð");

                            AcquiredFrame_->On();
                            AcquiredIcon_->On();
                            AcquiredIcon_->SetTexture("items-icons-spritesheet.png", Info_.ItemIndex_);
                            AcquiredIcon_->ScaleToCutTexture(Info_.ItemIndex_);
                        }
                    }
                }

                Mode_  = WindowMode::Show;
                IsBuy_ = false;
            }
            break;
        case ItemBuyWindow::WindowMode::Show:
            {
                AlphaTime_ += _DeltaTime;

                if (1.f > AlphaTime_)
                {
                    return;
                }

                float Alpha;

                {
                    Alpha = AcquiredFont_->GetColor().a - _DeltaTime;

                    AcquiredFont_->SetColor(float4{
                        AcquiredFont_->GetColor().r, AcquiredFont_->GetColor().g, AcquiredFont_->GetColor().b, Alpha});
                }

                {
                    Alpha = AcquiredItemName_->GetColor().a - _DeltaTime;

                    AcquiredItemName_->SetColor(float4{AcquiredItemName_->GetColor().r,
                                                       AcquiredItemName_->GetColor().g,
                                                       AcquiredItemName_->GetColor().b,
                                                       Alpha});
                }

                AcquiredFrame_->GetColorData().MulColor.a -= _DeltaTime;
                AcquiredIcon_->GetColorData().MulColor.a -= _DeltaTime;

                if (0.f >= Alpha)
                {
                    AcquiredFont_->SetColor(float4{
                        AcquiredFont_->GetColor().r, AcquiredFont_->GetColor().g, AcquiredFont_->GetColor().b, 1.f});

                    AcquiredItemName_->SetColor(float4{AcquiredItemName_->GetColor().r,
                                                       AcquiredItemName_->GetColor().g,
                                                       AcquiredItemName_->GetColor().b,
                                                       1.f});

                    AcquiredFrame_->GetColorData().MulColor.a = 1.f;
                    AcquiredIcon_->GetColorData().MulColor.a  = 1.f;

                    AcquiredItemName_->Off();
                    AcquiredFrame_->Off();
                    AcquiredFont_->Off();
                    AcquiredIcon_->Off();

                    Mode_ = WindowMode::Buy;
                    Off();
                }
            }
            break;
    }
}


void ItemBuyWindow::End() {}


void ItemBuyWindow::OnEvent()
{
    Mode_        = WindowMode::Buy;
    SelectIndex_ = 1;

    BackgroundRenderer_->On();
    HighFrameRenderer_->On();
    LowFrameRenderer_->On();
    SelectRenderer_->On();
    FrameRenderer_->On();
    PointRenderer_->On();
    IconRenderer_->On();

    Font_->On();
    BuyFont_->On();
    NoFont_->On();

    ItemName_->On();
    ItemDecs_->On();

    AcquiredFont_->SetColor(
        float4{AcquiredFont_->GetColor().r, AcquiredFont_->GetColor().g, AcquiredFont_->GetColor().b, 1.f});

    AcquiredItemName_->SetColor(
        float4{AcquiredItemName_->GetColor().r, AcquiredItemName_->GetColor().g, AcquiredItemName_->GetColor().b, 1.f});

    AcquiredFrame_->GetColorData().MulColor.a = 1.f;
    AcquiredIcon_->GetColorData().MulColor.a  = 1.f;

    AcquiredItemName_->Off();
    AcquiredFrame_->Off();
    AcquiredFont_->Off();
    AcquiredIcon_->Off();

    BuyFont_->SetColor({0.65f, 0.62f, 0.47f, 1.0f});
    NoFont_->SetColor({0.74f, 0.74f, 0.74f, 1.0f});
}


void ItemBuyWindow::OffEvent()
{
    AlphaTime_ = 0.f;

    SelectIndex_ = 1;
    SelectRenderer_->GetTransform().SetWorldPosition({0, 0});
    SelectRenderer_->GetTransform().SetWorldMove({-45, -205});

    BackgroundRenderer_->Off();
    HighFrameRenderer_->Off();
    LowFrameRenderer_->Off();
    SelectRenderer_->Off();
    FrameRenderer_->Off();
    PointRenderer_->Off();
    IconRenderer_->Off();

    Font_->Off();
    BuyFont_->Off();
    NoFont_->Off();

    ItemName_->Off();
    ItemDecs_->Off();

    AcquiredItemName_->Off();
    AcquiredFrame_->Off();
    AcquiredFont_->Off();
    AcquiredIcon_->Off();

    BuyFont_->SetColor({0.74f, 0.74f, 0.74f, 1.0f});
    NoFont_->SetColor({0.74f, 0.74f, 0.74f, 1.0f});
}


void ItemBuyWindow::SetItemInfo(const ItemInfo& _Info)
{
    Info_ = _Info;

    BackgroundRenderer_->On();
    IconRenderer_->SetTexture("items-icons-spritesheet.png", Info_.ItemIndex_);
    IconRenderer_->ScaleToCutTexture(Info_.ItemIndex_);
    IconRenderer_->On();
    FrameRenderer_->On();

    Font_->SetText("Do you want to buy the object for " + std::to_string(Info_.ItemPrice_) + "   ?", "NeoµÕ±Ù¸ð");

    std::string PriceStr = std::to_string(Info_.ItemPrice_);

    PointRenderer_->GetTransform().SetWorldPosition({210.f + (5.f * PriceStr.size()), -120});

    Font_->On();
    PointRenderer_->On();
    SelectRenderer_->On();

    BuyFont_->On();
    NoFont_->On();

    ItemName_->SetText(Info_.ItemName_, "NeoµÕ±Ù¸ð");
    ItemName_->On();

    ItemDecs_->SetText(Info_.ItemDecs_, "NeoµÕ±Ù¸ð");
    ItemDecs_->On();

    LowFrameRenderer_->On();
    HighFrameRenderer_->On();

    AlphaTime_ = 0.f;
}
