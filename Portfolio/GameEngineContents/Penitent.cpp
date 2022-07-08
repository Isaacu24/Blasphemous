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
{
}

Penitent::~Penitent() 
{
}

void Penitent::Start()
{
	DefaultRenderer_ = CreateComponent<GameEngineDefaultRenderer>();
	DefaultRenderer_->GetTransform().SetLocalScale({ 100, 100, 100 });
	DefaultRenderer_->SetPipeLine("Color");
}

void Penitent::Update(float _DeltaTime)
{

	GameEngineConstantBufferSetter& Data = DefaultRenderer_->GetPipeLine()->GetVertexShader()->GetConstantBufferSetter("TransformData");

	const TransformData& DataRef = DefaultRenderer_->GetTransformData();

	Data.Buffer->ChangeData(&DataRef, sizeof(TransformData));

	GameEngineDevice::GetContext()->VSSetConstantBuffers(Data.BindPoint, 1, &Data.Buffer->Buffer);
}

void Penitent::End()
{
}





