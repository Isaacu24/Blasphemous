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

	GameEngineTextureRenderer* ColMap_;

	class GameEngineCameraActor* CameraActor_;
	class Penitent* Penitent_;

	class BossMonster* BossMonster_;
	std::list<class BossMonster*> MonsterList_;

	//class LoadingActor* LoadingActor_;

	virtual void SettingStage() = 0;

	float4 CamerLeftPos_;
	float4 CamerRightPos_;

	float4 PlayerLeftPos_;
	float4 PlayerRightPos_;

private:

};

