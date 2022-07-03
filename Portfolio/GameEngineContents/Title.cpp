#include "Title.h"
#include "PreCompile.h"
#include <GameEngineCore/GameEngineCameraActor.h>

Title::Title()
{
}

Title::~Title()
{
}

void Title::Start()
{
	CreateActor<GameEngineCameraActor>(0);
}

void Title::Update(float _DeltaTime)
{
}

void Title::End()
{
}
