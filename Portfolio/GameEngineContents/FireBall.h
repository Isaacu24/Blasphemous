#pragma once

class FireBall
{
public:
	FireBall();
	~FireBall();

	FireBall(const FireBall& _Other) = delete;
	FireBall(FireBall&& _Other) noexcept = delete;
	FireBall& operator=(const FireBall& _Other) = delete;
	FireBall& operator=(FireBall&& _Other) noexcept = delete;

protected:

private:

};

