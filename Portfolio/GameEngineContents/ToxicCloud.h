#pragma once

class ToxicCloud
{
public:
	ToxicCloud();
	~ToxicCloud();

	ToxicCloud(const ToxicCloud& _Other) = delete;
	ToxicCloud(ToxicCloud&& _Other) noexcept = delete;
	ToxicCloud& operator=(const ToxicCloud& _Other) = delete;
	ToxicCloud& operator=(ToxicCloud&& _Other) noexcept = delete;

protected:

private:

};

