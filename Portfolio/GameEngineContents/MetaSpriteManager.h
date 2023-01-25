#pragma once
#include <map>

class MetaSpriteManager
{
    friend class MetaSpriteWindow;

private:
    static MetaSpriteManager* Inst_;

public:
    static void Destroy()
    {
        if (nullptr != Inst_)
        {
            delete Inst_;
            Inst_ = nullptr;
        }
    }

    static MetaSpriteManager* GetInst() { return Inst_; }

public:
    MetaSpriteManager();
    ~MetaSpriteManager();

    MetaSpriteManager(const MetaSpriteManager& _Other)                = delete;
    MetaSpriteManager(MetaSpriteManager&& _Other) noexcept            = delete;
    MetaSpriteManager& operator=(const MetaSpriteManager& _Other)     = delete;
    MetaSpriteManager& operator=(MetaSpriteManager&& _Other) noexcept = delete;

    std::vector<MetaData>& Insert(const std::string& _Name, std::vector<MetaData>& _Datas);
    std::vector<MetaData>& Find(const std::string& _Name);

    void Load(GameEngineDirectory _Dir);
    void MetaParsing(const std::string& _AllText);  //데이터 파싱

protected:

private:
    std::map<std::string, std::vector<MetaData>> MetaAnimations_;  //모든 애니메이션의 메타 데이터
    std::vector<std::vector<MetaData>>           AllDatas_;        //현 디렉토리의 모든 메타 데이터 파일
    std::vector<MetaData>                        MetaDatas_;       //현재 스프라이트의 데이터
    std::vector<GameEngineTexture*>              Textures_;        //메타 데이터를 통해 자를 텍스쳐들

    void CutAllTexture();  //데이터를 통한 텍스쳐 자르기


};
