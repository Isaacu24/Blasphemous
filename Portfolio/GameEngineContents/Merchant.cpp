#include "PreCompile.h"
#include "Merchant.h"
#include "MetaSpriteManager.h"
#include "MetaTextureRenderer.h"
#include "ItemBuyWindow.h"

Merchant::Merchant()
    : HP_(100)
{}

Merchant::~Merchant() {}

void Merchant::Start()
{
    GetTransform().SetWorldScale({2, 2, 1});

    MetaRenderer_ = CreateComponent<MetaTextureRenderer>();

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("ladrona_idle_anim");

        MetaRenderer_->CreateMetaAnimation(
            "ladrona_idle_anim",
            {"ladrona_idle_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.1f, true},
            Data);
    }

    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("ladrona_death_anim_0");

        MetaRenderer_->CreateMetaAnimation(
            "ladrona_death_anim_0",
            {"ladrona_death_anim_0.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.1f, false},
            Data);

        MetaRenderer_->AnimationBindEnd("ladrona_death_anim_0",
                                        [&](const FrameAnimation_DESC& _Info)
                                        {
                                            Penitent::GetMainPlayer()->SetTear(5000.f);
                                            BodyCollider_->Death();
                                            BuyWindow_->Death();
                                        });
    }


    {
        std::vector<MetaData> Data = MetaSpriteManager::Inst_->Find("ladrona_hit_reaction_anim");

        MetaRenderer_->CreateMetaAnimation(
            "ladrona_hit_reaction_anim",
            {"ladrona_hit_reaction_anim.png", 0, static_cast<unsigned int>(Data.size() - 1), 0.1f, false},
            Data);

        MetaRenderer_->AnimationBindEnd("ladrona_hit_reaction_anim",
                                        [&](const FrameAnimation_DESC& _Info) { State_.ChangeState("Idle"); });
    }

    MetaRenderer_->ChangeMetaAnimation("ladrona_idle_anim");
    MetaRenderer_->SetPivot(PIVOTMODE::METABOT);

    BodyCollider_ = CreateComponent<GameEngineCollision>();
    BodyCollider_->GetTransform().SetWorldScale({40.f, 80.f, 1.f});
    BodyCollider_->ChangeOrder(COLLISIONORDER::MonsterBody);
    BodyCollider_->SetDebugSetting(CollisionType::CT_OBB2D, float4{0.0f, 0.0f, 1.0f, 0.5f});
    BodyCollider_->GetTransform().SetWorldMove({0, 30});

    State_.CreateStateMember("Idle",
                             std::bind(&Merchant::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Merchant::IdleStart, this, std::placeholders::_1),
                             std::bind(&Merchant::IdleEnd, this, std::placeholders::_1));

    State_.CreateStateMember("Hit",
                             std::bind(&Merchant::HitUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Merchant::HitStart, this, std::placeholders::_1),
                             std::bind(&Merchant::HitEnd, this, std::placeholders::_1));

    State_.CreateStateMember("Death",
                             std::bind(&Merchant::DeathUpdate, this, std::placeholders::_1, std::placeholders::_2),
                             std::bind(&Merchant::DeathStart, this, std::placeholders::_1),
                             std::bind(&Merchant::DeathEnd, this, std::placeholders::_1));

    State_.ChangeState("Idle");


    {
        Item* NewItem = GetLevel()->CreateActor<Item>();
        NewItem->GetItemRenderer()->SetTexture("items-icons-spritesheet.png", 212);
        NewItem->GetItemRenderer()->ScaleToCutTexture(212);
        NewItem->CreateItemInfo({212,
                                 ItemType::Relics,
                                 "진홍의 베헤리트",
                                 "가나다라마바사 아자차카타파하\n아에이오우 아야어여오요우유.",
                                 100});

        NewItem->GetTransform().SetWorldPosition({830, -580, ObjectZ});

        SellItemList_.push_back(NewItem);
    }

    {
        Item* NewItem = GetLevel()->CreateActor<Item>();
        NewItem->GetItemRenderer()->SetTexture("items-icons-spritesheet.png", 87);
        NewItem->GetItemRenderer()->ScaleToCutTexture(87);
        NewItem->CreateItemInfo(
            {87, ItemType::Relics, "Crimson Beherit", "Crimsoasdfdsafasfdsfdsafdsfn Beherit.", 1000});

        NewItem->GetTransform().SetWorldPosition({950, -580, ObjectZ});
        SellItemList_.push_back(NewItem);
    }

    {
        Item* NewItem = GetLevel()->CreateActor<Item>();
        NewItem->GetItemRenderer()->SetTexture("items-icons-spritesheet.png", 64);
        NewItem->GetItemRenderer()->ScaleToCutTexture(64);
        NewItem->CreateItemInfo(
            {64, ItemType::Relics, "Crimson Beherit", "Crimsafawdfdsfdsafasdfsdafdsfon Beherit.", 100});

        NewItem->GetTransform().SetWorldPosition({1080, -580, ObjectZ});
        SellItemList_.push_back(NewItem);
    }

    BuyWindow_ = GetLevel()->CreateActor<ItemBuyWindow>();
    BuyWindow_->SetMerchant(this);
    BuyWindow_->Off();
}

void Merchant::Update(float _Update)
{
    State_.Update(_Update);

    if ("Death" == State_.GetCurStateStateName())
    {
        return;
    }

    if (false
        == BodyCollider_->IsCollision(
            CollisionType::CT_OBB2D, COLLISIONORDER::PlayerAttack, CollisionType::CT_OBB2D, nullptr))
    {
        IsHit_ = false;

        MetaRenderer_->GetColorData().PlusColor = float4{0.0f, 0.0f, 0.0f, 0.0f};
    }

    if (true == IsHit_)
    {
        return;
    }

    if (true
        == BodyCollider_->IsCollision(
            CollisionType::CT_OBB2D, COLLISIONORDER::PlayerAttack, CollisionType::CT_OBB2D, nullptr))
    {
        IsHit_ = true;
        State_.ChangeState("Hit");

        HP_ -= 50.f;

        MetaRenderer_->GetColorData().PlusColor = float4{1.5f, 1.5f, 1.5f, 0.0f};
    }

    if (0 >= HP_)
    {
        State_.ChangeState("Death");
    }
}

void Merchant::End() {}


void Merchant::IdleStart(const StateInfo& _Info) { MetaRenderer_->ChangeMetaAnimation("ladrona_idle_anim"); }

void Merchant::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
    for (size_t i = 0; i < SellItemList_.size(); i++)
    {
        if (nullptr != SellItemList_[i])
        {
            if (true == SellItemList_[i]->GetIsPlayerCollide())
            {
                if (true == GameEngineInput::GetInst()->IsDownKey("Interaction"))
                {
                    BuyWindow_->On();
                    BuyWindow_->SetItemInfo(SellItemList_[i]->GetItemInfo());
                }

                else if (true == GameEngineInput::GetInst()->IsDownKey("Escape"))
                {
                    BuyWindow_->Off();
                }
            }
        }
    }
}

void Merchant::IdleEnd(const StateInfo& _Info) {}


void Merchant::HitStart(const StateInfo& _Info) { MetaRenderer_->ChangeMetaAnimation("ladrona_hit_reaction_anim"); }

void Merchant::HitUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Merchant::HitEnd(const StateInfo& _Info) {}


void Merchant::DeathStart(const StateInfo& _Info)
{
    MetaRenderer_->ChangeMetaAnimation("ladrona_death_anim_0");
    MetaRenderer_->GetColorData().PlusColor = float4{0.0f, 0.0f, 0.0f, 0.0f};

    BodyCollider_->Off();

    for (size_t i = 0; i < SellItemList_.size(); i++)
    {
        if (true == SellItemList_[i]->IsUpdate())
        {
            SellItemList_[i]->GetItemCollsion()->Off();
        }
    }
}

void Merchant::DeathUpdate(float _DeltaTime, const StateInfo& _Info) {}

void Merchant::DeathEnd(const StateInfo& _Info) {}
