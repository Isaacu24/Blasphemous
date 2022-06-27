#include "Titile.h"
#include "PreCompile.h"
#include <GameEngineCore/GameEngineCameraActor.h>

Titile::Titile()
{
}

Titile::~Titile()
{
}

void Titile::Start()
{
	CreateActor<GameEngineCameraActor>(0);
}

void Titile::Update(float _DeltaTime)
{
}

void Titile::End()
{
}
