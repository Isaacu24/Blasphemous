#include "PreCompile.h"
#include "MetaSpriteManager.h"

MetaSpriteManager* MetaSpriteManager::Inst_ = new MetaSpriteManager();

MetaSpriteManager::MetaSpriteManager() 
{
}

MetaSpriteManager::~MetaSpriteManager() 
{

}

std::vector<MetaData>& MetaSpriteManager::Insert(const std::string& _Name, std::vector<MetaData>& _Datas)
{
    std::vector<MetaData> NewDatas = _Datas;

    std::string UpperName = GameEngineString::ToUpperReturn(_Name);

    if (MetaAnimations_.end() != MetaAnimations_.find(UpperName))
    {
        return _Datas;
    }

    MetaAnimations_.insert(std::make_pair(UpperName, NewDatas));

    if (0 == NewDatas.size())
    {
        MsgBoxAssert("잘못된 크기의 메타 데이터입니다.");
        return _Datas;
    }

    return _Datas;
}

std::vector<MetaData>& MetaSpriteManager::Find(const std::string& _Name) 
{
    std::string UpperName = GameEngineString::ToUpperReturn(_Name);

    std::map<std::string, std::vector<MetaData>>::iterator FindIter = MetaAnimations_.find(UpperName);

    if (FindIter == MetaAnimations_.end())
    {
        MsgBoxAssert("존재하지 않는 메타 데이터를 찾으려고 했습니다.");
        return FindIter->second;
    }

    return FindIter->second;
}

void MetaSpriteManager::Load(GameEngineDirectory _Dir)
{
    std::vector<GameEngineFile> Textures = _Dir.GetAllFile();

    for (size_t i = 0; i < Textures.size(); i++)
    {
        std::string FileName  = Textures[i].GetFileName();
        std::string extension = std::filesystem::path{FileName}.extension().string();

        if (".png" == extension)
        {
            GameEngineTexture* NewTexture = GameEngineRes<GameEngineTexture>::Find(Textures[i].GetFullPath());

            if (nullptr != NewTexture)
            {
                Textures_.push_back(NewTexture);
                continue;
            }

            NewTexture = GameEngineTexture::Load(Textures[i].GetFullPath());
            Textures_.push_back(NewTexture);
        }

        else if (".meta" == extension)
        {
            Textures[i].Open(OpenMode::Read, FileMode::Text);

            std::string AllText = Textures[i].GetString();

            MetaParsing(AllText);

            std::string FileName      = std::filesystem::path{Textures[i].GetFileName()}.filename().string();
            std::string ImageName     = std::filesystem::path{FileName}.replace_extension("").string();
            std::string AnimationName = std::filesystem::path{ImageName}.replace_extension("").string();

            if (0 == MetaDatas_.size())
            {
                int a = 0;
            }

            Insert(AnimationName, MetaDatas_);

            AllDatas_.push_back(MetaDatas_);
        }
    }

    CutAllTexture();
}

void MetaSpriteManager::MetaParsing(const std::string& _AllText) 
{
    MetaDatas_.clear();

    size_t StartPos       = 0;
    size_t AnimationStart = 0;

    while (true)
    {
        AnimationStart = _AllText.find("second:", AnimationStart);

        if (AnimationStart == std::string::npos)
        {
            break;
        }

        size_t AnimationEnd = _AllText.find("externalObjects", AnimationStart);

        if (AnimationEnd == std::string::npos)
        {
            break;
        }

        std::string AnimationString = _AllText.substr(AnimationStart, AnimationEnd - AnimationStart);

        StartPos = _AllText.find("rect:", StartPos);

        if (StartPos == std::string::npos)
        {
            break;
        }

        size_t EndPos = _AllText.find("outline:", StartPos);

        if (EndPos == std::string::npos)
        {
            break;
        }

        std::string CutDataString = _AllText.substr(StartPos, EndPos - StartPos);

        int  Index  = 0;
        float StartX = 0;
        float  StartY = 0;
        float  SizeX  = 0;
        float  SizeY  = 0;
        float PivotX = 0;
        float PivotY = 0;

        {
            std::string FindString   = "second:";
            size_t      DataStartPos = AnimationString.find(FindString);
            size_t      DataEndpos   = AnimationString.find("\n", DataStartPos);

            std::string IndexString = AnimationString.substr(DataStartPos, DataEndpos);

            size_t UnderBarPos = IndexString.rfind("_");

            size_t Size = IndexString.size();

            IndexString = IndexString.substr(UnderBarPos + 1, IndexString.size() - UnderBarPos);

            Index = atoi(IndexString.c_str());
        }

        {
            std::string FindString   = "x:";
            size_t      DataStartPos = CutDataString.find(FindString);
            size_t      DataEndpos   = CutDataString.find("\n", DataStartPos);
            std::string XString
                = CutDataString.substr(DataStartPos + FindString.size(), DataEndpos - DataStartPos + FindString.size());

            StartX = static_cast<float>(atof(XString.c_str()));
        }

        {
            std::string FindString   = "y:";
            size_t      DataStartPos = CutDataString.find(FindString);
            size_t      DataEndpos   = CutDataString.find("\n", DataStartPos);
            std::string XString
                = CutDataString.substr(DataStartPos + FindString.size(), DataEndpos - DataStartPos + FindString.size());

            StartY = static_cast<float>(atof(XString.c_str()));
        }

        {
            std::string FindString   = "width:";
            size_t      DataStartPos = CutDataString.find(FindString);
            size_t      DataEndpos   = CutDataString.find("\n", DataStartPos);
            std::string XString
                = CutDataString.substr(DataStartPos + FindString.size(), DataEndpos - DataStartPos + FindString.size());

            SizeX = static_cast<float>(atof(XString.c_str()));
        }

        {
            std::string FindString   = "height:";
            size_t      DataStartPos = CutDataString.find(FindString);
            size_t      DataEndpos   = CutDataString.find("\n", DataStartPos);

            std::string XString
                = CutDataString.substr(DataStartPos + FindString.size(), DataEndpos - DataStartPos + FindString.size());

            SizeY = static_cast<float>(atof(XString.c_str()));
        }

        {
            std::string FindString   = "pivot:";
            size_t      DataStartPos = CutDataString.find(FindString);
            size_t      DataEndpos   = CutDataString.find("}", DataStartPos);

            std::string PivotString
                = CutDataString.substr(DataStartPos + FindString.size(), DataEndpos - DataStartPos + FindString.size());

            size_t XStartPos = PivotString.find("x: ");
            size_t XEndpos   = PivotString.find(", ");

            std::string XString = PivotString.substr(XStartPos + 3, XEndpos - 5);

            size_t YStartPos = PivotString.find("y: ");
            size_t YEndpos   = PivotString.find("}");

            std::string YString = PivotString.substr(YStartPos + 3, PivotString.size() - YEndpos);

            PivotX = static_cast<float>(atof(XString.c_str()));
            PivotY = static_cast<float>(atof(YString.c_str()));

            MetaData Data = {Index, StartX, StartY, SizeX, SizeY, PivotX, PivotY};

            MetaDatas_.push_back(Data);
        }

        StartPos += 1;
        AnimationStart += 1;
    }
}

void MetaSpriteManager::CutAllTexture() 
{
    for (size_t i = 0; i < Textures_.size(); i++)
    {
        GameEngineTexture* TargetTexture = Textures_[i];

        if (nullptr == TargetTexture)
        {
            continue;
        }

        for (size_t j = 0; j < AllDatas_[i].size(); j++)
        {
            TargetTexture->Cut(static_cast<size_t>(AllDatas_[i][j].PosX),
                               static_cast<size_t>(TargetTexture->GetScale().y - AllDatas_[i][j].PosY - AllDatas_[i][j].Height),
                               static_cast<size_t>(AllDatas_[i][j].Width),
                               static_cast<size_t>(AllDatas_[i][j].Height));
        }
    }

    Textures_.clear();
    AllDatas_.clear();
}

