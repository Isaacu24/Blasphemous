#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class Stage20 : public GameEngineLevel
{
public:
	Stage20();
	~Stage20();

	Stage20(const Stage20& _Other) = delete;
	Stage20(Stage20&& _Other) noexcept = delete;
	Stage20& operator=(const Stage20& _Other) = delete;
	Stage20& operator=(Stage20&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	GameEngineActor* Stage_;

	class BossMonster* BossMonster_;
	std::list<class MonsterBase*> MonsterList_;
};

