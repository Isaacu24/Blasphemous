#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "NormalMonster.h"

class WingedFace : public GameEngineActor, public NormalMonster
{
public:
	WingedFace();
	~WingedFace();

	WingedFace(const WingedFace& _Other) = delete;
	WingedFace(WingedFace&& _Other) noexcept = delete;
	WingedFace& operator=(const WingedFace& _Other) = delete;
	WingedFace& operator=(WingedFace&& _Other) noexcept = delete;

	void PatrolStart(const StateInfo& _Info);
	void PatrolUpdate(float _DeltaTime, const StateInfo& _Info);

	void ShootStart(const StateInfo& _Info);
	void ShootUpdate(float _DeltaTime, const StateInfo& _Info);

	void DeathStart(const StateInfo& _Info);
	void DeathUpdate(float _DeltaTime, const StateInfo& _Info);

	inline void SetStartPos(float _Pos)
	{
		StartPos_ = _Pos;
	}

	inline void SetEndPos(float _Pos)
	{
		EndPos_ = _Pos;
	}

	inline void DeathEnd(const FrameAnimation_DESC& _Info)
	{
		Death();
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void PatrolMoveX(float _DeltaTime) override;
	void PatrolMoveY(float _DeltaTime) override;

private:
	float StartPos_;
	float EndPos_;
};


