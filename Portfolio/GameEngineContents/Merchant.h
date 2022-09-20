#pragma once
#include "NPCBase.h"

class Item;
class Merchant : public NPCBase
{
    friend class ItemBuyWindow;

public:
    Merchant();
    ~Merchant();

    Merchant(const Merchant& _Other)                = delete;
    Merchant(Merchant&& _Other) noexcept            = delete;
    Merchant& operator=(const Merchant& _Other)     = delete;
    Merchant& operator=(Merchant&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _Update) override;
    void End() override;

    void IdleStart(const StateInfo& _Info);
    void IdleUpdate(float _DeltaTime, const StateInfo& _Info);
    void IdleEnd(const StateInfo& _Info);

    void HitStart(const StateInfo& _Info);
    void HitUpdate(float _DeltaTime, const StateInfo& _Info);
    void HitEnd(const StateInfo& _Info);

    void DeathStart(const StateInfo& _Info);
    void DeathUpdate(float _DeltaTime, const StateInfo& _Info);
    void DeathEnd(const StateInfo& _Info);

private:
    GameEngineStateManager State_;

    class MetaTextureRenderer* MetaRenderer_;
    GameEngineCollision*       BodyCollider_;

    float HP_;

    bool IsHit_;

    class ItemBuyWindow* BuyWindow_;

    std::vector<Item*> SellItemList_;

};
