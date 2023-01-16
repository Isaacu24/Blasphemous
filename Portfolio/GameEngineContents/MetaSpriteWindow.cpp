#include "PreCompile.h"
#include "MetaSpriteWindow.h"
#include <GameEngineCore/GameEngineFolderTexture.h>
#include <GameEngineCore/GameEngineCoreDebug.h>
#include "MetaTextureRenderer.h"
#include <GameEngineCore/GameEngineRes.h>
#include "MetaSpriteManager.h"

MetaSpriteWindow::MetaSpriteWindow()
    : CurMetaFile_{}
    , CurAtlasFile_{}
{}

MetaSpriteWindow::~MetaSpriteWindow() {}

void MetaSpriteWindow::Initialize(GameEngineLevel* _Level) {}

void MetaSpriteWindow::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
    AtlasFileButton(_Level);
    MetaFileButton(_Level);
    AllFolderButton(_Level);
}


void MetaSpriteWindow::MetaFileButton(GameEngineLevel* _Level)
{
    if (nullptr == TargetTexture)
    {
        return;
    }

    if (true == ImGui::Button("MetaFileLoad") && nullptr == Renderer)
    {
        std::string Path
            = GameEngineGUI::OpenFileDlg(GameEngineString::AnsiToUTF8Return("메타 파일 로드"), MetaDir.GetFullPath());

        if (false == Path.empty())
        {
            GameEngineFile LoadFile = GameEngineFile(Path);
            LoadFile.Open(OpenMode::Read, FileMode::Text);

            std::string AllText = LoadFile.GetString();

            MetaSpriteManager::GetInst()->MetaParsing(AllText);

            std::vector<MetaData>& Datas = MetaSpriteManager::GetInst()->MetaDatas_;

            if (0 == TargetTexture->GetCutCount())
            {
                for (auto& [Index, PosX, PosY, Width, Height, PivotX, PivotY] : Datas)
                {
                    TargetTexture->Cut(static_cast<size_t>(PosX),
                                       static_cast<size_t>(TargetTexture->GetScale().y - PosY - Height),
                                       static_cast<size_t>(Width),
                                       static_cast<size_t>(Height));
                }
            }

            GameEngineActor* PreviewActor = _Level->CreateActor<GameEngineActor>();
            PreviewActor->GetTransform().SetLocalPosition(float4{-300.0f, 0.0f, 0.0f});
            Renderer = PreviewActor->CreateComponent<MetaTextureRenderer>();

            std::string FileName = std::filesystem::path{Path}.filename().string();

            std::string ImageName     = std::filesystem::path{FileName}.replace_extension("").string();  // Remove .meta
            std::string AnimationName = std::filesystem::path{ImageName}.replace_extension("").string();  // Remove .png

            Renderer->CreateFrameAnimationCutTexture(
                AnimationName, {ImageName, 0, static_cast<unsigned int>(Datas.size() - 1), 0.1f, true});

            Renderer->ChangeFrameAnimation(AnimationName);
            Renderer->SetCurData(Datas);

            MetaSpriteManager::GetInst()->Insert(AnimationName, Datas);
        }
    }

    //if (nullptr != Renderer && nullptr != TargetTexture && 0 != TargetTexture->GetCutCount())
    //{
    //    ImGui::SliderInt("ImageIndex", &CurFrame, 0, static_cast<int>(TargetTexture->GetCutCount() - 1));
    //    Renderer->SetTexture(TargetTexture, CurFrame);
    //    Renderer->ScaleToCutTexture(CurFrame);
    //}

    //디버깅 렌더
    if (nullptr != TargetTexture)
    {
        float4 ImagePos = TargetTexture->GetScale().Half();

        ImagePos.y = -ImagePos.y;

        GameEngineDebug::DrawTexture(TargetTexture, ImagePos);

        for (int i = 0; i < static_cast<int>(TargetTexture->GetCutCount()); i++)
        {
            float4 Pos   = TargetTexture->GetCutPos(i);
            float4 Scale = TargetTexture->GetCutScale(i);

            Pos.y = -Pos.y;
            Pos.x += Scale.x * 0.5f;
            Pos.y -= Scale.y * 0.5f;

            GameEngineDebug::DrawBox(Pos, Scale, float4::ZERO, float4(1.0f, 0.0f, 0.0f, 0.5f));
        }
    }

    if (false == CurMetaFile_.empty())
    {
        ImGui::SameLine();
        ImGui::Text(CurMetaFile_.c_str());
    }
}

void MetaSpriteWindow::AtlasFileButton(GameEngineLevel* _Level)
{
    if (true == ImGui::Button("AtlasFileLoad"))
    {
        std::string Path = GameEngineGUI::OpenFileDlg(GameEngineString::AnsiToUTF8Return("아틀라스 시트 로드"),
                                                      MetaDir.GetFullPath());

        if (false == Path.empty())
        {
            std::string        FileName   = std::filesystem::path{Path}.filename().string();
            GameEngineTexture* NewTexture = GameEngineRes<GameEngineTexture>::Find(FileName);

            TargetTexture = (nullptr != NewTexture) ? NewTexture : GameEngineTexture::Load(Path);
        }
    }

    if (false == CurAtlasFile_.empty())
    {
        ImGui::SameLine();
        ImGui::Text(TargetTexture->GetNameCopy().c_str());
    }
}

void MetaSpriteWindow::AllFolderButton(GameEngineLevel* _Level)
{
    if (true == ImGui::Button("FolderLoad"))
    {
        std::string Path
            = GameEngineGUI::OpenFolderDlg(GameEngineString::AnsiToUTF8Return("폴더 로드"), MetaDir.GetFullPath());

        if (false == Path.empty())
        {
            GameEngineDirectory Dir;
            MovePath(Dir, {"ContentsResources", "Resources", "MetaAtlas", "Penitent"});

            std::vector<GameEngineFile> Textures = Dir.GetAllFile();

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

                    MetaSpriteManager::GetInst()->MetaParsing(AllText);

                    std::string FileName      = std::filesystem::path{Textures[i].GetFileName()}.filename().string();
                    std::string ImageName     = std::filesystem::path{FileName}.replace_extension("").string();
                    std::string AnimationName = std::filesystem::path{ImageName}.replace_extension("").string();

                    if (0 == MetaSpriteManager::Inst_->MetaDatas_.size())
                    {
                        int a = 0;
                    }

                    MetaSpriteManager::GetInst()->Insert(AnimationName, MetaSpriteManager::GetInst()->MetaDatas_);
                }
            }

            MetaSpriteManager::GetInst()->CutAllTexture();
        }
    }
}

