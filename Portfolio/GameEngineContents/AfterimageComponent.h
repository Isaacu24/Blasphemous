#pragma once
#include <GameEngineCore/GameEngineComponent.h>

class AfterimageComponent : public GameEngineTransformComponent
{
public:
    AfterimageComponent();
    ~AfterimageComponent();

    AfterimageComponent(const AfterimageComponent& _Other)                = delete;
    AfterimageComponent(AfterimageComponent&& _Other) noexcept            = delete;
    AfterimageComponent& operator=(const AfterimageComponent& _Other)     = delete;
    AfterimageComponent& operator=(AfterimageComponent&& _Other) noexcept = delete;

    void CreateAfterimage(const std::string& _Name, const FrameAnimation_DESC& _Info);

    void CreateMetaAfterimage(const std::string& _Name, const FrameAnimation_DESC& _Info);

    void CreateOnceAfterimage(const std::string& _Name, const FrameAnimation_DESC& _Info, size_t _Size);

    void DrawAfterimage(float _DeltaTime);
    void DrawMetaAfterimage(float _DeltaTime);

    void SetAfterimageFrame(size_t Start, size_t End);
    void SetMetaAfterimageFrame(size_t Start, size_t End);

    void SetOnceAfterimageFrame(size_t _Length);

    inline void SetIsDraw(bool _Draw) { IsDraw_ = _Draw; }

    inline void SetIsMetaDraw(bool _Draw) { IsMetaDraw_ = _Draw; }

    void AfterimageLevelOn() 
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

private:
    std::vector<class GameEngineTextureRenderer*> Afterimages_;
    std::vector<class MetaTextureRenderer*>       MetaAfterimages_;

    std::vector<GameEngineActor*> AfterimageActors_;

    bool IsDraw_;
    bool IsMetaDraw_;

    float DrawTime_;
    float DisAppearTime_;

    size_t AfterimageSize_;  //��������� ���ϴ� �ܻ��� ��
    int Index_;
};