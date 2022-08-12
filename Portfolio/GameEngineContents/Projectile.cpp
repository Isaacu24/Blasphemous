#include "PreCompile.h"
#include "Projectile.h"

Projectile::Projectile() 
    : State_{}
    , Renderer_(nullptr)
    , Collider_(nullptr)
    , ColMap_(nullptr)
    , Dir_(float4::ZERO)
    , Speed_(200.f)
{
}

Projectile::~Projectile() 
{
}


