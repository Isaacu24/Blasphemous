#pragma once
#include <GameEngineCore/GameEngineActor.h>

class JumpCorpseEffecter : public GameEngineActor
{
public:
	JumpCorpseEffecter();
	~JumpCorpseEffecter();

	JumpCorpseEffecter(const JumpCorpseEffecter& _Other) = delete;
	JumpCorpseEffecter(JumpCorpseEffecter&& _Other) noexcept = delete;
	JumpCorpseEffecter& operator=(const JumpCorpseEffecter& _Other) = delete;
	JumpCorpseEffecter& operator=(JumpCorpseEffecter&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:

};

