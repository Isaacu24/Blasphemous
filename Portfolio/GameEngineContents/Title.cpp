#include "Title.h"
#include "Otus.h"

Title::Title() 
{
}

Title::~Title() 
{
}

void Title::Start()
{
	CreateActor<Otus>(1);

}

void Title::Update(float _DeltaTime)
{
}

void Title::End()
{
}
