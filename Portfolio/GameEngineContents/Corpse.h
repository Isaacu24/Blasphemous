#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineTextureRenderer;
class Corpse : public GameEngineActor
{
public:
	Corpse();
	~Corpse();

	Corpse(const Corpse& _Other) = delete;
	Corpse(Corpse&& _Other) noexcept = delete;
	Corpse& operator=(const Corpse& _Other) = delete;
	Corpse& operator=(Corpse&& _Other) noexcept = delete;

	void FloatCorpse(float _DeltaTime);

	inline void SetCreatePos(float4 _Pos)
	{
		CreatePos_ = _Pos;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	GameEngineTextureRenderer* Renderer_;

	float4 CreatePos_;
	bool IsSolstice_;

	inline void CorpseEnd(const FrameAnimation_DESC& _Info, Corpse* _Corpse)
	{
		_Corpse->Death();
	}
};

