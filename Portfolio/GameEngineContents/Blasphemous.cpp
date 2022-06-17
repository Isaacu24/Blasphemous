#include "Blasphemous.h"
#include "Titile.h"

#pragma comment(lib, "GameEngineBase.lib")


Blasphemous::Blasphemous() 
{
}

Blasphemous::~Blasphemous() 
{
}

void Blasphemous::Start()
{
	CreateLevel<Titile>("Title");
	ChangeLevel("Title");
}

void Blasphemous::Update(float _DeltaTime)
{
}

void Blasphemous::End()
{
}
