#include "PreCompile.h"
#include "Door.h"

Door::Door() {}

Door::~Door() {}

void Door::Open() {}

void Door::Start()
{
    SetObjectType(ObjectType::Door);

    Renderer_ = CreateComponent<GameEngineTextureRenderer>();
    Renderer_->CreateFrameAnimationCutTexture("brotherhood_door_anim_Close",
                                              {"brotherhood_door_anim 1.png", 0, 1, 0.1f, false});
    Renderer_->CreateFrameAnimationCutTexture("brotherhood_door_anim_Open",
                                              {"brotherhood_door_anim 1.png", 0, 14, 0.1f, false});
    Renderer_->ChangeFrameAnimation("brotherhood_door_anim_Close");
    Renderer_->GetTransform().SetWorldScale({450, 450});

    UICollider_ = CreateComponent<GameEngineCollision>();
    UICollider_->GetTransform().SetWorldScale({100.f, 200.f, 1.f});
    UICollider_->ChangeOrder(COLLISIONORDER::Object);
    UICollider_->SetDebugSetting(CollisionType::CT_OBB2D, float4{0.0f, 0.0f, 1.0f, 0.5f});
    UICollider_->GetTransform().SetWorldMove({0, -100});

    UIRenderer_ = CreateComponent<GameEngineTextureRenderer>();

    if (0 < GameEngineInput::GetInst()->GetInputState().dwPacketNumber)
    {
        UIRenderer_->SetTexture("CT_Y.png");
    }

    else
    {
        UIRenderer_->SetTexture("KB_E.png");
    }

    UIRenderer_->GetTransform().SetWorldScale({30, 30, 1});
    UIRenderer_->GetTransform().SetWorldMove({0, 70});
    UIRenderer_->Off();
}

void Door::Update(float _DeltaTime)
{
    if (true
        == UICollider_->IsCollision(CollisionType::CT_OBB2D, COLLISIONORDER::Player, CollisionType::CT_OBB2D, nullptr))
    {
        UIRenderer_->On();

        if (0 < GameEngineInput::GetInst()->GetInputState().dwPacketNumber)
        {
            UIRenderer_->SetTexture("CT_Y.png");
        }

        else
        {
            UIRenderer_->SetTexture("KB_E.png");
        }

        if (true == GameEngineInput::GetInst()->IsDownKey("Interaction") && (ObjectType::Door == GetObjectType())
            || true == GameEngineInput::GetInst()->IsDownButton("PenitentY") && (ObjectType::Door == GetObjectType()))
        {
            Renderer_->ChangeFrameAnimation("brotherhood_door_anim_Open");

            if (true == Renderer_->IsUpdate())
            {
                SoundPlayer_ = GameEngineSound::SoundPlayControl("DOOR_METAL_DOUBLE.wav");
            }
            return;
        }
    }

    else
    {
        UIRenderer_->Off();
    }

    if (ObjectType::Door == GetObjectType())
    {
        if (true == GameEngineInput::GetInst()->IsUpKey("Interaction")
            || true == GameEngineInput::GetInst()->IsUpButton("PenitentY"))
        {
            SetObjectType(ObjectType::OpenDoor);
        }
    }
}

void Door::End() { Renderer_->ChangeFrameAnimation("brotherhood_door_anim_Open"); }
