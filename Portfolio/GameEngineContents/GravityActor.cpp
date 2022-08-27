#include "PreCompile.h"
#include "GravityActor.h"

GravityActor::GravityActor()
	: Gravity_(nullptr)
	, IsMove_(false)
	, Speed_(100.f)
{
}

GravityActor::~GravityActor() 
{
}




void GravityActor::Start()
{
	Gravity_ = CreateComponent<GravityComponent>();
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->GetTransform().SetWorldScale({100, 100});
	Renderer_->SetPivot(PIVOTMODE::BOT);
}

void GravityActor::Update(float _DeltaTime)
{
	if (true == IsMove_)
	{
		//Alpha_ += _DeltaTime;
        GetTransform().SetWorldMove({(Dir_.x * 800.f * _DeltaTime), 0.f});
		//(float4::LerpLimit(StartPos_, EndPos_, Alpha_));

		if (0 > Dir_.x)
        {
            if (EndPos_.x > GetTransform().GetWorldPosition().x)
            {
                IsMove_ = false;
			}
		}

		else
		{
            if (EndPos_.x < GetTransform().GetWorldPosition().x)
            {
                IsMove_ = false;
            }
		}
	}

	GroundCheck();
	UphillRoadCheck();
	Gravity_->SetActive(!IsGround_);
}

void GravityActor::End()
{

}

void GravityActor::GroundCheck()
{
	float4 Color;

	Color = ColMap_->GetCurTexture()->GetPixelToFloat4(GetTransform().GetWorldPosition().x, -(GetTransform().GetWorldPosition().y));

	if (true == Color.CompareInt4D(float4::BLACK)
		|| true == Color.CompareInt4D(float4::MAGENTA)) //¶¥ÀÌ¶ó¸é 
	{
		IsGround_ = true;
	}

	else
	{
		IsGround_ = false;
	}
}



void GravityActor::UphillRoadCheck()
{
	while (true)
	{
		float4 Color = ColMap_->GetCurTexture()->GetPixelToFloat4(GetTransform().GetWorldPosition().x, -(GetTransform().GetWorldPosition().y - 1));

		if (true == Color.CompareInt4D(float4::BLACK)
			|| true == Color.CompareInt4D(float4::MAGENTA))
		{
			GetTransform().SetWorldMove(float4::UP);
			continue;
		}

		else
		{
			break;
		}
	}
}