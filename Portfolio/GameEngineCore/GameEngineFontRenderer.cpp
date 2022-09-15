#include "PreCompile.h"
#include "GameEngineFontRenderer.h"
#include "GameEngineBlend.h"
#include "GameEngineCamera.h"

GameEngineRenderTarget* GameEngineFontRenderer::FontTarget = nullptr;

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
	if (nullptr == FontTarget)
	{
		FontTarget = GameEngineRenderTarget::Create("FontTarget");
		FontTarget->CreateRenderTargetTexture(GameEngineWindow::GetScale(), float4::ZERO);
	}

	PushRendererToMainCamera();
}

void GameEngineFontRenderer::Render(float _DeltaTime)
{
	if (nullptr == Font)
	{
		return;
	}

	FontTarget->Clear();
	FontTarget->Setting();

	Font->FontDraw(Text, FontSize, ScreenPostion, Color, static_cast<int>(LR) | static_cast<int>(TB));

	GameEngineRenderingPipeLine::AllShaderReset();

	Camera->GetCameraRenderTarget()->Merge(FontTarget);
}