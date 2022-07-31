#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "BossMonster.h"

enum class PopeState
{
	Idle,
	Appear, //����
	Vanishing, //�����
	SpellCast,
	Hit,
	Death
};

//ù ��° ��Ȳ
class Pope : public GameEngineActor, public BossMonster
{
public:
	Pope();
	~Pope();

	Pope(const Pope& _Other) = delete;
	Pope(Pope&& _Other) noexcept = delete;
	Pope& operator=(const Pope& _Other) = delete;
	Pope& operator=(Pope&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	PopeState CurrentState_;
};

