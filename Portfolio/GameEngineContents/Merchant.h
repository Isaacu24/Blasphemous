#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Merchant : public GameEngineActor
{
public:
	Merchant();
	~Merchant();

	Merchant(const Merchant& _Other) = delete;
	Merchant(Merchant&& _Other) noexcept = delete;
	Merchant& operator=(const Merchant& _Other) = delete;
	Merchant& operator=(Merchant&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _Update) override;
    void End() override;

private:
    class MetaTextureRenderer* MetaRenderer_;

};

