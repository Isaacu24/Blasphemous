#include "PreCompile.h"
#include "GameEngineFontRenderer.h"

GameEngineFontRenderer::GameEngineFontRenderer()
	: Font(nullptr)
	, FontSize(20.0f)
	, Color(float4::WHITE)
	, ScreenPostion(float4::ZERO)
{
}

GameEngineFontRenderer::~GameEngineFontRenderer()
{
}

void GameEngineFontRenderer::SetText(const std::string& _Text, const std::string& _Font)
{
	Text = _Text;
	Font = GameEngineFont::Find(_Font);
}

void GameEngineFontRenderer::Start()
{
	PushRendererToMainCamera();
}

void GameEngineFontRenderer::Render(float _DeltaTime)
{
	if (nullptr == Font)
	{
		return;
	}

	Font->FontDraw(Text, FontSize, ScreenPostion, Color);
}