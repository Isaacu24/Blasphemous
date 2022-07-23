#pragma once

class StageBase
{
public:
	StageBase();
	~StageBase();

	StageBase(const StageBase& _Other) = delete;
	StageBase(StageBase&& _Other) noexcept = delete;
	StageBase& operator=(const StageBase& _Other) = delete;
	StageBase& operator=(StageBase&& _Other) noexcept = delete;

protected:
	GameEngineActor* Stage_;

	class GameEngineCameraActor* CameraActor_;
	class Penitent* Penitent_;

	class BossMonster* BossMonster_;
	std::list<class MonsterBase*> MonsterList_;

	//class LoadingActor* LoadingActor_;

	virtual void SettingStage() = 0;

	float CamerLeftPos_;
	float CamerRightPos_;

	float PlayerLeftPos_;
	float PlayerRightPos_;

private:

};

