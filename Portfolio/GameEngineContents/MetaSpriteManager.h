#pragma once
#include <map>

class MetaSpriteManager
{
public:
	MetaSpriteManager();
	~MetaSpriteManager();

	MetaSpriteManager(const MetaSpriteManager& _Other) = delete;
	MetaSpriteManager(MetaSpriteManager&& _Other) noexcept = delete;
	MetaSpriteManager& operator=(const MetaSpriteManager& _Other) = delete;
	MetaSpriteManager& operator=(MetaSpriteManager&& _Other) noexcept = delete;

	std::vector<MetaData>& Insert();
    std::vector<MetaData>& Find();


protected:

private:
    std::map<std::string, std::vector<MetaData>> MetaAnimations_;
};

