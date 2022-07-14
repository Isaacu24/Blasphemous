#pragma once
#include <GameEngineCore/GameEngineLevel.h>

//플레이어가 게임을 시작하는 스테이지
class Stage01 : public GameEngineLevel
{
public:
	Stage01();
	~Stage01();

	Stage01(const Stage01& _Other) = delete;
	Stage01(Stage01&& _Other) noexcept = delete;
	Stage01& operator=(const Stage01& _Other) = delete;
	Stage01& operator=(Stage01&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	class BossMonster* BossMonster_;
	std::list<class MonsterBase*> MonsterList_;
};

