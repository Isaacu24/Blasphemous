#pragma once

class ObjectBase
{
public:
	ObjectBase();
	~ObjectBase();

	ObjectBase(const ObjectBase& _Other) = delete;
	ObjectBase(ObjectBase&& _Other) noexcept = delete;
	ObjectBase& operator=(const ObjectBase& _Other) = delete;
	ObjectBase& operator=(ObjectBase&& _Other) noexcept = delete;

protected:
    class GameEngineCollision* UICollider_;
    class GameEngineTextureRenderer* UIRenderer_;

private:
};

