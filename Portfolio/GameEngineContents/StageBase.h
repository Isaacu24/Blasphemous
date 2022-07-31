#pragma once

enum class StageFlow
{
	NORMAL,
	BOSSCOMBAT,
	BOSSDEAD,
	STAGECLEAR
};

class StageBase
{
public:
	StageBase();
	~StageBase();

	StageBase(const StageBase& _Other) = delete;
	StageBase(StageBase&& _Other) noexcept = delete;
	StageBase& operator=(const StageBase& _Other) = delete;
	StageBase& operator=(StageBase&& _Other) noexcept = delete;

	inline void SetState(StageFlow _State)
	{
		CurrentState_ = _State;
	}

	inline StageFlow GetState()
	{
		return CurrentState_;
	}

protected:
	StageFlow CurrentState_;

	GameEngineActor* Stage_;

	GameEngineTextureRenderer* ColMap_;

	class Penitent* Penitent_;

	class BossMonster* BossMonster_;
	std::list<class MonsterBase*> MonsterList_;

	//class LoadingActor* LoadingActor_;

	virtual void SettingStage() = 0;

	virtual void SettingMonster() {};

	float4 PlayerLeftPos_;
	float4 PlayerRightPos_;

	bool IsLeftExit_;
	bool IsRightExit_;

private:

};

