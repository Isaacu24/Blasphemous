#include "Blasphemous.h"
#include "Titile.h"
#include "MainMenu.h"
#include "Pilgrimage.h"

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
	CreateLevel<MainMenu>("MainMenu");
	CreateLevel<Pilgrimage>("Pilgrimage");
	ChangeLevel("Pilgrimage");
}

void Blasphemous::Update(float _DeltaTime)
{
}

void Blasphemous::End()
{
}
