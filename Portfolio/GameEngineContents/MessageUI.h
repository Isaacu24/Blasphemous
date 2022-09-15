#pragma once
#include <GameEngineCore/GameEngineActor.h>

class MessageUI : public GameEngineActor
{
public:
	MessageUI();
	~MessageUI();

	MessageUI(const MessageUI& _Other) = delete;
	MessageUI(MessageUI&& _Other) noexcept = delete;
	MessageUI& operator=(const MessageUI& _Other) = delete;
	MessageUI& operator=(MessageUI&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

private:
    class GameEngineUIRenderer* Renderer_;
};

