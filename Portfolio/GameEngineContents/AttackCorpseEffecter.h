#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Corpse;
class GameEngineTextureRenderer;
class AttackCorpseEffecter : public GameEngineActor
{
public:
	AttackCorpseEffecter();
	~AttackCorpseEffecter();

	AttackCorpseEffecter(const AttackCorpseEffecter& _Other) = delete;
	AttackCorpseEffecter(AttackCorpseEffecter&& _Other) noexcept = delete;
	AttackCorpseEffecter& operator=(const AttackCorpseEffecter& _Other) = delete;
	AttackCorpseEffecter& operator=(AttackCorpseEffecter&& _Other) noexcept = delete;

	inline void SetCreatePos(float4 _Pos, float4 _Dir)
	{
		CreatePos_ = _Pos;
		Dir_ = _Dir;
	}

	inline void CreateEffect()
	{
		IsCreate_ = true;
	}

protected:	
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	float4 CreatePos_;
	float DelayTime_;

	float4 Dir_;

	int Index_;

	bool IsCreate_;
};

//이펙트 구조
//: 어느 기점과 방향을 주면 그 기점부터 해당 방향으로 이펙트(렌더러)를 생성한다.
//일단 빔 이펙트가 차례로 생성되어야 한다.