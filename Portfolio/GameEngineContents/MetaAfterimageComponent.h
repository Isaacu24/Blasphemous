#pragma once
#include "AfterimageComponent.h"

class MetaAfterimageComponent : public AfterimageComponent
{
public:
	MetaAfterimageComponent();
	~MetaAfterimageComponent();

	MetaAfterimageComponent(const MetaAfterimageComponent& _Other) = delete;
	MetaAfterimageComponent(MetaAfterimageComponent&& _Other) noexcept = delete;
	MetaAfterimageComponent& operator=(const MetaAfterimageComponent& _Other) = delete;
	MetaAfterimageComponent& operator=(MetaAfterimageComponent&& _Other) noexcept = delete;

protected:

private:

};

