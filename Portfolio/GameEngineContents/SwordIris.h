#pragma once

class SwordIris
{
public:
	SwordIris();
	~SwordIris();

	SwordIris(const SwordIris& _Other) = delete;
	SwordIris(SwordIris&& _Other) noexcept = delete;
	SwordIris& operator=(const SwordIris& _Other) = delete;
	SwordIris& operator=(SwordIris&& _Other) noexcept = delete;

protected:

private:

};

