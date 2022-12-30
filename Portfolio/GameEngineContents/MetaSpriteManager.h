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
    void MetaParsing(const std::string& _AllText);  //������ �Ľ�

protected:
private:
    std::map<std::string, std::vector<MetaData>> MetaAnimations_;  //��� �ִϸ��̼� ����
    std::vector<GameEngineTexture*>              Textures_;        //�����͸� ���� �ڸ� �ؽ��ĵ�
    std::vector<std::vector<MetaData>>           AllDatas_;        //�� �ִϸ��̼��� ��� ��Ÿ ������
    std::vector<MetaData>                        MetaDatas_;       //���� �ִϸ��̼��� ������

    void CutAllTexture();  //�����͸� ���� �ؽ��� �ڸ���
};
