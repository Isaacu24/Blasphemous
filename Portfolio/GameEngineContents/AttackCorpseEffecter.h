#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineBase/GameEngineRandom.h>
#include "CorpseGroundEffect.h"
#include "Corpse.h"

class GameEngineTextureRenderer;
class AttackCorpseEffecter : public GameEngineActor
{
public:
    AttackCorpseEffecter();
    ~AttackCorpseEffecter();

    AttackCorpseEffecter(const AttackCorpseEffecter& _Other)                = delete;
    AttackCorpseEffecter(AttackCorpseEffecter&& _Other) noexcept            = delete;
    AttackCorpseEffecter& operator=(const AttackCorpseEffecter& _Other)     = delete;
    AttackCorpseEffecter& operator=(AttackCorpseEffecter&& _Other) noexcept = delete;

    inline void SetCreatePos(float4 _Pos) { CreatePos_ = _Pos; }

    inline void CreateEffect()
    {
        float FRandom = GameEngineRandom::MainRandom.RandomFloat(30, 80);

        CorpseGroundEffect* Effect = GetLevel()->CreateActor<CorpseGroundEffect>();
        Effect->GetTransform().SetWorldPosition(
            {CreatePos_.x + ((DirX_ * 30.f) * Index_), CreatePos_.y, BossMonsterEffectZ});

        Corpse* NewCorpse = GetLevel()->CreateActor<Corpse>();
        NewCorpse->SetCreatePos(CreatePos_ + float4{0, FRandom});
        NewCorpse->GetTransform().SetWorldPosition(
            {CreatePos_.x + ((DirX_ * 30.f) * Index_), CreatePos_.y, BossMonsterEffectZ});

        float IRandom = GameEngineRandom::MainRandom.RandomInt(0, 3);
        float XRandom = GameEngineRandom::MainRandom.RandomInt(CreatePos_.x - 50, CreatePos_.x + 50);
        float YRandom = GameEngineRandom::MainRandom.RandomInt(CreatePos_.y - 30, CreatePos_.y + 30);

        if (1 == IRandom)
        {
            Corpse* NewCorpse = GetLevel()->CreateActor<Corpse>();
            NewCorpse->SetCreatePos(CreatePos_ + float4{0, FRandom});
            NewCorpse->GetTransform().SetWorldPosition(
                {CreatePos_.x + XRandom, CreatePos_.y + YRandom, BossMonsterEffectZ});
        }
    }

    inline void SetDir(float _X) { DirX_ = _X; }

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

private:
    float4 CreatePos_;
    float  DelayTime_;

    float DirX_;

    int Index_;

    bool IsCreate_;
};

//����Ʈ ����
//: ��� ������ ������ �ָ� �� �������� �ش� �������� ����Ʈ(������)�� �����Ѵ�.
//�ϴ� �� ����Ʈ�� ���ʷ� �����Ǿ�� �Ѵ�.