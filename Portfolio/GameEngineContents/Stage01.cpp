#include "Stage01.h"
#include "TenPiedad.h"
#include  <GameEngineCore/GameEngineLevel.h>

Stage01::Stage01() 
{
}

Stage01::~Stage01() 
{
}

void Stage01::Start()
{
	GetLevel()->CreateActor<TenPiedad>(0);
}

void Stage01::Update(float _DeltaTime)
{
}

void Stage01::End()
{
}
