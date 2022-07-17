#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class Stage10 : public GameEngineLevel
{
public:
	Stage10();
	~Stage10();

	Stage10(const Stage10& _Other) = delete;
	Stage10(Stage10&& _Other) noexcept = delete;
	Stage10& operator=(const Stage10& _Other) = delete;
	Stage10& operator=(Stage10&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	GameEngineActor* Stage_;

	class BossMonster* BossMonster_;
	std::list<class MonsterBase*> MonsterList_;
};

