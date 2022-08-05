#include "PreCompile.h"
#include "Pope.h"

Pope::Pope() 
{
}

Pope::~Pope() 
{
}

//GameEngineTexture::Cut("pope_idle.png", 4, 4);
//GameEngineTexture::Cut("pope_appear.png", 4, 4);
//GameEngineTexture::Cut("pope_death.png", 6, 6);
//GameEngineTexture::Cut("pope_hitReaction.png", 4, 3);
//GameEngineTexture::Cut("pope_spellCast.png", 8, 7);
//GameEngineTexture::Cut("pope_vanishing.png", 4, 4);

void Pope::Start()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->CreateFrameAnimationCutTexture("pope_idle", { "pope_idle.png", 0, 12, 0.1f, true });
	Renderer_->CreateFrameAnimationCutTexture("pope_appear", { "pope_appear.png", 0, 15, 0.1f, true });
	Renderer_->CreateFrameAnimationCutTexture("pope_hitReaction", { "pope_hitReaction.png", 0, 10, 0.1f, true });
	Renderer_->CreateFrameAnimationCutTexture("pope_spellCast", { "pope_spellCast.png", 0, 53, 0.1f, true });
	Renderer_->CreateFrameAnimationCutTexture("pope_spellCast_FXS", { "pope_spellCast_FXS.png", 0, 53, 0.1f, true }); //ÀÌÆåÆ®
	Renderer_->CreateFrameAnimationCutTexture("pope_vanishing", { "pope_vanishing.png", 0, 13, 0.1f, true });
	Renderer_->CreateFrameAnimationCutTexture("pope_death", { "pope_death.png", 0, 35, 0.1f, true });
	Renderer_->ChangeFrameAnimation("pope_idle");
	Renderer_->GetTransform().SetWorldScale({ 250, 250});
	Renderer_->SetPivot(PIVOTMODE::BOT);

	DetectCollider_ = CreateComponent<GameEngineCollision>();
	DetectCollider_->ChangeOrder(COLLISIONORDER::BossMonster);
	DetectCollider_->GetTransform().SetWorldScale({ 500.0f, 500.0f, 1.0f });
}

void Pope::Update(float _DeltaTime)
{
	if (true == DetectCollider_->IsCollision(CollisionType::CT_OBB2D, COLLISIONORDER::Player, CollisionType::CT_OBB2D,
		std::bind(&Pope::DecideState, this, std::placeholders::_1, std::placeholders::_2)))
	{
		int a = 0;
	}
}

void Pope::End()
{
}

bool Pope::DecideState(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	return false;
}
