#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Candle : public GameEngineActor
{
public:
	Candle();
	~Candle();

	Candle(const Candle& _Other) = delete;
	Candle(Candle&& _Other) noexcept = delete;
	Candle& operator=(const Candle& _Other) = delete;
	Candle& operator=(Candle&& _Other) noexcept = delete;

    inline MetaTextureRenderer* GetMetaRenderer() { return MetaRenderer_; }

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;


private:
    class MetaTextureRenderer* MetaRenderer_;
};

