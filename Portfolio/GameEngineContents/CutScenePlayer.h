#pragma once
#include <GameEngineCore/GameEngineActor.h>
 
enum class CutSceneType
{
	Intro,
	FallPenitent,
	DeadBrotherhood
};

class CutScenePlayer : public GameEngineActor
{
public:
	CutScenePlayer();
	~CutScenePlayer();

	CutScenePlayer(const CutScenePlayer& _Other) = delete;
	CutScenePlayer(CutScenePlayer&& _Other) noexcept = delete;
	CutScenePlayer& operator=(const CutScenePlayer& _Other) = delete;
	CutScenePlayer& operator=(CutScenePlayer&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	class GameEngineTextureRenderer* CutRenderer_;

	CutSceneType CurrentType_;

	float PlayTime_;
	int CurrentFrame_;

private:
	void PalyIntro(float DeltaTime_);
};

