#pragma once
#include <GameEngineCore/GameEngineTextureRenderer.h>

class MetaTextureRenderer : public GameEngineTextureRenderer
{
public:
    MetaTextureRenderer();
    ~MetaTextureRenderer();

    MetaTextureRenderer(const MetaTextureRenderer& _Other)                = delete;
    MetaTextureRenderer(MetaTextureRenderer&& _Other) noexcept            = delete;
    MetaTextureRenderer& operator=(const MetaTextureRenderer& _Other)     = delete;
    MetaTextureRenderer& operator=(MetaTextureRenderer&& _Other) noexcept = delete;

    void MetaSetPivot();

    // void SetMetaData(float4 _Pivot, float _TextureSizeX, float _TextureSizeY)
    //{
    //     Pivot_ = _Pivot;
    //     SizeX_ = _TextureSizeX;
    //     SizeY_ = _TextureSizeY;
    // }

    inline void SetCurData(std::vector<MetaData>& _MetaData) { CurData_ = _MetaData; }

    void CreateMetaAnimation(const std::string&         _AnimationName,
                             const FrameAnimation_DESC& _Desc,
                             std::vector<MetaData>&     _MetaDatas);

    void ChangeMetaAnimation(const std::string& _AnimationName);

protected:
    void Update(float _Delta) override;


private:
    float4 Pivot_;

    float SizeX_;
    float SizeY_;

    std::vector<MetaData> CurData_;

    std::map<std::string, std::vector<MetaData>> AllMetaData_;
};
