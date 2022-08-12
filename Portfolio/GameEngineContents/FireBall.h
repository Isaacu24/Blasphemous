#pragma once
#include "Projectile.h"

class FireBall : public Projectile
{
public:
	FireBall();
	~FireBall();

	FireBall(const FireBall& _Other) = delete;
	FireBall(FireBall&& _Other) noexcept = delete;
	FireBall& operator=(const FireBall& _Other) = delete;
	FireBall& operator=(FireBall&& _Other) noexcept = delete;
	
protected:
    void Start() override;
    void Update(float _DetalTime) override;
    void End() override;

private:

};

