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

private:

};

