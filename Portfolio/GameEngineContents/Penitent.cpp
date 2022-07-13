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
		Renderer = CreateComponent<GameEngineDefaultRenderer>();
		Renderer->GetTransform().SetLocalScale({ 2000, 1000, 100 });
		Renderer->SetPipeLine("Texture");
		Renderer->PipeLineHelper.SetConstantBufferLink("TimeData", Time_);

		// 내 맴버변수가 아니라 다른객체의 맴버변수를 사용했다면.
		// 이건 터질수 있다.
	}
}

void Penitent::Update(float _DeltaTime)
{
	Time_ += _DeltaTime;

	if (true == GameEngineInput::GetInst()->IsPress("PlayerLeft"))
	{
		Renderer->PipeLineHelper.SetConstantBufferLink("TimeData", Time_);

		GetTransform().SetWorldMove(GetTransform().GetLeftVector() * Speed_ * _DeltaTime);
	}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerRight"))
	{
		GetTransform().SetWorldMove(GetTransform().GetRightVector() * Speed_ * _DeltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPress("PlayerUp"))
	{
		GetTransform().SetWorldMove(GetTransform().GetUpVector() * Speed_ * _DeltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPress("PlayerDown"))
	{
		GetTransform().SetWorldMove(GetTransform().GetDownVector() * Speed_ * _DeltaTime);
	}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerForward"))
	{
		GetTransform().SetWorldMove(GetTransform().GetForwardVector() * Speed_ * _DeltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPress("PlayerBack"))
	{
		GetTransform().SetWorldMove(GetTransform().GetBackVector() * Speed_ * _DeltaTime);
	}

}

void Penitent::End()
{
}





