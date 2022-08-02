#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineStateManager.h>

class BloodSplatters : public GameEngineActor
{
public:
	BloodSplatters();
	~BloodSplatters();

	BloodSplatters(const BloodSplatters& _Other) = delete;
	BloodSplatters(BloodSplatters&& _Other) noexcept = delete;
	BloodSplatters& operator=(const BloodSplatters& _Other) = delete;
	BloodSplatters& operator=(BloodSplatters&& _Other) noexcept = delete;

	void FristStart(const StateInfo& _Info);
	void FristUpdate(float _DeltaTime, const StateInfo& _Info);

	void SecondStart(const StateInfo& _Info);
	void SecondUpdate(float _DeltaTime, const StateInfo& _Info);

	void ThridStart(const StateInfo& _Info);
	void ThridUpdate(float _DeltaTime, const StateInfo& _Info);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	GameEngineStateManager State_;

	class GameEngineTextureRenderer* Renderer_;

};

