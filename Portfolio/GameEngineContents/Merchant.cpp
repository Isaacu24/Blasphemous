#include "PreCompile.h"
#include "Merchant.h"
#include "MetaSpriteManager.h"
#include "MetaTextureRenderer.h"
#include "ItemBuyWindow.h"
#include "MonsterHitEffect.h"
#include "BloodSplatters.h"

Merchant::Merchant()
    : HP_(100)
{}

Merchant::~Merchant() {}

void Merchant::Start()
{
    GetTransform().SetWorldScale({2, 2, 1});

    MetaRenderer_ = CreateComponent<MetaTextureRenderer>();

    HitEffect_ = GetLevel()->CreateActor<MonsterHitEffect>();

    BloodEffect_ = GetLevel()->CreateActor<BloodSplatters>();
    BloodEffect_->GetRenderer()->Off();


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
                                            Penitent::GetMainPlayer()->PlusTear(5000);
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
                                 "패왕의 알이라 불리우는 알.\n눈코입이 제멋대로 붙어있다.",
                                 100});

        NewItem->GetTransform().SetWorldPosition({830, -580, ObjectZ});

        SellItemList_.push_back(NewItem);
    }

    {
        Item* NewItem = GetLevel()->CreateActor<Item>();
        NewItem->GetItemRenderer()->SetTexture("items-icons-spritesheet.png", 106);
        NewItem->GetItemRenderer()->ScaleToCutTexture(106);
        NewItem->CreateItemInfo(
            {87, ItemType::Relics, "오레스테스의 변형된 가면", "꿈의 세계에서 죽은 대주교의\n손에서 발견된 유물.", 500});

        NewItem->GetTransform().SetWorldPosition({950, -580, ObjectZ});
        SellItemList_.push_back(NewItem);
    }

    {
        Item* NewItem = GetLevel()->CreateActor<Item>();
        NewItem->GetItemRenderer()->SetTexture("items-icons-spritesheet.png", 112);
        NewItem->GetItemRenderer()->ScaleToCutTexture(112);
        NewItem->CreateItemInfo(
            {64, ItemType::Relics, "잘린 손", "방울을 꼭 쥐고 있는 잘린 손.\n가끔 경미한 경련을 일으킨다.", 100});

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

        float4 HitPos = BodyCollider_->GetTransform().GetWorldPosition();

        HitEffect_->GetTransform().SetWorldPosition({HitPos.x, HitPos.y, NPCZ});
        HitEffect_->ShowHitEffet();

        BloodEffect_->GetRenderer()->On();
        BloodEffect_->GetTransform().SetWorldPosition({HitPos.x + 50.f, HitPos.y, NPCZ});
        BloodEffect_->GetRenderer()->ChangeFrameAnimation("BloodSplattersV3");

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
                if (true == GameEngineInput::GetInst()->IsDownKey("Interaction") && false == BuyWindow_->IsUpdate()
                    || true == GameEngineInput::GetInst()->IsDownButton("PenitentY") && false == BuyWindow_->IsUpdate())
                {
                    BuyWindow_->On();
                    BuyWindow_->SetItemInfo(SellItemList_[i]->GetItemInfo());
                    return;
                }

                else if (true == GameEngineInput::GetInst()->IsDownKey("Escape") && true == BuyWindow_->IsUpdate()
                         || true == GameEngineInput::GetInst()->IsDownButton("PenitentB")
                                && true == BuyWindow_->IsUpdate())
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
