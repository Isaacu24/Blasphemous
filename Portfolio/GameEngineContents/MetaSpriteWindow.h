#pragma once
#include <GameEngineCore/GameEngineGUI.h>

struct MetaData
{
    int PosX; 
    int PosY; 
    int Width;
    int Height;
    float PivotX;
    float PivotY;
};

class GameEngineTextureRenderer;
class MetaTextureRenderer;
class MetaSpriteWindow : public GameEngineGUIWindow
{
public:
    MetaSpriteWindow();
    ~MetaSpriteWindow();

    MetaSpriteWindow(const MetaSpriteWindow& _Other)                = delete;
    MetaSpriteWindow(MetaSpriteWindow&& _Other) noexcept            = delete;
    MetaSpriteWindow& operator=(const MetaSpriteWindow& _Other)     = delete;
    MetaSpriteWindow& operator=(MetaSpriteWindow&& _Other) noexcept = delete;

    GameEngineDirectory MetaDir;
    GameEngineTexture*  TargetTexture;

    //void MetaSetPivot();

protected:
    void Initialize(class GameEngineLevel* _Level) override;
    void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;

private:
    int                  CurFrame;
    MetaTextureRenderer* Renderer;

    //GameEngineTextureRenderer* Renderer;


    std::string CurMetaFolder_;
    std::string CurAtlasFolder_;

    std::string CurMetaFile_;
    std::string CurAtlasFile_;

    void MetaFileButton(GameEngineLevel* _Level);
    void AtlasFileButton(GameEngineLevel* _Level);

    std::vector<MetaData> MetaDatas_;

    // void MetaFileButton();
    // void AtlasFileButton();
};
