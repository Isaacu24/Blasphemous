#pragma once
#include <map>

class MetaSpriteManager
{
public: 
	static MetaSpriteManager* Inst_;

public:
	MetaSpriteManager();
	~MetaSpriteManager();

	MetaSpriteManager(const MetaSpriteManager& _Other) = delete;
	MetaSpriteManager(MetaSpriteManager&& _Other) noexcept = delete;
	MetaSpriteManager& operator=(const MetaSpriteManager& _Other) = delete;
	MetaSpriteManager& operator=(MetaSpriteManager&& _Other) noexcept = delete;

	std::vector<MetaData>& Insert(const std::string& _Name, std::vector<MetaData>& _Datas);
    std::vector<MetaData>& Find(const std::string& _Name);

protected:

private:
    std::map<std::string, std::vector<MetaData>> MetaAnimations_;
};

