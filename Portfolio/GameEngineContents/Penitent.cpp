#include "Penitent.h"
#include "PreCompile.h"

Penitent* Penitent::Player_ = nullptr;

Penitent::Penitent() 
{
	Player_ = this;
}

Penitent::~Penitent() 
{
}

void Penitent::Start()
{
}

void Penitent::Update(float _DeltaTime)
{
}

void Penitent::End()
{
}





//플라스크
void Penitent::Flask::SetValue()
{
	
}

void Penitent::Flask::Recovery()
{
	Player_->HP_ = Value_;
}
