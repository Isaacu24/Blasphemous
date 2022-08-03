#pragma once
#include <vector>

class GameEngineTextureRenderer;
class ParallaxScrolling
{
public:
	ParallaxScrolling();
	~ParallaxScrolling();

	ParallaxScrolling(const ParallaxScrolling& _Other) = delete;
	ParallaxScrolling(ParallaxScrolling&& _Other) noexcept = delete;
	ParallaxScrolling& operator=(const ParallaxScrolling& _Other) = delete;
	ParallaxScrolling& operator=(ParallaxScrolling&& _Other) noexcept = delete;

	void PushParallax(GameEngineTextureRenderer* _Renderer);

protected:

private:
	
};

