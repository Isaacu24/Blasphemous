#pragma once

class Platform
{
public:
	Platform();
	~Platform();

	Platform(const Platform& _Other) = delete;
	Platform(Platform&& _Other) noexcept = delete;
	Platform& operator=(const Platform& _Other) = delete;
	Platform& operator=(Platform&& _Other) noexcept = delete;

protected:

private:

};

