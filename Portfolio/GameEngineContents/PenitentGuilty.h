#pragma once
#include <GameEngineCore/GameEngineActor.h>

class PenitentGuilty : public GameEngineActor
{
public:
	PenitentGuilty();
	~PenitentGuilty();

	PenitentGuilty(const PenitentGuilty& _Other) = delete;
	PenitentGuilty(PenitentGuilty&& _Other) noexcept = delete;
	PenitentGuilty& operator=(const PenitentGuilty& _Other) = delete;
	PenitentGuilty& operator=(PenitentGuilty&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

private:

};

