#include "Titile.h"
#include "PreCompile.h"
#include <GameEngineCore/GameEngineActor.h>
#include "Penitent.h"
#include "Stage01.h"
#include <GameEngineCore/GameEngineCameraActor.h>

Titile::Titile()
{
}

Titile::~Titile()
{
}

void Titile::Start()
{
	CreateActor<Penitent>(1);

	CreateActor<GameEngineCameraActor>(0);
}

void Titile::Update(float _DeltaTime)
{
}

void Titile::End()
{
}
