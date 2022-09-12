#pragma once
#include <GameEngineCore/GameEngineActor.h>
 
class PontiffMainBody : public GameEngineActor
{
public:
	PontiffMainBody();
	~PontiffMainBody();

	PontiffMainBody(const PontiffMainBody& _Other) = delete;
	PontiffMainBody(PontiffMainBody&& _Other) noexcept = delete;
	PontiffMainBody& operator=(const PontiffMainBody& _Other) = delete;
	PontiffMainBody& operator=(PontiffMainBody&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

private:
    class GameEngineTextureRenderer* Renderer_;

	bool IsAppear_;

	float Speed_;
};

