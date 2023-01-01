#pragma once
#include "AfterimageComponent.h"

class MetaAfterimageComponent : public AfterimageComponent
{
public:
	MetaAfterimageComponent();
	~MetaAfterimageComponent();

	MetaAfterimageComponent(const MetaAfterimageComponent& _Other) = delete;
	MetaAfterimageComponent(MetaAfterimageComponent&& _Other) noexcept = delete;
	MetaAfterimageComponent& operator=(const MetaAfterimageComponent& _Other) = delete;
	MetaAfterimageComponent& operator=(MetaAfterimageComponent&& _Other) noexcept = delete;

    void CreateAfterimage(const std::string& _Name, const FrameAnimation_DESC& _Info) override;

	void DrawAfterimage(float _DeltaTime) override;
    void SetAfterimageFrame(size_t Start, size_t End) override;

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

private:
    std::vector<class MetaTextureRenderer*> MetaAfterimages_;
};

