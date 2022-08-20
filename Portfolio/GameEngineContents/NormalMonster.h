#pragma once
#include "MonsterBase.h"
#include <GameEngineCore/GameEngineActor.h>

class Penitent;
class NormalMonster
    : public MonsterBase
    , public GameEngineActor
{
public:
	NormalMonster();
	~NormalMonster();

	NormalMonster(const NormalMonster& _Other) = delete;
	NormalMonster(NormalMonster&& _Other) noexcept = delete;
	NormalMonster& operator=(const NormalMonster& _Other) = delete;
	NormalMonster& operator=(NormalMonster&& _Other) noexcept = delete;

	inline void SetPatrolStart(bool _Start)
	{
		PatrolStart_ = _Start;
	}

	inline void SetPatrolEnd(bool _End)
	{
		PatrolEnd_ = _End;
	}

	//Penitent* GetPlayer();

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

	bool PatrolStart_;
	bool PatrolEnd_;

	bool IsPlayerLeft_;
	bool IsPlayerRight_;

	bool IsCollision_;

	GameEngineCollision* PlayerCollision_;

	virtual void PatrolMoveX(float _DeltaTime) {};
	virtual void PatrolMoveY(float _DeltaTime) {};

	bool LeftObstacleCheck(int _X, int _Y);
	bool RightObstacleCheck(int _X, int _Y);

	virtual bool LookAtPlayer(GameEngineCollision* _This, GameEngineCollision* _Other);
	virtual bool TrackPlayer(GameEngineCollision* _This, GameEngineCollision* _Other);

private:
};

