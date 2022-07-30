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
	Actor_ = CreateActor<OptionActor>();
}

void Option::Update(float _DeltaTime)
{

}

void Option::End()
{
}

void Option::OnEvent()
{
	Actor_->UpdateOptionMenu();
}

void Option::OffEvent()
{
}
