#pragma once
#include <map>

class MetaSpriteManager
{
public: 
	static MetaSpriteManager* Inst_;

	static void Destroy() 
	{
        if (nullptr != Inst_)
        {
            delete Inst_;
            Inst_ = nullptr;
        }
	}

public:
	MetaSpriteManager();
	~MetaSpriteManager();

	MetaSpriteManager(const MetaSpriteManager& _Other) = delete;
	MetaSpriteManager(MetaSpriteManager&& _Other) noexcept = delete;
	MetaSpriteManager& operator=(const MetaSpriteManager& _Other) = delete;
	MetaSpriteManager& operator=(MetaSpriteManager&& _Other) noexcept = delete;

	std::vector<MetaData>& Insert(const std::string& _Name, std::vector<MetaData>& _Datas);
    std::vector<MetaData>& Find(const std::string& _Name);

	void Load(GameEngineDirectory _Dir);

protected:

private:
    std::map<std::string, std::vector<MetaData>> MetaAnimations_;

    std::vector<MetaData> MetaDatas_;

    std::vector<GameEngineTexture*>    Textures_;
    std::vector<std::vector<MetaData>> AllDatas_;

	void MetaParsing(const std::string& _AllText);

    void CutAllTexture();
};

