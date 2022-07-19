#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class PlayerFSM
{
	Idle, 
	Run, 
	Fall,
	Slide, //公利 惑怕
	Attack, 
	Parring, //公利 惑怕
	Hit, 
	Death //公利 惑怕
};

class GameEngineTextureRenderer;
class Penitent : public GameEngineActor
{
public:
	Penitent();
	~Penitent();

	Penitent(const Penitent& _Other) = delete;
	Penitent(Penitent&& _Other) noexcept = delete;
	Penitent& operator=(Penitent&& _Other) noexcept = delete;

	inline void SetHP(int _Value)
	{
		HP_ = _Value;
	}

	inline int GetHP()
	{
		return HP_;
	}

	inline void SetMoney(int _Value)
	{
		Money_ = _Value;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void ButtonCheck();

private:
	PlayerFSM PrevState_;
	PlayerFSM CurrentState_;

	GameEngineTextureRenderer* Renderer;

	float4 Time_;

	int HP_;
	int MP_;
	float Speed_;

	int Money_; 

	std::vector<bool> Flasks_;
};

