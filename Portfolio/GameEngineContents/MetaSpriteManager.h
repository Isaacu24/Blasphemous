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
	void MetaParsing(const std::string& _AllText); //데이터 파싱
    std::vector<MetaData> MetaDatas_; //현재 애니메이션의 데이터

protected:

private:
    std::map<std::string, std::vector<MetaData>> MetaAnimations_; //모든 애니메이션 정보

    std::vector<GameEngineTexture*>    Textures_; //데이터를 통해 자를 텍스쳐들

    std::vector<std::vector<MetaData>> AllDatas_; //한 애니메이션의 모든 메타 데이터

    void CutAllTexture(); //데이터를 통한 텍스쳐 자르기	
};

