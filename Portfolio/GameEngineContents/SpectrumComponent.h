#pragma once
#include <GameEngineCore/GameEngineComponent.h>

class SpectrumComponent : public GameEngineTransformComponent
{
public:
    SpectrumComponent();
    ~SpectrumComponent();

    SpectrumComponent(const SpectrumComponent& _Other)                = delete;
    SpectrumComponent(SpectrumComponent&& _Other) noexcept            = delete;
    SpectrumComponent& operator=(const SpectrumComponent& _Other)     = delete;
    SpectrumComponent& operator=(SpectrumComponent&& _Other) noexcept = delete;

    void CreateSpectrum(const std::string& _Name, const FrameAnimation_DESC& _Info);

    void CreateMetaSpectrum(const std::string& _Name, const FrameAnimation_DESC& _Info);

    void CreateOnceSpectrum(const std::string& _Name, const FrameAnimation_DESC& _Info, size_t _Size);

    void DrawSpectrum(float _DeltaTime);
    void DrawMetaSpectrum(float _DeltaTime);

    void SetSpectrumFrame(size_t Start, size_t End);
    void SetMetaSpectrumFrame(size_t Start, size_t End);

    void SetOnceSpectrumFrame(size_t _Length);

    inline void SetIsDraw(bool _Draw) { IsDraw_ = _Draw; }

    inline void SetIsMetaDraw(bool _Draw) { IsMetaDraw_ = _Draw; }

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

private:
    std::vector<class GameEngineTextureRenderer*> Spectrums_;
    std::vector<class MetaTextureRenderer*>       MetaSpectrums_;

    std::vector<GameEngineActor*> SpectrumActors_;

    bool IsDraw_;
    bool IsMetaDraw_;

    float DrawTime_;
    float DisAppearTime_;

    int SpectrumSize_;  //만들어지길 원하는 잔상의 수
    int Index_;

    bool IsMetaDisAppear_;
    bool IsDisAppear_;
};