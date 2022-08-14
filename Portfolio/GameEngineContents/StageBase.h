#pragma once

enum class STAGEFLOW
{
	NORMAL,
	BOSSAPPEAR,
	BOSSCOMBAT,
	BOSSDEAD,
	STAGECLEAR
};

class GameEngineCollision;
class StageBase
{
public:
	StageBase();
	~StageBase();

	StageBase(const StageBase& _Other) = delete;
	StageBase(StageBase&& _Other) noexcept = delete;
	StageBase& operator=(const StageBase& _Other) = delete;
	StageBase& operator=(StageBase&& _Other) noexcept = delete;

	inline void SetFlow(STAGEFLOW _State)
	{
		CurrentFlow_ = _State;
	}

	inline STAGEFLOW GetFlow()
	{
		return	CurrentFlow_;
	}

protected:
	STAGEFLOW CurrentFlow_;

	GameEngineActor* Stage_;

	float4 CurPos_;
	float4 PrevPos_;

	GameEngineTextureRenderer* ColMap_;

	std::vector<GameEngineCollision*> DangleColiders_;

	class Penitent* Penitent_;

	class BossMonster* BossMonster_;
	std::list<class MonsterBase*> MonsterList_;

	class LoadingActor* LoadingActor_;

	virtual void SettingStage() = 0;

	virtual void SettingMonster(){};

	float4 PlayerLeftPos_;
	float4 PlayerRightPos_;

	bool IsLeftExit_;
	bool IsRightExit_;

	float CameraZPos_;

	bool IsChangeCameraPos_;

	class GameEngineFontRenderer* Font_;

	float CameraOffset_;

	bool IsEvent_;


private:

};

