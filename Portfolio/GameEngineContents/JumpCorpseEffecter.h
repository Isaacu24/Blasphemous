#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineBase/GameEngineRandom.h>

class JumpCorpseEffecter : public GameEngineActor
{
public:
	JumpCorpseEffecter();
	~JumpCorpseEffecter();

	JumpCorpseEffecter(const JumpCorpseEffecter& _Other) = delete;
	JumpCorpseEffecter(JumpCorpseEffecter&& _Other) noexcept = delete;
	JumpCorpseEffecter& operator=(const JumpCorpseEffecter& _Other) = delete;
	JumpCorpseEffecter& operator=(JumpCorpseEffecter&& _Other) noexcept = delete;

	void SetCreatePos(float4 _Pos)
	{
		CreatePos_ = _Pos;
	}

	void CreateEffect()
	{
		IsEffect_ = true;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	GameEngineRandom Random_;	
	int Index_;

	float4 CreatePos_;

	bool IsEffect_;

	float DelayTime_;
};

