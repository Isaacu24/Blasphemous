#pragma once
#include <GameEngineCore/GameEngineGUI.h>

class GameEngineTextureRenderer;
class MetaAnimationWindow : public GameEngineGUIWindow
{
public:
    MetaAnimationWindow();
    ~MetaAnimationWindow();

    MetaAnimationWindow(const MetaAnimationWindow& _Other)                = delete;
    MetaAnimationWindow(MetaAnimationWindow&& _Other) noexcept            = delete;
    MetaAnimationWindow& operator=(const MetaAnimationWindow& _Other)     = delete;
    MetaAnimationWindow& operator=(MetaAnimationWindow&& _Other) noexcept = delete;

protected:
    void Initialize(class GameEngineLevel* _Level) override;
    void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;

private:
    std::string CurMetaFolder_;
    std::string CurAtlasFolder_;

    std::string CurMetaFile_;
    std::string CurAtlasFile_;

    void MetaFolderButton();
    void AtlasFolderButton();

    void MetaFileButton();
    void AtlasFileButton();

};
