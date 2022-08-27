#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Corpse;
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

    inline void CreateEffect() { IsCreate_ = true; }

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