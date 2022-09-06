#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "ObjectBase.h"

class Door
    : public GameEngineActor
    , public ObjectBase
{
public:
	Door();
	~Door();

	Door(const Door& _Other) = delete;
	Door(Door&& _Other) noexcept = delete;
	Door& operator=(const Door& _Other) = delete;
	Door& operator=(Door&& _Other) noexcept = delete;

	void Open(); 

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	class GameEngineTextureRenderer* Renderer_;

};

