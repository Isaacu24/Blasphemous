#pragma once
#include "ObjectBase.h"

class NPCBase : public ObjectBase
{
public:
	NPCBase();
	~NPCBase();

	NPCBase(const NPCBase& _Other) = delete;
	NPCBase(NPCBase&& _Other) noexcept = delete;
	NPCBase& operator=(const NPCBase& _Other) = delete;
	NPCBase& operator=(NPCBase&& _Other) noexcept = delete;

protected:
    void Start() = 0;
    void Update(float _DeltaTime) override;
    void End() override;

private:

};

