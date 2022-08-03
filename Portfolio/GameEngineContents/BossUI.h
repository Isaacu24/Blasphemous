#pragma once
#include <GameEngineCore/GameEngineActor.h>

class BossUI : public GameEngineActor
{
	friend class BossMonster;

public:
	BossUI();
	~BossUI();

	BossUI(const BossUI& _Other) = delete;
	BossUI(BossUI&& _Other) noexcept = delete;
	BossUI& operator=(const BossUI& _Other) = delete;
	BossUI& operator=(BossUI&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	class LeftTopUI* BarFrame_;
	LeftTopUI* HPBar_;

	//class GameEngineFontRenderer* TitleName_;

};

