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

	inline void PatrolStartEnd(bool _Start, bool _End)
    {
        PatrolStart_ = _Start;
        PatrolEnd_   = _End;
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

	GameEngineCollision* PlayerCollision_;

	virtual void PatrolMoveX(float _DeltaTime) {};
	virtual void PatrolMoveY(float _DeltaTime) {};

	bool LeftObstacleCheck(int _X, int _Y);
	bool RightObstacleCheck(int _X, int _Y);

	virtual bool LookAtPlayer(GameEngineCollision* _This, GameEngineCollision* _Other);
	virtual bool TrackPlayer(GameEngineCollision* _This, GameEngineCollision* _Other);

	virtual void DamageCheck(){};

private:
};

