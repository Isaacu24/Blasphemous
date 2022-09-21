#pragma once
#include <GameEngineCore/GameEngineActor.h>

class ShopObejct : public GameEngineActor
{
public:
	ShopObejct();
	~ShopObejct();

	ShopObejct(const ShopObejct& _Other) = delete;
	ShopObejct(ShopObejct&& _Other) noexcept = delete;
	ShopObejct& operator=(const ShopObejct& _Other) = delete;
	ShopObejct& operator=(ShopObejct&& _Other) noexcept = delete;

    inline MetaTextureRenderer* GetMetaRenderer() { return MetaRenderer_; }

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

private:
    class MetaTextureRenderer* MetaRenderer_;
};

