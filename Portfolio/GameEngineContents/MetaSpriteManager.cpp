#include "PreCompile.h"
#include "MetaSpriteManager.h"

MetaSpriteManager* MetaSpriteManager::Inst_ = new MetaSpriteManager();

MetaSpriteManager::MetaSpriteManager() 
{
}

MetaSpriteManager::~MetaSpriteManager() 
{
    if (nullptr != Inst_)
    {
        delete Inst_;
        Inst_ = nullptr;
    }
}

std::vector<MetaData>& MetaSpriteManager::Insert(const std::string& _Name, std::vector<MetaData>& _Datas)
{
    std::vector<MetaData> NewDatas = _Datas;

    std::string UpperName = GameEngineString::ToUpperReturn(_Name);

    MetaAnimations_.insert(std::make_pair(UpperName, NewDatas));

    if (0 == NewDatas.size())
    {
        MsgBoxAssert("�߸��� ũ���� ��Ÿ �������Դϴ�.");
        return NewDatas;
    }

    return NewDatas;
}

std::vector<MetaData>& MetaSpriteManager::Find(const std::string& _Name) 
{
    std::string UpperName = GameEngineString::ToUpperReturn(_Name);

    std::map<std::string, std::vector<MetaData>>::iterator FindIter = MetaAnimations_.find(UpperName);

    if (FindIter == MetaAnimations_.end())
    {
        MsgBoxAssert("�������� �ʴ� ��Ÿ �����͸� ã������ �߽��ϴ�.");
        return FindIter->second;
    }

    return FindIter->second;
}

