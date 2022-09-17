#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class ObjectType
{
    NPC,
    Door,
    OpenDoor,
    PrieDieu,
    Guilt
};

class ObjectBase : public GameEngineActor
{
public:
    ObjectBase();
    ~ObjectBase();

    ObjectBase(const ObjectBase& _Other)                = delete;
    ObjectBase(ObjectBase&& _Other) noexcept            = delete;
    ObjectBase& operator=(const ObjectBase& _Other)     = delete;
    ObjectBase& operator=(ObjectBase&& _Other) noexcept = delete;

    inline void SetObjectType(ObjectType _Type) { MyType_ = _Type; }

    inline ObjectType GetObjectType() { return MyType_; }

protected:
    void Start() = 0;
    void Update(float _DeltaTime) override;
    void End() override;

    class GameEngineCollision*       UICollider_;
    class GameEngineTextureRenderer* UIRenderer_;

    bool Interaction_;

private:
    ObjectType MyType_;
};
