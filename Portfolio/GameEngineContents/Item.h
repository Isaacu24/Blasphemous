#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class ItemType
{
    RosaryBeads,     //묵주
    Relics,          //유물
    QuestItem,       //퀘스트 아이템
    MeaCulpaHearts,  //메아 쿨파 심장
    Prayers,         //기도
    Abilities,       //능력
    Collectibles     //수집품
};

struct ItemInfo
{
    int         ItemIndex_;
    ItemType    ItemType_;
    std::string ItemName_;
    std::string ItemDecs_;
    int         ItemPrice_;

    ItemInfo()
        : ItemIndex_(0)
        , ItemType_(ItemType::Abilities)
        , ItemName_{}
        , ItemDecs_{}
        , ItemPrice_(0)
    {}

    ItemInfo(int _Index, ItemType _Type, const std::string& _Name, const std::string& _Decs, int _Price)
        : ItemIndex_(_Index)
        , ItemType_(_Type)
        , ItemName_{_Name}
        , ItemDecs_{_Decs}
        , ItemPrice_(_Price)
    {}

    ~ItemInfo(){};

    bool operator==(const ItemInfo& _Info)
    {
        if (ItemIndex_ != _Info.ItemIndex_)
        {
            return false;
        }

        if (ItemType_ != _Info.ItemType_)
        {
            return false;
        }

        if (ItemName_ != _Info.ItemName_)
        {
            return false;
        }

        if (ItemDecs_ != _Info.ItemDecs_)
        {
            return false;
        }

        if (ItemPrice_ != _Info.ItemPrice_)
        {
            return false;
        }

        return true;
    }

     bool operator!=(const ItemInfo& _Info)
    {
        if (ItemIndex_ == _Info.ItemIndex_)
        {
            return false;
        }

        if (ItemType_ == _Info.ItemType_)
        {
            return false;
        }

        if (ItemName_ == _Info.ItemName_)
        {
            return false;
        }

        if (ItemDecs_ == _Info.ItemDecs_)
        {
            return false;
        }

        if (ItemPrice_ == _Info.ItemPrice_)
        {
            return false;
        }

        return true;
    }
};

//스킬도 포함
class Item : public GameEngineActor
{
public:
    Item();
    ~Item();

    Item(const Item& _Other)                = delete;
    Item(Item&& _Other) noexcept            = delete;
    Item& operator=(const Item& _Other)     = delete;
    Item& operator=(Item&& _Other) noexcept = delete;

    void CreateItemInfo(const ItemInfo& _Info) { Info_ = _Info; }

    GameEngineTextureRenderer* GetItemRenderer() { return ItemRenderer_; }

    void PlayerCheck();

    bool GetIsPlayerCollide() { return IsPlayerCollide_; }

    void SetIsPlayerCollide(bool _Value) { IsPlayerCollide_ = _Value; }

    const ItemInfo& GetItemInfo() { return Info_; }

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

private:
    GameEngineTextureRenderer* UIRenderer_;

    GameEngineTextureRenderer* ItemRenderer_;
    GameEngineCollision*       ItemCollider_;

    ItemInfo Info_;

    bool IsPlayerCollide_;
};
