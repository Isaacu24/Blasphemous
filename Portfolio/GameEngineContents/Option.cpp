#include "PreCompile.h"
#include "Option.h"
#include "OptionActor.h"

Option::Option() 
{
}

Option::~Option() 
{
}

void Option::Start()
{
	CreateActor<OptionActor>();
}

void Option::Update(float _DeltaTime)
{

}

void Option::End()
{
}
