#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class Stage30 : public GameEngineLevel
{
public:
	Stage30();
	~Stage30();

	Stage30(const Stage30& _Other) = delete;
	Stage30(Stage30&& _Other) noexcept = delete;
	Stage30& operator=(const Stage30& _Other) = delete;
	Stage30& operator=(Stage30&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	GameEngineActor* Stage_;

	class BossMonster* BossMonster_;
	std::list<class MonsterBase*> MonsterList_;
};

