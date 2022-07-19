#pragma once

class GiantSword
{
public:
	GiantSword();
	~GiantSword();

	GiantSword(const GiantSword& _Other) = delete;
	GiantSword(GiantSword&& _Other) noexcept = delete;
	GiantSword& operator=(const GiantSword& _Other) = delete;
	GiantSword& operator=(GiantSword&& _Other) noexcept = delete;

protected:

private:

};

