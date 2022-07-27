#pragma once
#include <GameEngineCore/GameEngineActor.h>

class LeftTopUI : public GameEngineActor
{
	friend class PlayerUI;

public:
	LeftTopUI();
	~LeftTopUI();

	LeftTopUI(const LeftTopUI& _Other) = delete;
	LeftTopUI(LeftTopUI&& _Other) noexcept = delete;
	LeftTopUI& operator=(const LeftTopUI& _Other) = delete;
	LeftTopUI& operator=(LeftTopUI&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	class GameEngineUIRenderer* Renderer_;
};

