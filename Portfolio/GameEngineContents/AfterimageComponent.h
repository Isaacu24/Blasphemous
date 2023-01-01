#pragma once
#include <GameEngineCore/GameEngineTransformComponent.h>

class AfterimageComponent : public GameEngineTransformComponent
{
public:
    AfterimageComponent();
    ~AfterimageComponent();

    AfterimageComponent(const AfterimageComponent& _Other)                = delete;
    AfterimageComponent(AfterimageComponent&& _Other) noexcept            = delete;
    AfterimageComponent& operator=(const AfterimageComponent& _Other)     = delete;
    AfterimageComponent& operator=(AfterimageComponent&& _Other) noexcept = delete;

    virtual void CreateAfterimage(const std::string& _Name, const FrameAnimation_DESC& _Info);
    virtual void CreateOnceAfterimage(const std::string& _Name, const FrameAnimation_DESC& _Info, size_t _Size);

    virtual void DrawAfterimage(float _DeltaTime);
    virtual void SetAfterimageFrame(size_t Start, size_t End);

    void SetOnceAfterimageFrame(size_t _Length);

    inline void SetIsDraw(bool _Draw) { IsDraw_ = _Draw; }

    virtual void AfterimageLevelOn() 
    {
        for (size_t i = 0; i < AfterimageActors_.size(); i++)
        {
            AfterimageActors_[i]->SetLevelOverOn();
        }
    }

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

    std::vector<class GameEngineTextureRenderer*> Afterimages_;

    std::vector<GameEngineActor*> AfterimageActors_;

    bool IsDraw_;

    float DrawTime_;
    float DisAppearTime_;

    size_t AfterimageSize_;  //만들어지길 원하는 잔상의 수
    int Index_;
    
private:
};