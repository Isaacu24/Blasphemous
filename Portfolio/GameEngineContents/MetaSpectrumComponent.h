#pragma once
#include "SpectrumComponent.h"

class MetaSpectrumComponent : public SpectrumComponent
{
public:
	MetaSpectrumComponent();
	~MetaSpectrumComponent();

	MetaSpectrumComponent(const MetaSpectrumComponent& _Other) = delete;
	MetaSpectrumComponent(MetaSpectrumComponent&& _Other) noexcept = delete;
	MetaSpectrumComponent& operator=(const MetaSpectrumComponent& _Other) = delete;
	MetaSpectrumComponent& operator=(MetaSpectrumComponent&& _Other) noexcept = delete;

protected:

private:

};

