#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineTextureRenderer;
class TitleActor : public GameEngineActor
{
public:
	TitleActor();
	~TitleActor();

	TitleActor(const TitleActor& _Other) = delete;
	TitleActor(TitleActor&& _Other) noexcept = delete;
	TitleActor& operator=(const TitleActor& _Other) = delete;
	TitleActor& operator=(TitleActor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	GameEngineUIRenderer* ButttonShadow_;
	GameEngineUIRenderer* PressAnyKey_;

	GameEngineUIRenderer* GameLogo_;

	GameEngineUIRenderer* DescRenderer_;

	bool IsReverse_;
	bool IsDown_;
    bool IsChage_;

	float Alpha_;

	float ChangeTime_;


};

