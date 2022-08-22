#pragma once
#include <GameEngineCore/GameEngineActor.h>

class SideFence : public GameEngineActor
{
public:
    SideFence();
    ~SideFence();

    SideFence(const SideFence& _Other)                = delete;
    SideFence(SideFence&& _Other) noexcept            = delete;
    SideFence& operator=(const SideFence& _Other)     = delete;
    SideFence& operator=(SideFence&& _Other) noexcept = delete;

    void OpenStart(const StateInfo& _Info);
    void OpenUpdate(float _DeltaTime, const StateInfo& _Info);
    void OpenEnd(const StateInfo& _Info);

    void CloseStart(const StateInfo& _Info);
    void CloseUpdate(float _DeltaTime, const StateInfo& _Info);
    void CloseEnd(const StateInfo& _Info);

    void DescendingStart(const StateInfo& _Info);
    void DescendingUpdate(float _DeltaTime, const StateInfo& _Info);
    void DescendingEnd(const StateInfo& _Info);

    inline void SetFenceState(const std::string& _Name) { State_.ChangeState(_Name); }

    bool GetIsClose()
    { 
        return IsClose_;
    }

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

private:
    GameEngineStateManager State_;
    // std::string PrevState_;

    bool IsClose_;

    GameEngineTextureRenderer* Rendrerer_;
    GameEngineCollision*       Collider_;
};
