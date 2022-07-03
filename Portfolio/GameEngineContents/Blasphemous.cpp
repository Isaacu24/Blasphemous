#include "Blasphemous.h"
#include "Title.h"
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
	CreateLevel<Title>("Title"); 
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
