#include "Penitent.h"
#include "PreCompile.h"
#include <GameEngineBase/GameEngineInput.h>
#include <iostream>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineDefaultRenderer.h>
#include <GameEngineCore/GameEngineDefaultRenderer.h>
#include <GameEngineCore/GameEngineRenderingPipeLine.h>
#include <GameEngineCore/GameEngineVertexShader.h>
#include <GameEngineCore/GameEngineConstantBuffer.h>
#include <GameEngineCore/GameEngineDevice.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>


Penitent::Penitent() 
	: Speed_(50.0f)
{
}

Penitent::~Penitent() 
{
}

void Penitent::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("PlayerLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("PlayerLeft", VK_NUMPAD4);
		GameEngineInput::GetInst()->CreateKey("PlayerRight", VK_NUMPAD6);
		GameEngineInput::GetInst()->CreateKey("PlayerUp", VK_NUMPAD9);
		GameEngineInput::GetInst()->CreateKey("PlayerDown", VK_NUMPAD7);
		GameEngineInput::GetInst()->CreateKey("PlayerForward", VK_NUMPAD8);
		GameEngineInput::GetInst()->CreateKey("PlayerBack", VK_NUMPAD5);
		GameEngineInput::GetInst()->CreateKey("Rot+", VK_NUMPAD1);
		GameEngineInput::GetInst()->CreateKey("Rot-", VK_NUMPAD2);
	}


	GetTransform().SetLocalScale({1, 1, 1});

	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		//Renderer->GetTransform().SetLocalScale({ 3000, 1700, 100 });
		Renderer->GetTransform().SetLocalScale({ 3300, 1600, 100 });
		//Renderer->getre
		//Renderer->PipeLineHelper.SetConstantBufferLink("TimeData", Time_);

		// 내 맴버변수가 아니라 다른객체의 맴버변수를 사용했다면.
		// 이건 터질수 있다.
	}
}

void Penitent::Update(float _DeltaTime)
{ 
	Time_ += _DeltaTime;

	if (true == GameEngineInput::GetInst()->IsPressKey("PlayerLeft"))
	{
		Renderer->ShaderResources.SetConstantBufferLink("TimeData", Time_);

		GetTransform().SetWorldMove(GetTransform().GetLeftVector() * Speed_ * _DeltaTime);
	}

	if (true == GameEngineInput::GetInst()->IsPressKey("PlayerRight"))
	{
		GetTransform().SetWorldMove(GetTransform().GetRightVector() * Speed_ * _DeltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPressKey("PlayerUp"))
	{
		GetTransform().SetWorldMove(GetTransform().GetUpVector() * Speed_ * _DeltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPressKey("PlayerDown"))
	{
		GetTransform().SetWorldMove(GetTransform().GetDownVector() * Speed_ * _DeltaTime);
	}

	if (true == GameEngineInput::GetInst()->IsPressKey("PlayerForward"))
	{
		GetTransform().SetWorldMove(GetTransform().GetForwardVector() * Speed_ * _DeltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPressKey("PlayerBack"))
	{
		GetTransform().SetWorldMove(GetTransform().GetBackVector() * Speed_ * _DeltaTime);
	}

}

void Penitent::End()
{
}





