#pragma once
#include "ObjectBase.h"

class Lantern : public ObjectBase
{
public:
	Lantern();
	~Lantern();

	Lantern(const Lantern& _Other) = delete;
	Lantern(Lantern&& _Other) noexcept = delete;
	Lantern& operator=(const Lantern& _Other) = delete;
	Lantern& operator=(Lantern&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void End() override;

private:
    class MetaTextureRenderer* MetaRenderer_;
    class GameEngineCollision* Collider_;

    bool IsExplode_;

};

