#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "SpawnerBase.h"

class AnguishBeamSpawner 
	: public GameEngineActor
    , public SpawnerBase
{
public:
	AnguishBeamSpawner();
	~AnguishBeamSpawner();

	AnguishBeamSpawner(const AnguishBeamSpawner& _Other) = delete;
	AnguishBeamSpawner(AnguishBeamSpawner&& _Other) noexcept = delete;
	AnguishBeamSpawner& operator=(const AnguishBeamSpawner& _Other) = delete;
	AnguishBeamSpawner& operator=(AnguishBeamSpawner&& _Other) noexcept = delete;

	void CreateOnce();
    void CreateTwice();

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

private:

	class AnguishBeam* Beam_;

 };

