#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Merchant;
class ItemBuyWindow : public GameEngineActor
{
public:
    enum class WindowMode
    {
        Buy,
        Show
    };

public:
    ItemBuyWindow();
    ~ItemBuyWindow();

    ItemBuyWindow(const ItemBuyWindow& _Other)                = delete;
    ItemBuyWindow(ItemBuyWindow&& _Other) noexcept            = delete;
    ItemBuyWindow& operator=(const ItemBuyWindow& _Other)     = delete;
    ItemBuyWindow& operator=(ItemBuyWindow&& _Other) noexcept = delete;

    void SetItemInfo(const ItemInfo& _Info);

    void SetMerchant(Merchant* _Merchant) { Merchant_ = _Merchant; }

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

    void OnEvent() override;
    void OffEvent() override;

private:
    WindowMode Mode_;

    Merchant* Merchant_;

    GameEngineUIRenderer* PointRenderer_;
    GameEngineUIRenderer* FrameRenderer_;
    GameEngineUIRenderer* IconRenderer_;

    GameEngineUIRenderer* SelectRenderer_;

    GameEngineUIRenderer* BackgroundRenderer_;
    GameEngineUIRenderer* HighFrameRenderer_;
    GameEngineUIRenderer* LowFrameRenderer_;

    GameEngineFontRenderer* Font_;
    GameEngineFontRenderer* BuyFont_;
    GameEngineFontRenderer* NoFont_;

    int SelectIndex_;

    GameEngineFontRenderer* ItemName_;
    GameEngineFontRenderer* ItemDecs_;

    GameEngineFontRenderer* AcquiredFont_;
    GameEngineFontRenderer* AcquiredItemName_;

    GameEngineUIRenderer* AcquiredIcon_;
    GameEngineUIRenderer* AcquiredFrame_;

    ItemInfo Info_;

    bool IsBuy_;

    float AlphaTime_;
    
	bool  IsPadInput_;
    float PadDelayTime_;

    SHORT ThumbLY_;
};
