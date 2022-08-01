#pragma once
#include <GameEngineCore/GameEngineActor.h>

//5�ʸ��� ȥ�� �˾Ƽ� ����
class Platform : public GameEngineActor
{
public:
	Platform();
	~Platform();

	Platform(const Platform& _Other) = delete;
	Platform(Platform&& _Other) noexcept = delete;
	Platform& operator=(const Platform& _Other) = delete;
	Platform& operator=(Platform&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	class GameEngineTextureRenderer* Renderer_;
};

