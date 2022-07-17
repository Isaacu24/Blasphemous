#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class Stage21 : public GameEngineLevel
{
public:
	Stage21();
	~Stage21();

	Stage21(const Stage21& _Other) = delete;
	Stage21(Stage21&& _Other) noexcept = delete;
	Stage21& operator=(const Stage21& _Other) = delete;
	Stage21& operator=(Stage21&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	GameEngineActor* Stage_;

	class BossMonster* BossMonster_;
	std::list<class MonsterBase*> MonsterList_;
};
