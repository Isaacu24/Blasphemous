#pragma once

// Ό³Έν :
class Titile
{
public:
	// constrcuter destructer
	Titile();
	~Titile();

	// delete Function
	Titile(const Titile& _Other) = delete;
	Titile(Titile&& _Other) noexcept = delete;
	Titile& operator=(const Titile& _Other) = delete;
	Titile& operator=(Titile&& _Other) noexcept = delete;

protected:

private:

};

