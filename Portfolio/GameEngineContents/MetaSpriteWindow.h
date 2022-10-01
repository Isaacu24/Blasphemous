#pragma once
#include <GameEngineCore/GameEngineGUI.h>

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
    // GameEngineTextureRenderer* Renderer;

    std::string CurMetaFile_;
    std::string CurAtlasFile_;

    void MetaFileButton(GameEngineLevel* _Level);
    void AtlasFileButton(GameEngineLevel* _Level);

    void AllFolderButton(GameEngineLevel* _Level);

    void MetaParsing(const std::string& _AllText);

    void CutAllTexture();

    std::vector<MetaData> MetaDatas_;

    std::vector<GameEngineTexture*> Textures_;
    std::vector<std::vector<MetaData>> AllDatas_;
};
